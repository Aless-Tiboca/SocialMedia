//
// Created by alext on 26/05/2022.
//

#ifndef PROIECTSDA_NETWORK_H
#define PROIECTSDA_NETWORK_H


#include "FriendshipService.h"
#include "UserService.h"
#include "ConversationService.h"
#include "../Exceptions/serviceException.h"


class Network {
private:
    UserService userService;
    FriendshipService friendshipService;
    ConversationService conversationService;
public:
    Network()= default;

    void setFileName(const string& userFile, const string& friendFile, const string& conversationFile){
        userService.setFileName(userFile);
        friendshipService.setFileName(friendFile);
        conversationService.setFileName(conversationFile);
    }

    User logIn(string username, string password){
        if(userService.find(username).getPassword() == password)
            return userService.find(username);
        else throw serviceException("The Password was incorrect! Try again.");
    }

    User signOn(string username, string password, string name){
        userService.create(User(username, password, name));
        return userService.find(username);
    }

   void updateUser(string current, string username, string password, string name){
        userService.update(current, User(username, password, name));
        if(current != username){
            Array<Friendship> array = getFriends(current);
            conversationService.updateUsername(current, username);
            for (int i = 0; i < array.getSize(); i++) {
                Friendship newFriend = array[i];
                if(array[i].getUserA() == current)
                    newFriend.setUserA(username);
                else
                    newFriend.setUserB(username);
                friendshipService.update(array[i].getId(), newFriend);
            }
        }
    }

    Array<Friendship> getFriends(string username){
        Array<Friendship> friends;
        for(int i=0; i<friendshipService.getAll().getSize(); i++){
            if(friendshipService.getAll()[i].getUserA() == username || friendshipService.getAll()[i].getUserB() == username){
                friends.pushBack(friendshipService.getAll()[i]);
            }
        }
        return friends;
    }

    Array<User> getNonFriendsUsers(string username){
        return userService.getAllThatAreNotFriends(getFriends(username), username);
    }

    void addFriends(string userA, string userB){
        int id = rand();
        while(!friendshipService.isIdUnique(id)) id = rand();
        friendshipService.create(Friendship(id, userA, userB));
    }

    void deleteUser(string username){
        userService.erase(username);
        for(int i=0; i<getFriends(username).getSize(); i++){
            if(getFriends(username)[i].getUserA() == username)
                conversationService.erase(username, getFriends(username)[i].getUserB());
            else conversationService.erase(username, getFriends(username)[i].getUserA());
        }
        friendshipService.deleteAllByUsername(username);
    }

    Conversation getConversation(string userA, string userB){
        return conversationService.getByUsernames(userA, userB);
    }

    void addMessage(string userA, string userB, string text){
        int id = rand();
        while(!conversationService.isIdUnique(id)) id = rand();
        tm* data;
        time_t t = time(NULL);
        data = localtime(&t);
        char charTime[100];
        strftime(charTime, 100, "%d/%m/%Y %H:%M:%S", data);
        string time(charTime);
        conversationService.create(Message(id, userA, userB, text, time));
    }

    void unfriend(string userA, string userB){
        friendshipService.deleteByUsernames(userA, userB);
        conversationService.erase(userA, userB);
    }
};


#endif //PROIECTSDA_NETWORK_H
