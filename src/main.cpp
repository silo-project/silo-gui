#include <cstring>
#include <csignal>

#include <libwebsockets.h>
#include <cassert>

#define RING_DEPTH 4096

struct msg {
    void *payload; /* is malloc'd */
    size_t len;
    char binary;
    char first;
    char final;
};

struct per_session_data__backend {
    struct lws_ring *ring;
    uint32_t msglen;
    uint32_t tail;
    uint8_t completed:1;
    uint8_t flow_controlled:1;
    uint8_t write_consume_pending:1;
};

struct vhd_backend {
    struct lws_context *context;
    struct lws_vhost *vhost;

    int *interrupted;
    int *options;
};

static void
__minimal_destroy_message(struct msg * _msg)
{
    struct msg * msg = _msg;

    free(msg->payload);
    msg->payload = NULL;
    msg->len = 0;
}

static int callback_backend(struct lws *wsi, enum lws_callback_reasons reason,
                             void *user, void *in, size_t len)
{
    struct per_session_data__backend *pss =
            (struct per_session_data__backend *)user;
    struct vhd_backend *vhd = (struct vhd_backend *)
            lws_protocol_vh_priv_get(lws_get_vhost(wsi),
                                     lws_get_protocol(wsi));
    const struct msg *pmsg;
    struct msg amsg;
    int m, n, flags;

    switch (reason) {

        case LWS_CALLBACK_PROTOCOL_INIT:
            vhd = static_cast<struct vhd_backend *>(
                    lws_protocol_vh_priv_zalloc(lws_get_vhost(wsi),
                            lws_get_protocol(wsi),
                            sizeof(struct vhd_backend)));
            if (!vhd)
                return -1;

            vhd->context = lws_get_context(wsi);
            vhd->vhost = lws_get_vhost(wsi);

            /* get the pointers we were passed in pvo */

            vhd->interrupted = (int *)lws_pvo_search(
                    (const struct lws_protocol_vhost_options *)in,
                    "interrupted")->value;
            vhd->options = (int *)lws_pvo_search(
                    (const struct lws_protocol_vhost_options *)in,
                    "options")->value;
            break;

        case LWS_CALLBACK_ESTABLISHED:
            /* generate a block of output before travis times us out */
            lwsl_warn("LWS_CALLBACK_ESTABLISHED\n");
            pss->ring = lws_ring_create(sizeof(struct msg), RING_DEPTH,
                                        reinterpret_cast<void (*)(void *)>(__minimal_destroy_message));
            if (!pss->ring)
                return 1;
            pss->tail = 0;
            break;

        case LWS_CALLBACK_SERVER_WRITEABLE:

            lwsl_user("LWS_CALLBACK_SERVER_WRITEABLE\n");

            if (pss->write_consume_pending) {
                /* perform the deferred fifo consume */
                lws_ring_consume_single_tail(pss->ring, &pss->tail, 1);
                pss->write_consume_pending = 0;
            }

            pmsg = static_cast<const msg *>(lws_ring_get_element(pss->ring, &pss->tail));
            if (!pmsg) {
                lwsl_user(" (nothing in ring)\n");
                break;
            }

            flags = lws_write_ws_flags(
                    pmsg->binary ? LWS_WRITE_BINARY : LWS_WRITE_TEXT,
                    pmsg->first, pmsg->final);

            /* notice we allowed for LWS_PRE in the payload already */
            m = lws_write(wsi, ((unsigned char *)pmsg->payload) +
                               LWS_PRE, pmsg->len, static_cast<lws_write_protocol>(flags));
            if (m < (int)pmsg->len) {
                lwsl_err("ERROR %d writing to ws socket\n", m);
                return -1;
            }

            lwsl_user(" wrote %d: flags: 0x%x first: %d final %d\n",
                      m, flags, pmsg->first, pmsg->final);
            /*
             * Workaround deferred deflate in pmd extension by only
             * consuming the fifo entry when we are certain it has been
             * fully deflated at the next WRITABLE callback.  You only need
             * this if you're using pmd.
             */
            pss->write_consume_pending = 1;
            lws_callback_on_writable(wsi);

            if (pss->flow_controlled &&
                (int)lws_ring_get_count_free_elements(pss->ring) > RING_DEPTH - 5) {
                lws_rx_flow_control(wsi, 1);
                pss->flow_controlled = 0;
            }

            if ((*vhd->options & 1) && pmsg && pmsg->final)
                pss->completed = 1;

            break;

        case LWS_CALLBACK_RECEIVE:

            lwsl_user("LWS_CALLBACK_RECEIVE: %4d (rpp %5d, first %d, "
                      "last %d, bin %d, msglen %d (+ %d = %d))\n",
                      (int)len, (int)lws_remaining_packet_payload(wsi),
                      lws_is_first_fragment(wsi),
                      lws_is_final_fragment(wsi),
                      lws_frame_is_binary(wsi), pss->msglen, (int)len,
                      (int)pss->msglen + (int)len);

            if (len) {
                ;
                //puts((const char *)in);
                //lwsl_hexdump_notice(in, len);
            }

            amsg.first = lws_is_first_fragment(wsi);
            amsg.final = lws_is_final_fragment(wsi);
            amsg.binary = lws_frame_is_binary(wsi);
            n = (int)lws_ring_get_count_free_elements(pss->ring);
            if (!n) {
                lwsl_user("dropping!\n");
                break;
            }

            if (amsg.final)
                pss->msglen = 0;
            else
                pss->msglen += len;

            amsg.len = len;
            /* notice we over-allocate by LWS_PRE */
            amsg.payload = malloc(LWS_PRE + len);
            if (!amsg.payload) {
                lwsl_user("OOM: dropping\n");
                break;
            }

            memcpy((char *)amsg.payload + LWS_PRE, in, len);
            if (!lws_ring_insert(pss->ring, &amsg, 1)) {
                __minimal_destroy_message(&amsg);
                lwsl_user("dropping!\n");
                break;
            }
            lws_callback_on_writable(wsi);

            if (n < 3 && !pss->flow_controlled) {
                pss->flow_controlled = 1;
                lws_rx_flow_control(wsi, 0);
            }
            break;

        case LWS_CALLBACK_CLOSED:
            lwsl_user("LWS_CALLBACK_CLOSED\n");
            lws_ring_destroy(pss->ring);

            if (*vhd->options & 1) {
                if (!*vhd->interrupted)
                    *vhd->interrupted = 1 + pss->completed;
                lws_cancel_service(lws_get_context(wsi));
            }
            break;

        default:
            break;
    }

    return 0;
}

