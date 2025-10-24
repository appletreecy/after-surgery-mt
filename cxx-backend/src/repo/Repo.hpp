// Repo.h
#pragma once
#include <drogon/drogon.h>
#include <optional>

struct Tenant { long id; std::string key; };
struct UserRow { long id; long tenantId; std::string email; std::string hash; std::string role; };

class Repo {
public:
    explicit Repo(drogon::orm::DbClientPtr db): db_(std::move(db)) {}
    std::optional<Tenant> findTenantByKey(const std::string& key);
    std::optional<UserRow> findUserByEmail(long tenantId, const std::string& email);
    long insertRecord(long tenantId, const std::string& date, const std::string& patientId,
                      const std::string& status, const std::string& notes);
    drogon::Json::Value listRecords(long tenantId, int page, int size);

private:
    drogon::orm::DbClientPtr db_;
};
