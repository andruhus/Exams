#ifndef HOMEWORK_AVL_TREE_H
#define HOMEWORK_AVL_TREE_H

#include "OrderedListsVirtual.h"

class AVL_Tree_Node {
public:
    DataStructure data;
    unsigned char height;
    AVL_Tree_Node *left;
    AVL_Tree_Node *right;

    AVL_Tree_Node(DataStructure data) {
        this->data = data;
        left = right = nullptr;
        height = 1;
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

class AVL_Tree : public OrderedListsVirtual {
private:
    AVL_Tree_Node *head = nullptr;

    unsigned char height(AVL_Tree_Node *p) {
        return p ? p->height : 0;
    }

    void fixheight(AVL_Tree_Node *p) {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    AVL_Tree_Node *rotateright(AVL_Tree_Node *p) {
        AVL_Tree_Node *q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }

    int bfactor(AVL_Tree_Node *p) {
        return height(p->right) - height(p->left);
    }

    AVL_Tree_Node *rotateleft(AVL_Tree_Node *q) {
        AVL_Tree_Node *p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }

    AVL_Tree_Node *balance(AVL_Tree_Node *p) {
        fixheight(p);
        if (bfactor(p) == 2) {
            if (bfactor(p->right) < 0)
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if (bfactor(p) == -2) {
            if (bfactor(p->left) > 0)
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p;
    }

    AVL_Tree_Node *insert(AVL_Tree_Node *p, DataStructure dataStructure) {
        if (!p) return new AVL_Tree_Node(dataStructure);
        if (dataStructure.getValue() < p->data.getValue())
            p->left = insert(p->left, dataStructure);
        else
            p->right = insert(p->right, dataStructure);
        return balance(p);
    }

    AVL_Tree_Node *findmin(AVL_Tree_Node *p) {
        return p->left ? findmin(p->left) : p;
    }

    AVL_Tree_Node *removemin(AVL_Tree_Node *p) {
        if (p->left == nullptr)
            return p->right;
        p->left = removemin(p->left);
        return balance(p);
    }

    AVL_Tree_Node *remove(AVL_Tree_Node *p, DataStructure dataStructure) {
        if (!p) return nullptr;
        if (dataStructure.getValue() < p->data.getValue())
            p->left = remove(p->left, dataStructure);
        else if (dataStructure.getValue() > p->data.getValue())
            p->right = remove(p->right, dataStructure);
        else {
            AVL_Tree_Node *q = p->left;
            AVL_Tree_Node *r = p->right;
            delete p;
            if (!r) return q;
            AVL_Tree_Node *min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }

public:
    void append(DataStructure dataStructure) {
        head = insert(head, dataStructure);
    }

    string toString() {
        if (head != nullptr) {
            return head->getNodeWithChildrenInString();
        } else {
            return "";
        }
    }

    static AVL_Tree createRandomListWithSize(int size) {
        AVL_Tree toReturn;
        for (int i = 0; i < size; ++i) {
            toReturn.append(DataStructure::createRandomPosition());
        }
        return toReturn;
    }

    void removeAll(DataStructure dataStructure) {
        while (!search(dataStructure).empty()) {
            head = remove(head, dataStructure);
        }
    }

    vector<DataStructure> search(DataStructure dataStructure) {
        vector<DataStructure> result;
        if (head == nullptr) {
            return result;
        }
        AVL_Tree_Node *iterationNode = head;
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
