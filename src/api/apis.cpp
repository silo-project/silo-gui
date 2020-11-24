//
// Created by penta on 2020-11-24.
//

#include <httplib.h>

#include "apis.h"

void registerapis(httplib::Server &svr) {
    svr.Post("/api/upload/logisimfile", api::upload::logisimfile);
    svr.Post("/api/upload/libraryfile", api::upload::libraryfile);

    svr.Get("/api/library/list", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });
}