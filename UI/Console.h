//
// Created by alext on 23/05/2022.
//

#ifndef PROIECTSDA_CONSOLE_H
#define PROIECTSDA_CONSOLE_H


#include "../Service/Network.h"
#include "../Exceptions/uiException.h"
#include <cstring>
#include <fstream>
#include <limits>

using namespace std;

class Console {
private:
    Network network;
    User currentUser;

    void firstMenu() {
        cout <<"-------START-------"<<endl;
        cout << "1.Log in" << endl;
        cout << "2.Sign on" << endl;
        cout << "x.Exit" <<endl;
    }

    void userMenu() {
        cout << "-------" <<currentUser.getUsername()<< "-------"<<endl;
        cout << "1.Show friends" << endl;
        cout << "2.Add a new friend" << endl;
        cout << "3.Change details of my account"<<endl;
        cout << "4.Delete my account" << endl;
        cout << "x.Log out" <<endl;
    }

    void validateInput(istream& is){
        if(!is.good()){
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
            throw uiException("Invalid input!");
        }
    }

    void friendMenu(string friendUser){
        cout << "-------" <<friendUser<< "-------"<<endl;
        cout << "1.Show conversation" << endl;
        cout << "2.Text a message" << endl;
        cout << "3.Unfriend" << endl;
        cout << "x.Exit" <<endl;
    }
public:
    Console()= default;

    void setFileName(const string& userFile, const string& friendFile, const string& conversationFile) {
        network.setFileName(userFile, friendFile, conversationFile);
    }

    void FirstPage() {
        bool ok = true;
        char option;
        while(ok) {
            firstMenu();
            cout << "Enter option: " << endl;
            cin >> option;
            switch (option) {
                case '1': {
                    runLogIn();
                    break;
                }
                case '2': {
                    runSignOn();
                    break;
                }
                case 'x':{
                    ok = false;
                    break;
                }
                default:
                    cout << "Your option is invalid!" << endl;
            }
        }
    }

    void runLogIn(){
        try{
            string username, password;
            cout<<"Username:"<<endl;
            cin>>username;
            cout<<"Password:"<<endl;
            cin>>password;
            currentUser = network.logIn(username, password);
            UserPage();
        }
        catch (customException& e){
            cout<<e.what()<<endl;
        }
    }

    void runSignOn(){
        try{
            string username, password, name;
            cout << "Username:" << endl;
            cin >> username;
            cout << "Password:" << endl;
            cin >> password;
            cout << "Name:" << endl;
            getline(cin>>ws, name);
            currentUser = network.signOn(username, password, name);
            UserPage();
        }
        catch (customException& e){
            cout<<e.what()<<endl;
        }
    }

    void UserPage() {
        bool ok = true;
        char option;
        while(ok) {
            userMenu();
            cout << "Enter option: " << endl;
            cin >> option;
            switch (option) {
                case '1': {
                    runShowFriends();
                    break;
                }
                case '2': {
                    runAddFriend();
                    break;
                }
                case '3':{
                    runUpdateAccount();
                    break;
                }
                case '4':{
                    runDeleteAccount();
                    currentUser = User();
                    break;
                }
                case 'x':{
                    ok = false;
                    currentUser = User();
                    break;
                }
                default:
                    cout << "Your option is invalid!" << endl;
            }
        }
    }

    void runShowFriends(){
        try{
            Array<Friendship> friends = network.getFriends(currentUser.getUsername());
            for (int i = 0; i < friends.getSize(); i++) {
                if (friends[i].getUserA() == currentUser.getUsername())
                    cout << i + 1 << "." << friends[i].getUserB() << endl;
                else
                    cout << i + 1 << "." << friends[i].getUserA() << endl;
            }
            string index;
            cout<<"Open friend profile ('x' for Exit):"<<endl;
            cin>>index;
            if(index != "x"){
                int id = stoi(index)-1;
                string friendUsername;
                if(friends.getSize() < id) throw uiException("Invalid input");
                else{
                    if (friends[id].getUserA() == currentUser.getUsername())
                        friendUsername = friends[id].getUserB();
                    else friendUsername = friends[id].getUserA();
                    FriendPage(friendUsername);
                }
            }
        }
        catch (customException& e){
            cout<<e.what()<<endl;
        }
    }

