cmake_minimum_required(VERSION 3.16)
project(cxx_backend_mt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
find_library(ARGON2_LIB argon2)
include_directories(${JSONCPP_INCLUDE_DIRS})

add_executable(cxx_backend_mt
        src/main.cpp
        src/middleware/TenantGuard.cc
        src/auth/Jwt.cc
        src/auth/Password.cc
        src/controllers/AuthCtrl.cc
        src/controllers/RecordsCtrl.cc
        src/repo/Repo.cc
        src/util/Db.h
        src/auth/Jwt.h
        src/auth/Jwt.cc
        src/repo/Repo.hpp
        src/repo/Repo.cc
)

target_link_libraries(cxx_backend_mt
        Drogon::Drogon
        OpenSSL::SSL OpenSSL::Crypto
        ${JSONCPP_LIBRARIES}
        ${ARGON2_LIB}
)
