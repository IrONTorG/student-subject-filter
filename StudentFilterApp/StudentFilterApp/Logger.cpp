#include "pch.h"
#include "Logger.h"
#include <fstream>
#include <ctime>
#include <iomanip>

void Logger::LogInfo(const std::string& message) {
    WriteLog("INFO", message);
}

void Logger::LogWarning(const std::string& message) {
    WriteLog("WARNING", message);
}

void Logger::LogError(const std::string& message) {
    WriteLog("ERROR", message);
}

void Logger::WriteLog(const std::string& type, const std::string& message) {
    std::ofstream logFile("app_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "[" << GetCurrentTime() << "] [" << type << "] " << message << "\n";
    }
}

std::string Logger::GetCurrentTime() {
    auto now = std::time(nullptr);
    struct tm newtime;
    localtime_s(&newtime, &now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &newtime);
    return buffer;
}