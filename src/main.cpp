#ifdef __WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include "httplib.h"

#include <iostream>


int main(int argc, const char **argv) {
    httplib::Server svr;

    svr.set_file_extension_and_mimetype_mapping("circ", "text/x-logisim");

    svr.set_mount_point("/", "./mount-origin");

    svr.Post("/api/uploadlogisimfile", [](const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader) {
        if (req.is_multipart_form_data()) {
            httplib::MultipartFormDataItems files;
            content_reader(
                    [&files](const httplib::MultipartFormData &file) {
                        files.push_back(file);
                        return true;
                    },[&files](const char *data, size_t data_length) {
                        files.back().content.append(data, data_length);
                        std::cout << data;
                        return true;
                    });
        } else {
            std::string body;
            content_reader(
                    [&](const char *data, size_t data_length) {
                        body.append(data, data_length);
                        return true;
            });
            res.set_content(body, "text/plain");
        }
    });

    svr.Get("/api/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.listen("0.0.0.0", 7681);

    return 0;
}
