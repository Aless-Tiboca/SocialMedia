//
// Created by alext on 26/05/2022.
//

#ifndef PROIECTSDA_CONVERSATIONSERVICE_H
#define PROIECTSDA_CONVERSATIONSERVICE_H


#include "../Domain/Message/Message.h"
#include "../Repository/ConversationRepository.h"
#include "../Exceptions/serviceException.h"

class ConversationService {
private:
    ConversationRepository conversationRepository;
public:
    ConversationService(){}

    void setFileName(const string &fileName) {
        conversationRepository.setFileName(fileName);
    }

    void create(Message msg){
        conversationRepository.create(msg);
    }

    void erase(string userA, string userB){
        conversationRepository.erase(userA,userB);
    }

    Array<Conversation> getAll(){
        return conversationRepository.getAll();
    }

    Conversation getByUsernames(string userA, string userB){
        for(int i=0; i<getAll().getSize(); i++){
            if((getAll()[i].getAll()[0].getUserA() == userA && getAll()[i].getAll()[0].getUserB() == userB) || (getAll()[i].getAll()[0].getUserA() == userB && getAll()[i].getAll()[0].getUserB() == userA))
                return getAll()[i];
        }
        throw serviceException("There's no message between you!");
    }

    bool isIdUnique(int id){
        for(int i=0; i<getAll().getSize(); i++){
            for(int j=0; j<getAll()[i].getAll().getSize(); j++)
            if(getAll()[i].getAll()[j].getId()==id)
                return false;
        }
        return true;
    }

    void updateUsername(string userA, string newUsername){
        conversationRepository.update(userA, newUsername);
    }
};



#endif //PROIECTSDA_CONVERSATIONSERVICE_H
