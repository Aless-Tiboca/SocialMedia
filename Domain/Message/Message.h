//
// Created by alext on 21/05/2022.
//

#ifndef PROIECTSDA_MESSAGE_H
#define PROIECTSDA_MESSAGE_H


#include <string>
#include <ostream>

using namespace std;

class Message {
private:
    int id;
    string userA;
    string userB;
    string text;
    string dataTime;
public:
    Message();

    Message(int id, const string &userA, const string &userB, const string &text, const string &dataTime);

    const string &getUserA() const;

    void setUserA(const string &userA);

    const string &getUserB() const;

    void setUserB(const string &userB);

    const string &getText() const;

    void setText(const string &text);

    const string &getDataTime() const;

    void setDataTime(const string &dataTime);

    int getId() const;

    bool operator<(const Message &rhs) const;

    bool operator>(const Message &rhs) const;

    bool operator<=(const Message &rhs) const;

    bool operator>=(const Message &rhs) const;

    friend ostream &operator<<(ostream &os, const Message &message);

    string toString();
};


#endif //PROIECTSDA_MESSAGE_H
