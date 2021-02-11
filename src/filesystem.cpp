//
// Created by penta on 2020-12-16.
//

#include "filesystem.h"

#include <miniz.h>
#include <filesystem>

void FileSystem::init() {
    std::filesystem::create_directory("./lib");
}

void FileSystem::unzip(std::string const &zipFile, std::string const &path) {
    mz_zip_archive zip_archive;
    memset(&zip_archive, 0, sizeof(zip_archive));

    auto status = mz_zip_reader_init_file(&zip_archive, zipFile.c_str(), 0);
    if (!status) return;
    int fileCount = (int)mz_zip_reader_get_num_files(&zip_archive);
    if (fileCount == 0) {
        mz_zip_reader_end(&zip_archive);
        return;
    }

    mz_zip_archive_file_stat file_stat;
    if (!mz_zip_reader_file_stat(&zip_archive, 0, &file_stat)) {
        mz_zip_reader_end(&zip_archive);
        return;
    }

    char* cpath = (char*)malloc(512);
    size_t cpathl = path.length() + 1;
    memcpy(cpath, path.c_str(), cpathl);
    cpath[cpathl] = '/';
    ++cpathl;
    cpath[cpathl] = '\0';

    for (int i = 0; i < fileCount; i++) {
        if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)) continue;
        if (mz_zip_reader_is_file_a_directory(&zip_archive, i)) continue;

        memcpy(cpath + cpathl, file_stat.m_filename, strlen(file_stat.m_filename) + 1);

        mz_zip_reader_extract_to_file(&zip_archive, i, cpath, 0);
    }

    mz_zip_reader_end(&zip_archive);
    free(cpath);
}