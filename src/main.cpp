

#ifdef __WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include "httplib.h"


int main(int argc, const char **argv) {
    httplib::Server svr;

    svr.set_mount_point("/", "./mount-origin");

    svr.Get("/api/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.listen("0.0.0.0", 7681);

    return 0;
}
