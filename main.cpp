#include <iostream>
#include "Domain/TAD/Array.h"
#include "Domain/User/User.h"
#include "Tests/tests.h"
#include "Domain/TAD/BinarySearchTree.h"
#include "Repository/UserRepository.h"
#include "UI/Console.h"

int main() {
    runAll();
    Console cons;
    cons.setFileName("users.csv", "friends.csv", "conversations.csv");
    cons.FirstPage();

    return 0;
}
