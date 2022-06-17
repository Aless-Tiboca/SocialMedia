//
// Created by alext on 21/05/2022.
//

#ifndef PROIECTSDA_EVENTREPOSITORY_H
#define PROIECTSDA_EVENTREPOSITORY_H


#include "../Domain/TAD/Array.h"
#include "../Domain/Event/Event.h"
#include <fstream>

using namespace std;

class EventRepository {
private:
    Array<Event> entities;
    string fileName;
public:
    EventRepository(string filename): fileName(filename) {
        loadFromFile();
    }

    virtual ~EventRepository() {
        saveToFile();
    }

    void add(Event event){
        this->entities.pushBack(event);
        saveToFile();
    }

    void erase(int id){
        for(int i=0; i<entities.getSize(); i++){
            if(entities[i].getId() == id){
                entities.erase(i);
            }
        }
        saveToFile();
    }

    void update(int id, Event newEvent){
        for(int i=0; i<entities.getSize(); i++){
            if(entities[i].getId() == id){
                entities[i] = newEvent;
            }
        }
        saveToFile();
    }

    Array<Event> getAll(){
        return entities;
    }

    void saveToFile(){
        if (!this->fileName.empty())
        {
            ofstream f(this->fileName);
            for(int i=0; i<entities.getSize(); i++)
            {
                f << entities[i];
            }
            f.close();
        }
    }

    void loadFromFile(){
        string line;
        ifstream f(this->fileName);
        while (std::getline(f, line)) {
            Event ob(line);
            this->entities.pushBack(ob);
        }
    }
};


#endif //PROIECTSDA_EVENTREPOSITORY_H
