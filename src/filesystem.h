//
// Created by penta on 2020-12-16.
//

#include <string>

#ifndef SILO_GUI_FILESYSTEM_H
#define SILO_GUI_FILESYSTEM_H

namespace FileSystem {
    void init();
    void unzip(std::string const &zipFile, std::string const &path);
}

#endif //SILO_GUI_FILESYSTEM_H
