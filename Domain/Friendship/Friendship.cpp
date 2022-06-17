//
// Created by alext on 21/05/2022.
//

#include "Friendship.h"
#include "../utils.h"

Friendship::Friendship(int id, const string &userA, const string &userB) : id(id), userA(userA), userB(userB) {}

const string &Friendship::getUserA() const {
    return userA;
}

void Friendship::setUserA(const string &userA) {
    Friendship::userA = userA;
}

const string &Friendship::getUserB() const {
    return userB;
}

void Friendship::setUserB(const string &userB) {
    Friendship::userB = userB;
}

int Friendship::getId() const {
    return id;
}

Friendship::Friendship() {}

ostream &operator<<(ostream &os, const Friendship &friendship) {
    os << friendship.id << "," << friendship.userA << "," << friendship.userB<<endl;
    return os;
}

Friendship::Friendship(string line) {
    Array<string> elements = splitWithDelim(line, ',');
    if(elements.getSize() == 3){
        this->id = stoi(elements[0]);
        this->userA = elements[1];
        this->userB = elements[2];
    }

}

Friendship &Friendship::operator=(const Friendship &friendship) {
    this->id = friendship.id;
    this->userA = friendship.userA;
    this->userB = friendship.userB;
    return *this;
}

