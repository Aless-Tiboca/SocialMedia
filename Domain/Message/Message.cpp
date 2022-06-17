//
// Created by alext on 21/05/2022.
//

#include "Message.h"
#include "../utils.h"

Message::Message(int id, const string &userA, const string &userB, const string &text, const string &dataTime) : id(id),
                                                                                                                 userA(userA),
                                                                                                                 userB(userB),
                                                                                                                 text(text),
                                                                                                                 dataTime(
                                                                                                                         dataTime) {}

const string &Message::getUserA() const {
    return userA;
}

void Message::setUserA(const string &userA) {
    Message::userA = userA;
}

const string &Message::getUserB() const {
    return userB;
}

void Message::setUserB(const string &userB) {
    Message::userB = userB;
}

const string &Message::getText() const {
    return text;
}

void Message::setText(const string &text) {
    Message::text = text;
}

const string &Message::getDataTime() const {
    return dataTime;
}

void Message::setDataTime(const string &dataTime) {
    Message::dataTime = dataTime;
}

int Message::getId() const {
    return id;
}

bool Message::operator<(const Message &rhs) const {
    return !compareDates(this->dataTime, rhs.dataTime);
}

bool Message::operator>(const Message &rhs) const {
    return rhs < *this;
}

bool Message::operator<=(const Message &rhs) const {
    return !(rhs < *this);
}

bool Message::operator>=(const Message &rhs) const {
    return !(*this < rhs);
}

Message::Message() {}

ostream &operator<<(ostream &os, const Message &message) {
    os << message.id << "," << message.userA << "," << message.userB << ","
       << message.text << "," << message.dataTime;
    return os;
}

string Message::toString() {
    return(userA + ": " + text);
}
