#pragma once
#include <drogon/drogon.h>

inline drogon::orm::DbClientPtr makeDb() {
    using namespace drogon::orm;
    const auto host = std::getenv("DB_HOST") ?: "127.0.0.1";
    const auto port = std::getenv("DB_PORT") ?: "3308";
    const auto db   = std::getenv("DB_NAME") ?: "asurgery";
    const auto user = std::getenv("DB_USER") ?: "root";
    const auto pass = std::getenv("DB_PASS") ?: "password";
    std::string conn = fmt::format("host={} port={} dbname={} user={} password={}",
                                   host, port, db, user, pass);
    return drogon::orm::DbClient::newClient(
        fmt::format("mysql://{}:{}@{}:{}/{}", user, pass, host, port, db),
        4);
}