static struct lws_protocols protocols[] = {
        { "backend", callback_backend, sizeof(per_session_data__backend), 1024, 0, NULL, 0 },
        { "http", lws_callback_http_dummy, 0, 0 },
        { NULL, NULL, 0, 0 } /* terminator */
};

static const lws_retry_bo_t retry = {
        .secs_since_valid_ping = 3,
        .secs_since_valid_hangup = 10,
};

static char interrupted, options;

static const struct lws_protocol_vhost_options pvo_options = {
        NULL,
        NULL,
        "options",		/* pvo name */
        &options	/* pvo value */
};

static const struct lws_protocol_vhost_options pvo_interrupted = {
        &pvo_options,
        NULL,
        "interrupted",		/* pvo name */
        &interrupted	/* pvo value */
};

static const struct lws_protocol_vhost_options pvo = {
        NULL,				/* "next" pvo linked-list */
        &pvo_interrupted,		/* "child" pvo linked-list */
        "lws-minimal-server-echo",	/* protocol name we belong to on this vhost */
        ""				/* ignored */
};
static const struct lws_extension extensions[] = {
        {
                "permessage-deflate",
                lws_extension_callback_pm_deflate,
                "permessage-deflate"
                "; client_no_context_takeover"
                "; client_max_window_bits"
        },
        { NULL, NULL, NULL /* terminator */ }
};

static const struct lws_http_mount mount = {
        /* .mount_next */		NULL,		/* linked-list "next" */
        /* .mountpoint */		"/",		/* mountpoint URL */
        /* .origin */			"./mount-origin",  /* serve from dir */
        /* .def */			"index.html",	/* default filename */
        /* .protocol */			NULL,
        /* .cgienv */			NULL,
        /* .extra_mimetypes */		NULL,
        /* .interpret */		NULL,
        /* .cgi_timeout */		0,
        /* .cache_max_age */		0,
        /* .auth_mask */		0,
        /* .cache_reusable */		0,
        /* .cache_revalidate */		0,
        /* .cache_intermediaries */	0,
        /* .origin_protocol */		LWSMPRO_FILE,	/* files in a dir */
        /* .mountpoint_len */		1,		/* char count */
        /* .basic_auth_login_file */	NULL,
};

void sigint_handler(int sig)
{
    interrupted = 1;
}

int main(int argc, const char **argv)
{
    struct lws_context_creation_info info;
    struct lws_context *context;
    const char *p;
    int n = 0, logs = LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE
    /* for LLL_ verbosity above NOTICE to be built into lws,
     * lws must have been configured and built with
     * -DCMAKE_BUILD_TYPE=DEBUG instead of =RELEASE */
    /* | LLL_INFO */ /* | LLL_PARSER */ /* | LLL_HEADER */
    /* | LLL_EXT */ /* | LLL_CLIENT */ /* | LLL_LATENCY */
    /* | LLL_DEBUG */;

    signal(SIGINT, sigint_handler);

    if ((p = lws_cmdline_option(argc, argv, "-d")))
        logs = atoi(p);

    lws_set_log_level(logs, NULL);
    lwsl_user("LWS minimal ws server | visit http://localhost:7681 (-s = use TLS / https)\n");

    memset(&info, 0, sizeof info); /* otherwise uninitialized garbage */
    info.port = 7681;
    info.mounts = &mount;
    info.protocols = protocols;
    info.pvo = &pvo;
    info.vhost_name = "localhost";
    info.options =
            LWS_SERVER_OPTION_VALIDATE_UTF8 |
            LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;

#if defined(LWS_WITH_TLS)
    if (lws_cmdline_option(argc, argv, "-s")) {
        lwsl_user("Server using TLS\n");
        info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
        info.ssl_cert_filepath = "localhost-100y.cert";
        info.ssl_private_key_filepath = "localhost-100y.key";
    }
#endif

    if (lws_cmdline_option(argc, argv, "-h"))
        info.options |= LWS_SERVER_OPTION_VHOST_UPG_STRICT_HOST_CHECK;

    if (lws_cmdline_option(argc, argv, "-v"))
        info.retry_and_idle_policy = &retry;

    context = lws_create_context(&info);
    if (!context) {
        lwsl_err("lws init failed\n");
        return 1;
    }

    while (n >= 0 && !interrupted)
        n = lws_service(context, 0);

    lws_context_destroy(context);

    return 0;
}
