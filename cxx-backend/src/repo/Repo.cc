// Repo.cc
#include "Repo.h"
using namespace drogon;
using namespace drogon::orm;

std::optional<Tenant> Repo::findTenantByKey(const std::string& key){
  auto r = db_->execSqlSync("SELECT id,key_name FROM tenants WHERE key_name=?", key);
  if (r.empty()) return std::nullopt;
  return Tenant{ (long)r[0]["id"].as<long long>(), r[0]["key_name"].as<std::string>() };
}

std::optional<UserRow> Repo::findUserByEmail(long tenantId, const std::string& email){
  auto r = db_->execSqlSync(
    "SELECT id,tenant_id,email,password_hash,role FROM users WHERE tenant_id=? AND email=?",
    tenantId, email);
  if (r.empty()) return std::nullopt;
  return UserRow{ (long)r[0]["id"].as<long long>(),
                  (long)r[0]["tenant_id"].as<long long>(),
                  r[0]["email"].as<std::string>(),
                  r[0]["password_hash"].as<std::string>(),
                  r[0]["role"].as<std::string>() };
}

long Repo::insertRecord(long tenantId, const std::string& date,
                        const std::string& patientId, const std::string& status,
                        const std::string& notes){
  auto r = db_->execSqlSync(
    "INSERT INTO after_surgery_records(tenant_id,surgery_date,patient_id,status,notes) "
    "VALUES (?,?,?,?,?)", tenantId, date, patientId, status, notes);
  return r.getInsertId();
}

Json::Value Repo::listRecords(long tenantId, int page, int size){
  int offset = (page<0?0:page)* (size<=0?10:size);
  auto r = db_->execSqlSync(
    "SELECT id,surgery_date,patient_id,status,notes,created_at "
    "FROM after_surgery_records WHERE tenant_id=? "
    "ORDER BY surgery_date DESC LIMIT ? OFFSET ?",
    tenantId, size, offset);
  Json::Value arr(Json::arrayValue);
  for (auto &row : r){
    Json::Value j;
    j["id"] = (Json::UInt64)row["id"].as<long long>();
    j["surgery_date"] = row["surgery_date"].as<std::string>();
    j["patient_id"] = row["patient_id"].as<std::string>();
    j["status"] = row["status"].as<std::string>();
    j["notes"] = row["notes"].as<std::string>();
    j["created_at"] = row["created_at"].as<std::string>();
    arr.append(j);
  }
  return arr;
}
