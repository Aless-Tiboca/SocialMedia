//
// Created by alext on 22/05/2022.
//

#ifndef PROIECTSDA_FRIENDSHIPREPOSITORY_H
#define PROIECTSDA_FRIENDSHIPREPOSITORY_H


#include "../Domain/Friendship/Friendship.h"
#include "../Domain/TAD/Array.h"
#include <fstream>

using namespace std;

class FriendshipRepository {
private:
    Array<Friendship> entities;
    string fileName;
public:
    FriendshipRepository(){}

    FriendshipRepository(string filename): fileName(filename) {
        loadFromFile();
    }

    void setFileName(const string &fileName) {
        FriendshipRepository::fileName = fileName;
        loadFromFile();
    }

    void add(Friendship friendship){
        this->entities.pushBack(friendship);
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

    void update(int id, Friendship newFriend){
        erase(id);
        add(newFriend);
        saveToFile();
    }

    Array<Friendship> getAll(){
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
            Friendship ob(line);
            this->entities.pushBack(ob);
        }
    }
};


#endif //PROIECTSDA_FRIENDSHIPREPOSITORY_H
