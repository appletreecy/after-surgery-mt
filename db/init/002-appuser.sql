-- runs once on first startup
CREATE USER IF NOT EXISTS 'appuser'@'%' IDENTIFIED BY 'apppass';
GRANT ALL PRIVILEGES ON asurgery.* TO 'appuser'@'%';
FLUSH PRIVILEGES;
