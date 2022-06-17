cmake_minimum_required(VERSION 3.21)
project(ProiectSDA)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProiectSDA main.cpp Domain/TAD/Array.h Domain/TAD/TreeNode.h Domain/TAD/BinarySearchTree.h Domain/User/User.cpp Domain/User/User.h Tests/tests.cpp Tests/tests.h Domain/Friendship/Friendship.cpp Domain/Friendship/Friendship.h Domain/Message/Message.cpp Domain/Message/Message.h Domain/Event/Event.cpp Domain/Event/Event.h Domain/Conversation/Conversation.h Repository/UserRepository.h Domain/utils.h
        Repository/EventRepository.h Repository/FriendshipRepository.h Exceptions/customException.h Exceptions/domainException.h
        Exceptions/repoException.h Exceptions/serviceException.h Exceptions/uiException.h UI/Console.h
        Repository/ConversationRepository.h Service/UserService.h Service/FriendshipService.h Service/ConversationService.h Service/Network.h)
