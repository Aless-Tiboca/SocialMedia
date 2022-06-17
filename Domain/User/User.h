//
// Created by alext on 11/05/2022.
//

#ifndef PROIECTSDA_USER_H
#define PROIECTSDA_USER_H

#include <string>
#include <ostream>

using namespace std;

class User {
private:
    string username;
    string password;
    string name;
public:
    User();

    /**
     * Cosntructor with parameters
     */
    User(const string &username, const string &password, const string &name);

    User(string line);

    const string &getUsername() const;

    void setUsername(const string &username);

    const string &getPassword() const;

    void setPassword(const string &password);

    const string &getName() const;

    void setName(const string &name);

    bool operator<(const User &rhs) const;

    bool operator>(const User &rhs) const;

    bool operator<=(const User &rhs) const;

    bool operator>=(const User &rhs) const;

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;

    friend ostream &operator<<(ostream &os, const User &user);

    string toString();

    User& operator=(const User &rhs);
};


#endif //PROIECTSDA_USER_H
