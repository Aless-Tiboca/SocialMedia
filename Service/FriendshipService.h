//
// Created by alext on 26/05/2022.
//

#ifndef PROIECTSDA_FRIENDSHIPSERVICE_H
#define PROIECTSDA_FRIENDSHIPSERVICE_H

#include "../Repository/FriendshipRepository.h"
#include "../Domain/Friendship/Friendship.h"

class FriendshipService {
private:
    FriendshipRepository friendshipRepository;
public:
    FriendshipService(){}

    void setFileName(const string &fileName) {
        friendshipRepository.setFileName(fileName);
    }

    void create(Friendship friendship){
        friendshipRepository.add(friendship);
    }

    void erase(int id){
        friendshipRepository.erase(id);
    }

    void update(int id, Friendship newFriend){
        friendshipRepository.update(id, newFriend);
    }

    Array<Friendship> getAll(){
        return friendshipRepository.getAll();
    }

    bool isIdUnique(int id){
        for(int i=0; i<getAll().getSize(); i++){
            if(getAll()[i].getId()==id)
                return false;
        }
        return true;
    }

    void populate(Array<Friendship> array){
        while(!getAll().empty()){
            friendshipRepository.erase(getAll()[0].getId());
        }
        for(int i=0; i<array.getSize();i++){
            friendshipRepository.add(array[i]);
        }
    }

    void deleteAllByUsername(string username){
        for(int i=0; i<friendshipRepository.getAll().getSize(); i++){
            if(friendshipRepository.getAll()[i].getUserA() == username || friendshipRepository.getAll()[i].getUserB() == username){
                friendshipRepository.erase(friendshipRepository.getAll()[i].getId());
                i=i-1;
            }
        }
    }

    void deleteByUsernames(string userA, string userB){
        for(int i=0; i<friendshipRepository.getAll().getSize(); i++)
            if((friendshipRepository.getAll()[i].getUserA() == userA && friendshipRepository.getAll()[i].getUserB() == userB) || (friendshipRepository.getAll()[i].getUserA() == userB && friendshipRepository.getAll()[i].getUserB() == userA)) {
                friendshipRepository.erase(friendshipRepository.getAll()[i].getId());
            }
    }
};


#endif //PROIECTSDA_FRIENDSHIPSERVICE_H
