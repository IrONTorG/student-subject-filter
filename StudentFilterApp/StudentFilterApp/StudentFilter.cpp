#include "pch.h"
#include "StudentFilter.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Logger.h"
#include <cctype> 


const std::unordered_map<char, std::string> StudentFilter::translitMap = {
    {'�', "a"}, {'�', "b"}, {'�', "v"}, {'�', "g"},
    {'�', "d"}, {'�', "e"}, {'�', "yo"}, {'�', "zh"},
    {'�', "z"}, {'�', "i"}, {'�', "y"}, {'�', "k"},
    {'�', "l"}, {'�', "m"}, {'�', "n"}, {'�', "o"},
    {'�', "p"}, {'�', "r"}, {'�', "s"}, {'�', "t"},
    {'�', "u"}, {'�', "f"}, {'�', "kh"}, {'�', "ts"},
    {'�', "ch"}, {'�', "sh"}, {'�', "shch"}, {'�', ""},
    {'�', "y"}, {'�', ""}, {'�', "e"}, {'�', "yu"},
    {'�', "ya"},
 
    {'�', "A"}, {'�', "B"}, {'�', "V"}, {'�', "G"},
    {'�', "D"}, {'�', "E"}, {'�', "Yo"}, {'�', "Zh"},
    {'�', "Z"}, {'�', "I"}, {'�', "Y"}, {'�', "K"},
    {'�', "L"}, {'�', "M"}, {'�', "N"}, {'�', "O"},
    {'�', "P"}, {'�', "R"}, {'�', "S"}, {'�', "T"},
    {'�', "U"}, {'�', "F"}, {'�', "Kh"}, {'�', "Ts"},
    {'�', "Ch"}, {'�', "Sh"}, {'�', "Shch"}, {'�', ""},
    {'�', "Y"}, {'�', ""}, {'�', "E"}, {'�', "Yu"},
    {'�', "Ya"}
};


std::string StudentFilter::Transliterate(const std::string& cyrillic) {
    std::string result;
    for (char c : cyrillic) {
        auto it = translitMap.find(c);
        if (it != translitMap.end()) {
            result += it->second;
        }
        else {
           
            result += c;
        }
    }
    return result;
}


void StudentFilter::AddStudent(const std::string& subject, const std::string& student) {
    data_[subject].insert(student);
}

bool StudentFilter::LoadFromFile(const std::string& filename) {
    data_.clear();
    Logger::LogInfo("Opening file: " + filename);

    std::ifstream file(filename);
    if (!file.is_open()) {
        Logger::LogError("Failed to open file: " + filename);
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string student, subject;

        if (iss >> student >> subject) {
            AddStudent(subject, student);
            Logger::LogInfo("Added: " + student + " - " + subject);
        }
    }

    Logger::LogInfo("File loaded successfully. Total subjects: " + std::to_string(data_.size()));
    return true;
}


std::set<std::string> StudentFilter::FilterStudents(
    const std::vector<std::string>& includeSubjects,
    const std::vector<std::string>& excludeSubjects)
{
    Logger::LogInfo("=== Starting filtering ===");

    std::set<std::string> result;

  
    for (const auto& subject : includeSubjects) {
        if (data_.count(subject)) {
            for (const auto& student : data_.at(subject)) {
                result.insert(student);
            }
        }
    }

   
    for (const auto& subject : excludeSubjects) {
        if (data_.count(subject)) {
            for (const auto& student : data_.at(subject)) {
                result.erase(student);
            }
        }
    }

    Logger::LogInfo("=== Filtering complete ===");
    Logger::LogInfo("Final result count: " + std::to_string(result.size()));
    return result;
}

const std::unordered_map<std::string, std::set<std::string>>& StudentFilter::GetData() const {
    return data_;
}