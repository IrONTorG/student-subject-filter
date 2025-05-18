#pragma once
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

class StudentFilter {
public:
    void AddStudent(const std::string& subject, const std::string& student);
    bool LoadFromFile(const std::string& filename);
    std::set<std::string> FilterStudents(
        const std::vector<std::string>& includeSubjects,
        const std::vector<std::string>& excludeSubjects);
    const std::unordered_map<std::string, std::set<std::string>>& GetData() const;
    static std::string Transliterate(const std::string& cyrillic);

private:
    std::unordered_map<std::string, std::set<std::string>> data_;

    static const std::unordered_map<char, std::string> translitMap;

    static std::string JoinStrings(const std::vector<std::string>& strings) {
        std::string result;
        for (const auto& s : strings) {
            if (!result.empty()) result += ", ";
            result += s;
        }
        return result.empty() ? "(none)" : result;
    }
};