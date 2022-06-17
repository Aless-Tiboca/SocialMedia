//
// Created by alext on 21/05/2022.
//

#ifndef PROIECTSDA_EVENT_H
#define PROIECTSDA_EVENT_H

#include <string>
#include <ostream>
#include "../User/User.h"
#include "../TAD/Array.h"

using namespace std;

class Event {
private:
    int id;
    string host;
    string name;
    string location;
    Array<string> participants;

public:
    Event();

    Event(string line);

    Event(int id, const string &host, const string &name, const string &location, const Array<string> &participants);

    const string &getHost() const;

    void setHost(const string &host);

    const string &getName() const;

    void setName(const string &name);

    const Array<string> &getParticipants() const;

    void setParticipants(const Array<string> &participants);

    const string &getLocation() const;

    void setLocation(const string &location);

    int getId() const;

    Event& operator=(const Event& event);

    friend ostream &operator<<(ostream &os, const Event &event);
};


#endif //PROIECTSDA_EVENT_H
