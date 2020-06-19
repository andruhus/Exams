#ifndef HOMEWORK_ORDEREDLISTSVIRTUAL_H
#define HOMEWORK_ORDEREDLISTSVIRTUAL_H

#include "../DataStructure.h"

class OrderedListsVirtual {
    virtual void append(DataStructure dataStructure) = 0;

    virtual string toString() = 0;

    virtual void removeAll(DataStructure dataStructure) = 0;

    virtual vector<DataStructure> search(DataStructure dataStructure) = 0;

    virtual vector<DataStructure> search(double double1, double double2) = 0;
};

#endif
