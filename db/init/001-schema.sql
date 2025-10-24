-- Create the main schema
CREATE DATABASE IF NOT EXISTS asurgery;
USE asurgery;

-- 1️⃣  Tenants table
-- Each department or organization is a tenant.
CREATE TABLE IF NOT EXISTS tenants (
                                       id BIGINT PRIMARY KEY AUTO_INCREMENT,
                                       key_name VARCHAR(64) UNIQUE NOT NULL,        -- e.g. 'cardiology'
    display_name VARCHAR(128) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );

-- 2️⃣  Users table
-- Each user belongs to one tenant.
CREATE TABLE IF NOT EXISTS users (
                                     id BIGINT PRIMARY KEY AUTO_INCREMENT,
                                     tenant_id BIGINT NOT NULL,
                                     email VARCHAR(255) NOT NULL,
    password_hash VARCHAR(255) NOT NULL,         -- argon2id hash
    role ENUM('ADMIN','EDITOR','VIEWER') NOT NULL DEFAULT 'VIEWER',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    UNIQUE KEY uniq_tenant_email (tenant_id, email),
    CONSTRAINT fk_users_tenant FOREIGN KEY (tenant_id) REFERENCES tenants(id)
    );

-- 3️⃣  After Surgery Records
-- Equivalent to your previous AfterSurgeryTableOne
CREATE TABLE IF NOT EXISTS after_surgery_records (
                                                     id BIGINT PRIMARY KEY AUTO_INCREMENT,
                                                     tenant_id BIGINT NOT NULL,
                                                     surgery_date DATE NOT NULL,
                                                     patient_id VARCHAR(64) NOT NULL,
    status VARCHAR(64) NOT NULL,
    notes TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_asr_tenant FOREIGN KEY (tenant_id) REFERENCES tenants(id),
    INDEX idx_asr_tenant_date (tenant_id, surgery_date)
    );

