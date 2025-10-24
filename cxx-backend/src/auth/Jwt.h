// Jwt.h
#pragma once
#include <string>
#include <drogon/drogon.h>

namespace jwt {
    std::string sign(long userId, long tenantId, const std::string& role);
    struct Claims { long userId; long tenantId; std::string role; };
    std::optional<Claims> verify(const std::string& token);
}
