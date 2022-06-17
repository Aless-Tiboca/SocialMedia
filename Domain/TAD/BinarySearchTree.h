//
// Created by alext on 23/05/2022.
//

#ifndef PROIECTSDA_BINARYSEARCHTREE_H
#define PROIECTSDA_BINARYSEARCHTREE_H

#include "TreeNode.h"
#include "Array.h"
#include "../../Exceptions/repoException.h"
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class BinarySearchTree {
private:
    TreeNode<T> *root;

    void add(TreeNode<T> *adress, T element) {
        if (adress->info > element) {
            if (adress->left != nullptr) {
                add(adress->left, element);
            } else {
                adress->left = new TreeNode<T>(element, nullptr, nullptr);
            }
        } else {
            if (adress->right != nullptr) {
                add(adress->right, element);
            } else {
                adress->right = new TreeNode<T>(element, nullptr, nullptr);
            }
        }
    }

    void inOrder(TreeNode<T> *pNode, Array<T>& array){
        if(pNode != nullptr) {
            inOrder(pNode->left, array);
            array.pushBack(pNode->info);
            inOrder(pNode->right, array);
        }
    }

    void preOrder(TreeNode<T>* t, Array<string>& stringArray)
    {
        if (t != nullptr)
        {
            stringArray.pushBack(t->info.toString());
            preOrder(t->left, stringArray);
            preOrder(t->right, stringArray);
        }
    }

    TreeNode<T>* findMin(TreeNode<T>* t)
    {
        TreeNode<T>* min = t;
        while (min->left != nullptr) //min node is the leftmost node
            min = min->left;
        return min;
    }

    TreeNode<T>* find(TreeNode<T>* t, T item)
    {
        if (t == nullptr) //empty tree
            return nullptr;
        else if (item == t->info) //item found
            return t;

            //item not found; look for right and left subtrees recursively
        else if (item < t->info)
            return find(t->left, item);
        else
            return find(t->right, item);
    }

    bool erase(TreeNode<T>*& t, T item)
    {
        if (t == nullptr) //no deletion
            return 0;

        else if (item > t->info) //item not found; look in right or left subtrees
            erase(t->right, item);
        else if (item < t->info)
            erase(t->left, item);

        else //item found
        {
            if (t->left == nullptr && t->right == nullptr) //item is contained in a leaf node
            {
                delete t;
                t = nullptr;
            }

            else if (t->left == nullptr) //node has only a right child
            {   //replace the node with its right child
                TreeNode<T>* del = t;
                t = t->right;
                delete del;
            }

            else if (t->right == nullptr) //node has only a left child
            {   //replace the node with its left child
                TreeNode<T>* del = t;
                t = t->left;
                delete del;
            }

            else //node containing the item has both its children
            {   //replace the node to delete with the min from the right subtree
                TreeNode<T>* temp = findMin(t->right);
                t->info = temp->info;
                erase(t->right, t->info);
            }   //alternatively we can replace the node to delete with the max node from the left tree
            return 1; //item found and deleted
        }
    }
public:
    /**
     * Constructor
     */
    BinarySearchTree() {
        this->root = nullptr;
    }

    /**
     * Add element
     * @param element: T class object
     */
    void add(T element) {
        if(this->root == nullptr) {
            this->root = new TreeNode<T>(element, nullptr, nullptr);
        }
        else {
            add(this->root, element);
        }
    }


    /**
     * Get all elements in order on a array of strings
     */
    void getInOrder(Array<T>& array) {
        inOrder(this->root, array);
    }

    /**
     * Get all elements in pre order on a array of strings
     */
    void getPreOrder(Array<string>& stringArray){
        preOrder(this->root, stringArray);
    }

    /**
     * Delete a entity from the binary search tree
     * @param value the entity to delete
     */
    void remove(T value){
        erase(root, value);
    }

    /**
     * Search and return the value found
     * @param item
     * @return
     */
    T find(T item)
    {
        if (find(this->root, item) != nullptr)
            return find(this->root, item)->info;
        throw repoException("Nothing was found!");
    }
                    
    /**
     * Search if there is an entity equal with item
     * @param item
     * @return
     */
    bool exist(T item)
    {
        if (find(this->root, item) != nullptr)
            return true;
        return false;
    }

};


#endif //PROIECTSDA_BINARYSEARCHTREE_H
