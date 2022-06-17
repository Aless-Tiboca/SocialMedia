//
// Created by alext on 21/05/2022.
//

#ifndef PROIECTSDA_USERREPOSITORY_H
#define PROIECTSDA_USERREPOSITORY_H

#include "../Domain/User/User.h"
#include "../Domain/TAD/BinarySearchTree.h"
#include "../Domain/TAD/Array.h"
#include <fstream>

using namespace std;

class UserRepository{
private:
    BinarySearchTree<User> entities;
    string fileName;
public:
    UserRepository(string filename): fileName(filename) {
        loadFromFile();
    }

    UserRepository() {}

    void setFileName(const string &fileName) {
        UserRepository::fileName = fileName;
        loadFromFile();
    }

    void add(const User& us){
        if(!entities.exist(us)){
            this->entities.add(us);
            saveToFile();
        }
        else throw repoException("This username is already used!");
    }

    void erase(const string& username){
        User user(username, "", "");
        this->entities.remove(user);
        saveToFile();
    }

    void update(const string& username, const User& newUser){
        erase(username);
        add(newUser);
        saveToFile();
    }

    Array<User> getAllInOrder(){
        Array<User> array;
        this->entities.getInOrder(array);
        return array;
    }

    User find(string username){
        User user(username, "", "");
        return entities.find(user);
    }

    void saveToFile(){
        if (!this->fileName.empty())
        {
            Array<string> aux;
            ofstream f(this->fileName);
            this->entities.getPreOrder(aux);
            for(int i=0; i<aux.getSize(); i++){
                f<<aux[i]<<endl;
            }
            f.close();
        }
    }

    void loadFromFile(){
        string line;
        ifstream f(this->fileName);
        while (std::getline(f, line)) {
            User ob(line);
            this->entities.add(ob);
        }
    }

};

#endif //PROIECTSDA_USERREPOSITORY_H
