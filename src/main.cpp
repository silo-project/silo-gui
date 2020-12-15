#ifdef __WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <httplib.h>
#include <miniz.h>

#include <iostream>

#include "api/apis.h"

int main(int argc, const char **argv) {
    httplib::Server svr;

    svr.set_file_extension_and_mimetype_mapping("circ", "text/x-logisim");

    svr.set_mount_point("/", "./mount-origin");

    registerapis(svr);

    svr.listen("0.0.0.0", 7681);

    return 0;
}
