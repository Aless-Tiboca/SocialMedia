//
// Created by alext on 21/05/2022.
//

#ifndef PROIECTSDA_CONVERSATION_H
#define PROIECTSDA_CONVERSATION_H


#include "../TAD/BinarySearchTree.h"
#include "../Message/Message.h"
#include "../TAD/Array.h"
#include "../utils.h"
#include <fstream>
#include <ostream>

using namespace std;

class Conversation {
private:
    Array<Message> conversation;
public:
    Conversation() {}

    Conversation(string line){
        Array<string> elements = splitWithDelim(line, ',');
        for(int i=0; i<elements.getSize(); i+=5){
            Message aux(stoi(elements[i]), elements[i+1], elements[i+2], elements[i+3], elements[i+4]);
            conversation.pushBack(aux);
        }
    }

    void add(Message mess){
        this->conversation.pushBack(mess);
    }

    void erase(int id){
        for(int i=0; i<conversation.getSize(); i++){
            if(conversation[i].getId() == id){
                conversation.erase(i);
            }
        }
    }

    void setNewUsername(string userA, string newUsername){
        for(int i=0; i<conversation.getSize(); i++){
            if(conversation[i].getUserB() == userA)
                conversation[i].setUserB(newUsername);
            else if(conversation[i].getUserA() == userA)
                conversation[i].setUserA(newUsername);
        }
    }

    void deleteAll(){
        conversation.clear();
    }

    Array<Message> getAll(){
        return this->conversation;

    }

    friend ostream &operator<<(ostream &os, const Conversation& conversation) {
        for(int i=0; i<conversation.conversation.getSize(); i++){
            os<<conversation.conversation[i]<<",";
        }
        return os;
    }
};


#endif //PROIECTSDA_CONVERSATION_H
