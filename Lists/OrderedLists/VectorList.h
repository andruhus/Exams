#ifndef HOMEWORK_VECTORLIST_H
#define HOMEWORK_VECTORLIST_H

#include "OrderedListsVirtual.h"

class VectorList : public OrderedListsVirtual {
private:
    vector<DataStructure> base;
public:
    void append(DataStructure dataStructure) {
        if (base.size() == 0) {
            base.push_back(dataStructure);
            return;
        }
        for (int i = 0; i < base.size(); ++i) {
            if (base[i].getValue() > dataStructure.getValue()) {
                base.insert(base.begin() + i, dataStructure);
                return;
            }
        }
        base.push_back(dataStructure);
    }

    string toString() {
        string toReturn;
        for (int i = 0; i < base.size(); ++i) {
            toReturn += to_string(base[i].getValue()) + " = " + base[i].toString();
            toReturn += "\n";
        }
        return toReturn;
    }

    static VectorList createRandomListWithSize(int size) {
        VectorList toReturn;
        for (int i = 0; i < size; ++i) {
            toReturn.append(DataStructure::createRandomPosition());
        }
        return toReturn;
    }

    void removeAll(DataStructure dataStructure) {
        for (int i = 0; i < base.size(); ++i) {
            if (base[i].equals(dataStructure)) {
                base.erase(base.begin() + i);
                removeAll(dataStructure);
                break;
            }
            if (base[i].getValue() > dataStructure.getValue()) {
                return;
            }
        }
    }

    vector<DataStructure> search(DataStructure dataStructure) {
        vector<DataStructure> result;
        for (int i = 0; i < base.size(); ++i) {
            if (base[i].equals(dataStructure)) {
                result.push_back(base[i]);
            }
            if (base[i].getValue() > dataStructure.getValue()) {
                return result;
            }
        }
        return result;
    }

    vector<DataStructure> search(double double1, double double2) {
        double min = (double1 > double2) ? double2 : double1;
        double max = (double1 > double2) ? double1 : double2;
        vector<DataStructure> result;
        for (int i = 0; i < base.size(); ++i) {
            if (base[i].getValue() >= min) {
                if (base[i].getValue() <= max) {
                    result.push_back(base[i]);
                } else {
                    return result;
                }
            }
        }
        return result;
    }

};

#endif
