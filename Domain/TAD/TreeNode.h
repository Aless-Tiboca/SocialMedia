//
// Created by alext on 11/05/2022.
//

#ifndef PROIECTSDA_TREENODE_H
#define PROIECTSDA_TREENODE_H
template<typename T> class BinarySearchTree;

template<class T> class TreeNode {
private:
    T info;
    TreeNode<T> *left;
    TreeNode<T> *right;
public:
    TreeNode(){}

    /**
     * Constructor
     * @param info: T class object
     */
    TreeNode(T info) : info(info) {
        this->left = nullptr;
        this->right = nullptr;
    }

    /**
     * Constructor with parameters
     * @param info: T class object
     * @param left: left pointer
     * @param right: right pointer
     */
    TreeNode(T info, TreeNode<T> *left, TreeNode<T> *right) : info(info), left(left), right(right) {}

    friend class BinarySearchTree<T>;
};
#endif //PROIECTSDA_TREENODE_H
