//
// Created by penta on 2020-11-24.
//

#include <httplib.h>

#include "../apis.h"

void api::upload::logisimfile(const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader) {
    if (req.is_multipart_form_data()) {
        httplib::MultipartFormDataItems files;
        content_reader(
                [&files](const httplib::MultipartFormData &file) {
                    files.push_back(file);
                    return true;
                },[&files](const char *data, size_t data_length) {
                    files.back().content.append(data, data_length);
                    return true;
                });
        std::for_each(files.begin(), files.end(), [](const httplib::MultipartFormData& f) {
            std::cout << f.filename << " " << f.name << " " << f.content_type << std::endl;
        });
    } else {
        std::string body;
        content_reader(
                [&body](const char *data, size_t data_length) {
                    body.append(data, data_length);
                    return true;
                });
        res.set_content(body, "text/plain");
    }
}