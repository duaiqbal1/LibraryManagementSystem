#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>

class Member {
public:
    int id;
    std::string name;
    std::string email;
    std::vector<int> borrowedBookIds;

    Member();
    Member(int id, const std::string& name, const std::string& email);

    void display() const;
    std::string serialize() const;
    static Member deserialize(const std::string& line);
};

#endif // MEMBER_H
