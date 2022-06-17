//
// Created by alext on 21/05/2022.
//

#ifndef PROIECTSDA_FRIENDSHIP_H
#define PROIECTSDA_FRIENDSHIP_H

#include <string>
#include <ostream>

using namespace std;

class Friendship {
private:
    int id;
    string userA;
    string userB;
public:
    Friendship();
    Friendship(string line);
    Friendship(int id, const string &userA, const string &userB);
    const string &getUserA() const;
    void setUserA(const string &userA);
    const string &getUserB() const;
    void setUserB(const string &userB);
    int getId() const;
    friend ostream &operator<<(ostream &os, const Friendship &friendship);
    Friendship& operator=(const Friendship& friendship);

};


#endif //PROIECTSDA_FRIENDSHIP_H
