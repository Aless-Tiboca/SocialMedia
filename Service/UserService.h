//
// Created by alext on 26/05/2022.
//

#ifndef PROIECTSDA_USERSERVICE_H
#define PROIECTSDA_USERSERVICE_H


#include "../Repository/UserRepository.h"
#include "../Domain/utils.h"

class UserService {
private:
    UserRepository userRepository;
public:
    UserService(){}

    void setFileName(string filename){
        userRepository.setFileName(filename);
    }

    void create(User user){
        userRepository.add(user);
    }

    void erase(string userName){
        userRepository.erase(userName);
    }

    void update(string userName, User newUser){
        userRepository.update(userName, newUser);
    }

    Array<User> getAllInOrder(){
        return userRepository.getAllInOrder();
    }

    User find(string username){
        return userRepository.find(username);
    }

    Array<User> getAllThatAreNotFriends(Array<Friendship> friends, string username){
        Array<User> nonFriends = getAllInOrder();
        nonFriends.erase(binarySearch(nonFriends, User(username,"","")));
        if(friends.getSize() == 0) return nonFriends;
        else {
            for (int i = 0; i < friends.getSize(); i++) {
                string auxUser;
                if (friends[i].getUserA() == username) {
                    auxUser = friends[i].getUserB();
                } else auxUser = friends[i].getUserA();
                User aux(auxUser, "", "");  
                nonFriends.erase(binarySearch<User>(nonFriends, aux));
            }
            return nonFriends;
        }
    }
};


#endif //PROIECTSDA_USERSERVICE_H
