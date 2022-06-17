//
// Created by alext on 26/05/2022.
//

#ifndef PROIECTSDA_CONVERSATIONREPOSITORY_H
#define PROIECTSDA_CONVERSATIONREPOSITORY_H


#include "../Domain/TAD/Array.h"
#include "../Domain/Conversation/Conversation.h"
#include "../Domain/User/User.h"
#include <string>

using namespace std;

class ConversationRepository {
private:
    Array<Conversation> entities;
    string fileName;
public:
    ConversationRepository(){}

    void setFileName(const string &filename) {
        ConversationRepository::fileName = filename;
        loadFromFile();
    }

    ConversationRepository(string filename){
        loadFromFile();
    }

    void create(Message msg){
        bool empty = true;
        if(entities.getSize()==0) {
            Conversation conversation;
            conversation.add(msg);
            entities.pushBack(conversation);
        }
        else{
            for(int i=0; i<entities.getSize(); i++)
                if((msg.getUserA() == entities[i].getAll()[0].getUserA() && msg.getUserB() == entities[i].getAll()[0].getUserB()) || (msg.getUserB() == entities[i].getAll()[0].getUserA() && msg.getUserA() == entities[i].getAll()[0].getUserB())){
                    entities[i].add(msg);
                    empty = false;
                }
            if(empty){
                Conversation conversation;
                conversation.add(msg);
                entities.pushBack(conversation);
            }
        }
        saveToFile();
    }

    void update(string userA, string newUsername){
        for(int i=0; i<entities.getSize(); i++) {
            entities[i].setNewUsername(userA, newUsername);
        }
        saveToFile();
    }

    void erase(string userA, string userB){
        for(int i=0; i<entities.getSize(); i++){
            if((entities[i].getAll()[0].getUserA() == userA && entities[i].getAll()[0].getUserB() == userB) || (entities[i].getAll()[0].getUserA() == userB && entities[i].getAll()[0].getUserB() == userA)){
                entities.erase(i);
                i-=1;
            }
        }
        saveToFile();
    }

    Array<Conversation> getAll(){
        return entities;
    }

    void saveToFile(){
        if (!this->fileName.empty())
        {
            ofstream f(this->fileName);
            for(int i=0; i<entities.getSize(); i++) {
                for (int j = 0; j < entities[i].getAll().getSize(); j++) {
                    f << entities[i].getAll()[j] <<",";
                }
                f << endl;
            }
            f.close();
        }
    }

    void loadFromFile(){
        string line;
        ifstream f(this->fileName);
        while (std::getline(f, line)) {
            Conversation ob(line);
            this->entities.pushBack(ob);
        }
    }
};


#endif //PROIECTSDA_CONVERSATIONREPOSITORY_H
