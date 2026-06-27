cmake_minimum_required(VERSION 3.16)

project(file_byte_transfer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(file_byte_transfer main.cpp)

include(GNUInstallDirs)
install(TARGETS file_byte_transfer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
