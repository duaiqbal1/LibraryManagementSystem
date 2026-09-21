#include "Member.h"
#include <iostream>
#include <sstream>

Member::Member() : id(0) {}

Member::Member(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}

void Member::display() const {
    std::cout << "[" << id << "] " << name << " <" << email << ">"
              << " | Borrowed Books: ";
    if (borrowedBookIds.empty()) {
        std::cout << "None";
    } else {
        for (size_t i = 0; i < borrowedBookIds.size(); ++i) {
            std::cout << borrowedBookIds[i];
            if (i != borrowedBookIds.size() - 1) std::cout << ", ";
        }
    }
    std::cout << "\n";
}

// Fields: id|name|email|borrowedId1,borrowedId2,...
std::string Member::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << name << "|" << email << "|";
    for (size_t i = 0; i < borrowedBookIds.size(); ++i) {
        oss << borrowedBookIds[i];
        if (i != borrowedBookIds.size() - 1) oss << ",";
    }
    return oss.str();
}

Member Member::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string field;
    std::vector<std::string> parts;

    while (std::getline(ss, field, '|')) {
        parts.push_back(field);
    }

    Member m;
    if (parts.size() >= 3) {
        m.id = std::stoi(parts[0]);
        m.name = parts[1];
        m.email = parts[2];

        if (parts.size() == 4 && !parts[3].empty()) {
            std::stringstream bss(parts[3]);
            std::string idStr;
            while (std::getline(bss, idStr, ',')) {
                if (!idStr.empty()) {
                    m.borrowedBookIds.push_back(std::stoi(idStr));
                }
            }
        }
    }
    return m;
}
