#ifndef HOMEWORK_NOTBALANCEDBINARYTREE_H
#define HOMEWORK_NOTBALANCEDBINARYTREE_H

#include "OrderedListsVirtual.h"

class NotBalancedBinaryTreeNode {
public:
    DataStructure data;
    NotBalancedBinaryTreeNode *left = nullptr;
    NotBalancedBinaryTreeNode *right = nullptr;

    NotBalancedBinaryTreeNode(DataStructure data) {
        this->data = data;
    }

    NotBalancedBinaryTreeNode(DataStructure data, NotBalancedBinaryTreeNode *left, NotBalancedBinaryTreeNode *right) {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    string getNodeWithChildrenInString() {
        string outputData;
        if (left != nullptr) {
            outputData += left->getNodeWithChildrenInString();
        }
        outputData += data.toString() + "\n";
        if (right != nullptr) {
            outputData += right->getNodeWithChildrenInString();
        }
        return outputData;
    }

    void search(double min, double max, vector<DataStructure> &result) {
        if (left != nullptr) {
            left->search(min, max, result);
        }
        if (data.getValue() <= max && data.getValue() >= min) {
            result.push_back(data);
        }
        if (right != nullptr) {
            right->search(min, max, result);
        }
    }
};

class NotBalancedBinaryTree : public OrderedListsVirtual {
public:
    NotBalancedBinaryTreeNode *head = nullptr;
    BinaryTree *left = nullptr;
    BinaryTree *right = nullptr;

    void append(DataStructure data) {
        if (head == nullptr) {
            head = new NotBalancedBinaryTreeNode(data);
            return;
        }
        NotBalancedBinaryTreeNode *iterationNode = head;
        while (true) {
            if (data.getValue() < iterationNode->data.getValue()) {
                if (iterationNode->left == nullptr) {
                    iterationNode->left = new NotBalancedBinaryTreeNode(data);
                    return;
                } else {
                    iterationNode = iterationNode->left;
                }

            } else {
                if (iterationNode->right == nullptr) {
                    iterationNode->right = new NotBalancedBinaryTreeNode(data);
                    return;
                } else {
                    iterationNode = iterationNode->right;
                }
            }
        }
    }

private:
    void append(NotBalancedBinaryTreeNode *node) {
        if (head == nullptr) {
            head = node;
            return;
        }
        NotBalancedBinaryTreeNode *iterationNode = head;
        while (true) {
            if (node->data.getValue() < iterationNode->data.getValue()) {
                if (iterationNode->left == nullptr) {
                    iterationNode->left = node;
                    return;
                } else {
                    iterationNode = iterationNode->left;
                }
            } else {
                if (iterationNode->right == nullptr) {
                    iterationNode->right = node;
                    return;
                } else {
                    iterationNode = iterationNode->right;
                }
            }
        }
    }

public:
    string toString() {
        if (head != nullptr) {
            return head->getNodeWithChildrenInString();
        } else {
            return "";
        }
    }

    static NotBalancedBinaryTree createRandomListWithSize(int size) {
        NotBalancedBinaryTree toReturn;
        for (int i = 0; i < size; ++i) {
            toReturn.append(DataStructure::createRandomPosition());
        }
        return toReturn;
    }

    void removeAll(DataStructure dataStructure) {
        if (head == nullptr) {
            return;
        }
        if (head->data.equals(dataStructure)) {
            if (head->left == nullptr && head->right == nullptr) {
                head = nullptr;
                return;
            }
            if (head->left == nullptr && head->right != nullptr) {
                head = head->right;
                removeAll(dataStructure);
                return;
            }
            if (head->left != nullptr && head->right == nullptr) {
                head = head->left;
                return;
            }
            if (head->left != nullptr && head->right != nullptr) {
                NotBalancedBinaryTreeNode *leftPart = head->left;
                head = head->right;
                append(leftPart);
                removeAll(dataStructure);
                return;
            }
        }

        NotBalancedBinaryTreeNode *iterationNode = head;
        while (true) {
            if (dataStructure.getValue() < iterationNode->data.getValue()) {
                if (iterationNode->left == nullptr) {
                    return;
                }
                if (iterationNode->left->data.equals(dataStructure)) {
                    if (iterationNode->left->left == nullptr && iterationNode->left->right == nullptr) {
                        iterationNode->left = nullptr;
                        return;
                    }
                    if (iterationNode->left->left == nullptr && iterationNode->left->right != nullptr) {
                        iterationNode->left = iterationNode->left->right;
                        removeAll(dataStructure);
                        return;
                    }
                    if (iterationNode->left->left != nullptr && iterationNode->left->right == nullptr) {
                        iterationNode->left = iterationNode->left->left;
                        return;
                    }
                    if (iterationNode->left->left != nullptr && iterationNode->left->right != nullptr) {
                        NotBalancedBinaryTreeNode *leftPart = iterationNode->left->left;
                        iterationNode->left = iterationNode->left->right;
                        append(leftPart);
                        removeAll(dataStructure);
                        return;
                    }
                } else {
                    iterationNode = iterationNode->left;
                }
            } else {
                if (iterationNode->right == nullptr) {
                    return;
                }
                if (iterationNode->right->data.equals(dataStructure)) {
                    if (iterationNode->right->left == nullptr && iterationNode->right->right == nullptr) {
                        iterationNode->right = nullptr;
                        return;
                    }
                    if (iterationNode->right->left == nullptr && iterationNode->right->right != nullptr) {
                        iterationNode->right = iterationNode->right->right;
                        removeAll(dataStructure);
                        return;
                    }
                    if (iterationNode->right->left != nullptr && iterationNode->right->right == nullptr) {
                        iterationNode->right = iterationNode->right->left;
                        return;
                    }
                    if (iterationNode->right->left != nullptr && iterationNode->right->right != nullptr) {
                        NotBalancedBinaryTreeNode *leftPart = iterationNode->right->left;
                        iterationNode->right = iterationNode->right->right;
                        append(leftPart);
                        removeAll(dataStructure);
                        return;
                    }
                } else {
                    iterationNode = iterationNode->right;
                }
            }
        }
    }

    vector<DataStructure> search(DataStructure dataStructure) {
        vector<DataStructure> result;
        if (head == nullptr) {
            return result;
        }
        NotBalancedBinaryTreeNode *iterationNode = head;
        while (true) {
            if (iterationNode->data.equals(dataStructure)) {
                result.push_back(iterationNode->data);
                if (iterationNode->right == nullptr) {
                    return result;
                }
                if (iterationNode->right->data.equals(dataStructure)) {
                    iterationNode = iterationNode->right;
                } else {
                    return result;
                }
            }
            if (dataStructure.getValue() < iterationNode->data.getValue()) {
                if (iterationNode->left == nullptr) {
                    return result;
                } else {
                    iterationNode = iterationNode->left;
                }
            }
            if (dataStructure.getValue() > iterationNode->data.getValue()) {
                if (iterationNode->right == nullptr) {
                    return result;
                } else {
                    iterationNode = iterationNode->right;
                }
            }
        }
    }

    vector<DataStructure> search(double double1, double double2) {
        vector<DataStructure> result;
        if (head == nullptr) {
            return result;
        }
        double min = (double1 > double2) ? double2 : double1;
        double max = (double1 > double2) ? double1 : double2;
        head->search(min, max, result);
        return result;
    }
};

#endif
