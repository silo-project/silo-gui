add_executable(silo-gui
        main.cpp
        library.cpp part.cpp wirenet.cpp
        api/apis.cpp
        api/upload/logisimfile.cpp api/upload/libraryfile.cpp
        api/session.cpp
        filesystem.cpp filesystem.h)

add_subdirectory(silo-main)