    void runAddFriend(){
        try{
            Array<User> nonFriends = network.getNonFriendsUsers(currentUser.getUsername());
            for (int i = 0; i < nonFriends.getSize(); i++) {
                cout << i + 1 << "." << nonFriends[i].getUsername()<<": "<<nonFriends[i].getName()<< endl;
            }
            int index;
            cout << "Chose who do you want to add as a friend ('x' to exit): " << endl;
            validateInput(cin>>index);
            network.addFriends(currentUser.getUsername(), nonFriends[index-1].getUsername());
        }
        catch (customException& e){
            cout<<e.what()<<endl;
        }
    }

    void runUpdateAccount(){
        try{

            bool ok = true;
            char option;
            while(ok) {
                cout << "1.Username" << endl;
                cout << "2.Password" << endl;
                cout << "3.Name" << endl;
                cout << "x.Exit" << endl;
                cout << "Enter option: " << endl;
                cin >> option;
                switch (option) {
                    case '1': {
                        string username;
                        cout << "Enter your new username:" << endl;
                        cin >> username;
                        network.updateUser(currentUser.getUsername(), username, currentUser.getPassword(), currentUser.getName());
                        currentUser.setUsername(username);
                        break;
                    }
                    case '2': {
                        string password;
                        cout<<"Enter your new password:" <<endl;
                        cin>>password;
                        network.updateUser(currentUser.getUsername(), currentUser.getUsername(), password, currentUser.getName());
                        currentUser.setPassword(password);
                        break;
                    }
                    case '3':{
                        string name;
                        cout << "Enter your new name:" << endl;
                        getline(cin >> ws, name);
                        network.updateUser(currentUser.getUsername(), currentUser.getUsername(),
                                           currentUser.getPassword(), name);
                        currentUser.setName(name);
                        break;
                    }
                    case 'x': {
                        ok = false;
                        break;
                    }
                    default:
                        cout << "Your option is invalid!" << endl;
                }

            }
        }
        catch (customException& e){
            cout<<e.what()<<endl;
        }
    }

    void runDeleteAccount(){
        network.deleteUser(currentUser.getUsername());
        FirstPage();
    }

    void FriendPage(string friendUsername) {
        bool ok = true;
        char option;
        while(ok) {
            friendMenu(friendUsername);
            cout << "Enter option: " << endl;
            cin>>option;
            switch (option) {
                case '1': {
                    runShowConversation(friendUsername);
                    break;
                }
                case '2': {
                    runAddMessage(friendUsername);
                    break;
                }
                case '3':{
                    runUnfriend(friendUsername);
                    ok = false;
                    break;
                }
                case 'x':{
                    ok = false;
                    break;
                }
                default:
                    cout << "Your option is invalid!" << endl;
            }
        }
    }

    void runAddMessage(string &friendUsername) {
        try{
            string text;
            cout << "Enter you message:" << endl;
            getline(cin >> ws, text);
            network.addMessage(currentUser.getUsername(), friendUsername, text);
        }
        catch (customException& e){
            cout<<e.what()<<endl;
        }
    }

    void runShowConversation(string &friendUsername) {
        try{
            Conversation conversation = network.getConversation(currentUser.getUsername(), friendUsername);
            for (int i = 0; i < conversation.getAll().getSize(); i++) {
                cout << conversation.getAll()[i].toString() << endl;
            }
        }
        catch (customException& e){
            cout<<e.what()<<endl;
        }
    }

    void runUnfriend(string &friendUsername){
        try{
            network.unfriend(currentUser.getUsername(), friendUsername);
        }
        catch (customException& e){
            cout<<e.what()<<endl;
        }
    }
};


#endif //PROIECTSDA_CONSOLE_H
