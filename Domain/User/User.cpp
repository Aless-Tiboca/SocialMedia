//
// Created by alext on 11/05/2022.
//

#include "User.h"
#include "../TAD/Array.h"
#include "../utils.h"

User::User() {}

User::User(const string &username, const string &password, const string &name) : username(username),
                                                                                 password(password),
                                                                                 name(name) {}

const string &User::getUsername() const {
    return username;
}

void User::setUsername(const string &username) {
    User::username = username;
}

const string &User::getPassword() const {
    return password;
}

void User::setPassword(const string &password) {
    User::password = password;
}

const string &User::getName() const {
    return name;
}

void User::setName(const string &name) {
    User::name = name;
}

bool User::operator<(const User &rhs) const {
    return username < rhs.username;
}

bool User::operator>(const User &rhs) const {
    return rhs < *this;
}

bool User::operator<=(const User &rhs) const {
    return !(rhs < *this);
}

bool User::operator>=(const User &rhs) const {
    return !(*this < rhs);
}

ostream &operator<<(ostream &os, const User &user) {
    os << user.username << "," << user.password << ","
       << user.name <<endl;
    return os;
}

bool User::operator==(const User &rhs) const {
    return username == rhs.username;
}

bool User::operator!=(const User &rhs) const {
    return !(rhs == *this);
}

User::User(string line) {
    Array<string> elements = splitWithDelim(line, ',');
    if(elements.getSize() == 3){
        this->username = elements[0];
        this->password = elements[1];
        this->name = elements[2];
    }
}

User &User::operator=(const User &rhs) {
    this->username = rhs.username;
    this->name = rhs.name;
    this->password = rhs.password;
    return *this;
}

string User::toString() {
    return (this->username + "," + this->password + "," + this->name);
}





