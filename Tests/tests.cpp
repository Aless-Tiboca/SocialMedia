//
// Created by alext on 11/05/2022.
//

#include <cassert>
#include "../Domain/Message/Message.h"
#include "../Domain/User/User.h"
#include "tests.h"
#include "../Domain/TAD/Array.h"
#include "../Domain/Friendship/Friendship.h"
#include "../Repository/UserRepository.h"
#include "../Repository/FriendshipRepository.h"
#include "../Repository/ConversationRepository.h"
#include "../Service/UserService.h"
#include "../Service/FriendshipService.h"
#include "../Service/ConversationService.h"
#include "../Service/Network.h"

void runAll(){
    testDomain();
    testRepository();
    testService();
}

void testArrayAdd() {
    Array<int> ar;
    ar.pushBack(1);
    ar.pushBack(3);
    ar.pushBack(2);
    assert(ar[0] = 1);
    assert(ar[1] = 2);
    assert(ar[3] = 3);
}

void testDomain() {
    testArrayAdd();
    testUser();
    testMessage();
    testFriendship();
}

void testMessage() {
    Message msg;
    msg.setUserA("test1");
    msg.setUserB("test2");
    msg.setDataTime("12/02/2002 10:12:12");
    msg.setText("Hei!");
    assert((msg.getUserA()=="test1"));
    assert(msg.getUserB()=="test2");
    assert(msg.getText()=="Hei!");
    assert(msg.getDataTime() == "12/02/2002 10:12:12");

    Message msg1(2,"test","test","TEST","12/02/2002 10:12:10");
    assert(msg<msg1);
}

void testUser() {
    User user("test", "****", "TEST");
    assert(user.getUsername() == "test");
    assert(user.getPassword() == "****");
    assert(user.getName() == "TEST");
    assert(user == User("test,ceva,Nicu Mihai"));
}

void testFriendship() {
    Friendship friendship(2,"test","test");
    assert(friendship.getUserB() == "test");
    assert(friendship.getUserA() == "test");
    assert(friendship.getId() == 2);
    Friendship test("2,test,test");
    assert(test.getId() == 2);
}

void testRepository() {
    testUserRepo();
    testFriendRepo();
    testConversationRepo();
}

void testUserRepo() {
    UserRepository userRepository("testUser.csv");
    userRepository.add(User("test1,0000,TEST"));
    userRepository.add(User("test0,0000,TEST"));
    userRepository.add(User("test3","0000","TEST"));
    assert(userRepository.getAllInOrder().getSize() == 3);
    userRepository.erase("test0");
    assert(userRepository.getAllInOrder().getSize() == 2);
    userRepository.erase("test1");
    userRepository.erase("test3");
}

void testFriendRepo() {
    FriendshipRepository friendshipRepository("testFriend.csv");
    friendshipRepository.add(Friendship(1,"test1","test2"));
    friendshipRepository.add(Friendship(2,"test3","test1"));
    friendshipRepository.add(Friendship(3,"test2","test2"));
    assert(friendshipRepository.getAll().getSize() == 3);
    friendshipRepository.erase(1);
    assert(friendshipRepository.getAll().getSize() == 2);
    friendshipRepository.update(2, Friendship(2,"test1", "test2"));
    assert(friendshipRepository.getAll()[1].getUserA() == "test1");
    friendshipRepository.erase(2);
    friendshipRepository.erase(3);


}

void testConversationRepo() {
    ConversationRepository conversationRepository("testConversation.csv");
    conversationRepository.create(Message(1,"test1","test2","TEST","12/02/2002 10:12:12"));
    conversationRepository.create(Message(2,"test1","test2","TEST1","12/02/2002 10:12:12"));
    conversationRepository.create(Message(3,"test1","test2","TEST2","12/02/2002 10:12:12"));
    conversationRepository.create(Message(4,"test1","test3","TEST","12/02/2002 10:12:12"));
    assert(conversationRepository.getAll().getSize() == 2);
    conversationRepository.update("test1", "altceva");
    assert(conversationRepository.getAll()[0].getAll()[0].getUserA() == "altceva");
    conversationRepository.erase("altceva", "test2");
    conversationRepository.erase("altceva", "test2");
}

void testService() {
    testUserService();
    testFriendService();
    testConversationService();
    testNetwork();
}

void testUserService() {
    UserService userService;
    userService.setFileName("testUser.csv");
    userService.create(User("test1,0000,TEST"));
    userService.create(User("test0,0000,TEST"));
    userService.create(User("test3","0000","TEST"));
    assert(userService.getAllInOrder().getSize() == 3);
    Array<Friendship> array;
    array.pushBack(Friendship(1,"test1","test3"));
    assert(userService.getAllThatAreNotFriends(array, "test1").getSize() == 1);
    userService.update("test1", User("test-1, 0001, TEsss"));
    assert(userService.getAllInOrder()[0].getUsername() == "test-1");
    userService.erase("test-1");
    userService.erase("test0");
    userService.erase("test3");
}

void testFriendService() {
    FriendshipService friendshipService;
    friendshipService.setFileName("testFriend.csv");
    friendshipService.create(Friendship(1,"test1","test2"));
    friendshipService.create(Friendship(2,"test3","test1"));
    friendshipService.create(Friendship(3,"test2","test3"));
    assert(friendshipService.getAll().getSize() == 3);
    assert(friendshipService.isIdUnique(1) == false);
    friendshipService.deleteAllByUsername("test1");
    assert(friendshipService.getAll().getSize() == 1);
    friendshipService.deleteByUsernames("test2", "test3");
    assert(friendshipService.getAll().getSize() == 0);
}

void testConversationService() {
    ConversationService conversationService;
    conversationService.setFileName("testConversation.csv");
    conversationService.create(Message(1,"test1","test2","TEST","12/02/2002 10:12:12"));
    conversationService.create(Message(2,"test1","test2","TEST1","12/02/2002 10:12:12"));
    conversationService.create(Message(3,"test1","test2","TEST2","12/02/2002 10:12:12"));
    conversationService.create(Message(4,"test1","test3","TEST","12/02/2002 10:12:12"));
    assert(conversationService.getAll().getSize() == 2);
    conversationService.updateUsername("test1", "test");
    conversationService.erase("test", "test3");
    assert(conversationService.getByUsernames("test", "test2").getAll().getSize() == 3);
    conversationService.erase("test", "test2");

}

void testNetwork() {
    Network network;
    network.setFileName("testUser.csv", "testFriend.csv","testConversation.csv");
    network.signOn("test2", "0000", "Ceva");
    network.signOn("test3", "0000", "Ceva");
    network.signOn("test1", "0000", "Ceva");
    assert(network.logIn("test1","0000").getName() == "Ceva");
    network.addFriends("test1", "test2");
    network.addFriends("test2","test3");
    assert(network.getFriends("test1").getSize() == 1);
    assert(network.getNonFriendsUsers("test1").getSize() == 1);
    network.addMessage("test1","test2", "Ceva");
    network.addMessage("test1","test2","ceva");
    network.addMessage("test2", "test3", "Test");
    assert(network.getConversation("test2", "test3").getAll().getSize() == 1);
    assert(network.getConversation("test2", "test1").getAll().getSize() == 2);
    network.unfriend("test1","test2");
    assert(network.getFriends("test1").getSize() == 0);
    network.updateUser("test1", "nou", "000", "name");
    network.deleteUser("nou");
    network.deleteUser("test2");
    network.deleteUser("test3");
}

