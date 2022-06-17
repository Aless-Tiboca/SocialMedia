//
// Created by alext on 21/05/2022.
//

#include "Event.h"
#include "../utils.h"

Event::Event(int id, const string &host, const string &name, const string &location, const Array<string> &participants)
        : id(id), host(host), name(name), participants(participants), location(location) {}

const string &Event::getHost() const {
    return host;
}

void Event::setHost(const string &host) {
    Event::host = host;
}

const string &Event::getName() const {
    return name;
}

void Event::setName(const string &name) {
    Event::name = name;
}

const Array<string> &Event::getParticipants() const {
    return participants;
}

void Event::setParticipants(const Array<string> &participants) {
    Event::participants = participants;
}

const string &Event::getLocation() const {
    return location;
}

void Event::setLocation(const string &location) {
    Event::location = location;
}

Event::Event() {}

int Event::getId() const {
    return id;
}

Event &Event::operator=(const Event& event) {
    this->name = event.name;
    this->host = event.host;
    this->location = event.location;
    this->participants = event.participants;
    return *this;
}

ostream &operator<<(ostream &os, const Event &event) {
    os << event.id << "," << event.host << event.name << "," << event.location;
    for(int i=0; i<event.participants.getSize(); i++){
        os<<","<<event.participants[i];
    }

    return os;
}

Event::Event(string line) {
    Array<string> elements = splitWithDelim(line, ',');
    if(elements.getSize() >= 4){
        this->id = stoi(elements[0]);
        this->host = elements[1];
        this->name = elements[2];
        this->location = elements[3];
        for(int i=4; i<elements.getSize(); i++){
            this->participants.pushBack(elements[i]);
        }
    }

}
