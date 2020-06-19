#ifndef HOMEWORK_LINKEDLIST_H
#define HOMEWORK_LINKEDLIST_H

#include "OrderedListsVirtual.h"

class LinkedListNode {
public:
    DataStructure data;
    LinkedListNode *next = nullptr;

    LinkedListNode(DataStructure data) {
        this->data = data;
    }

    LinkedListNode(DataStructure data, LinkedListNode *next) {
        this->data = data;
        this->next = next;
    }
};

class LinkedList : public OrderedListsVirtual {
private:
    LinkedListNode *head = nullptr;

public:
    void append(DataStructure dataStructure) {
        if (head == nullptr) {
            head = new LinkedListNode(dataStructure);
            return;
        }
        if (head->data.getValue() > dataStructure.getValue()) {
            head = new LinkedListNode(dataStructure, head);
            return;
        }
        LinkedListNode *iterationNode = head;
        while (iterationNode->next != nullptr) {
            if (iterationNode->next->data.getValue() < dataStructure.getValue()) {
                iterationNode = iterationNode->next;
            } else {
                break;
            }
        }
        if (iterationNode->next == nullptr) {
            iterationNode->next = new LinkedListNode(dataStructure);
        } else {
            iterationNode->next = new LinkedListNode(dataStructure, iterationNode->next);
        }
    }

    string toString() {
        if (head == nullptr) {
            return "";
        }
        string toReturn;
        LinkedListNode *iterationNode = head;
        while (iterationNode != nullptr) {
            toReturn += iterationNode->data.toString();
            toReturn += "\n";
            iterationNode = iterationNode->next;
        }
        return toReturn;
    }

    static LinkedList createRandomListWithSize(int size) {
        LinkedList toReturn;
        for (int i = 0; i < size; ++i) {
            toReturn.append(DataStructure::createRandomPosition());
        }
        return toReturn;
    }

    void removeAll(DataStructure dataStructure) {
        if (head == nullptr)
            return;
        if (head->data.equals(dataStructure)) {
            head = head->next;
            removeAll(dataStructure);
        }
        LinkedListNode *iterationNode = head;
        while (iterationNode != nullptr) {
            if (iterationNode->next->data.equals(dataStructure)) {
                iterationNode->next = iterationNode->next->next;
            }
            if (iterationNode->data.getValue() > dataStructure.getValue()) {
                return;
            }
            iterationNode = iterationNode->next;
        }
    }

    vector<DataStructure> search(DataStructure dataStructure) {
        vector<DataStructure> result;
        LinkedListNode *iterationNode = head;
        while (iterationNode != nullptr) {
            if (iterationNode->data.equals(dataStructure)) {
                result.push_back(iterationNode->data);
            }
            if (iterationNode->data.getValue() > dataStructure.getValue()) {
                return result;
            }
            iterationNode = iterationNode->next;
        }
        return result;
    }

    vector<DataStructure> search(double double1, double double2) {
        double min = (double1 > double2) ? double2 : double1;
        double max = (double1 > double2) ? double1 : double2;
        vector<DataStructure> result;
        LinkedListNode *iterationNode = head;
        while (iterationNode != nullptr) {
            if (iterationNode->data.getValue() >= min) {
                if (iterationNode->data.getValue() <= max) {
                    result.push_back(iterationNode->data);
                } else {
                    return result;
                }
            }
            iterationNode = iterationNode->next;
        }
        return result;
    }
};

#endif
