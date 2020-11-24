//
// Created by penta on 2020-11-24.
//

#include <httplib.h>

#ifndef SILO_GUI_APIS_H
#define SILO_GUI_APIS_H

void registerapis(httplib::Server &svr);

namespace api {
    namespace upload {
        void logisimfile(const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader);
        void libraryfile(const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader);
    }
    namespace library {

    }
}

#endif //SILO_GUI_APIS_H