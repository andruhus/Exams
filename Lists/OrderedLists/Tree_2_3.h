#ifndef HOMEWORK_TREE_2_3_H
#define HOMEWORK_TREE_2_3_H

#include "OrderedListsVirtual.h"

struct Tree_2_3_Node {
public:
    int size;
    DataStructure data[3];
    Tree_2_3_Node *first;
    Tree_2_3_Node *second;
    Tree_2_3_Node *third;
    Tree_2_3_Node *fourth;
    Tree_2_3_Node *parent;

    string getNodeWithChildrenInString() {
        string outputData;
        if (first != nullptr) {
            outputData += first->getNodeWithChildrenInString();
        }
        outputData += data[0].toString() + "\n";
        if (second != nullptr) {
            outputData += second->getNodeWithChildrenInString();
        }
        if (size != 1) {
            outputData += data[1].toString() + "\n";
        }
        if (third != nullptr) {
            outputData += third->getNodeWithChildrenInString();
        }
        return outputData;
    }

    void search(double min, double max, vector<DataStructure> &result) {
        if (first != nullptr) {
            first->search(min, max, result);
        }
        if (data[0].getValue() <= max && data[0].getValue() >= min) {
            result.push_back(data[0]);
        }
        if (second != nullptr) {
            second->search(min, max, result);
        }
        if (size != 1) {
            if (data[1].getValue() <= max && data[1].getValue() >= min) {
                result.push_back(data[1]);
            }
        }
        if (third != nullptr) {
            third->search(min, max, result);
        }
    }

    void search(DataStructure dataStructure, vector<DataStructure> &result) {
        if (first != nullptr) {
            first->search(dataStructure, result);
        }
        if (data[0].equals(dataStructure)) {
            result.push_back(data[0]);
        }
        if (second != nullptr) {
            second->search(dataStructure, result);
        }
        if (size != 1) {
            if (data[1].equals(dataStructure)) {
                result.push_back(data[1]);
            }
        }
        if (third != nullptr) {
            third->search(dataStructure, result);
        }
    }

    bool find(DataStructure dataStructure) {
        for (int i = 0; i < size; ++i)
            if (data->equals(dataStructure)) return true;
        return false;
    }

    void swap(DataStructure &x, DataStructure &y) {
        DataStructure r = x;
        x = y;
        y = r;
    }

    void sort2(DataStructure &x, DataStructure &y) {
        if (x.getValue() > y.getValue()) swap(x, y);
    }

    void sort3(DataStructure &x, DataStructure &y, DataStructure &z) {
        if (x.getValue() > y.getValue()) swap(x, y);
        if (x.getValue() > z.getValue()) swap(x, z);
        if (y.getValue() > z.getValue()) swap(y, z);
    }

    void sort() {
        if (size == 1) return;
        if (size == 2) sort2(data[0], data[1]);
        if (size == 3) sort3(data[0], data[1], data[2]);
    }

    void insert_to_node(DataStructure dataStructure) {
        data[size] = dataStructure;
        size++;
        sort();
    }

    void remove_from_node(DataStructure k) {
        if (size >= 1 && data[0].equals(k)) {
            data[0] = data[1];
            data[1] = data[2];
            size--;
        } else if (size == 2 && data[1].equals(k)) {
            data[1] = data[2];
            size--;
        }
    }

    void become_node2(DataStructure k, Tree_2_3_Node *first_, Tree_2_3_Node *second_) {
        data[0] = k;
        first = first_;
        second = second_;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
        size = 1;
    }

    bool is_leaf() {
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
    }

public:
    Tree_2_3_Node(DataStructure k) : size(1), data{k, k, k}, first(nullptr),
                                     second(nullptr),
                                     third(nullptr), fourth(nullptr), parent(nullptr) {}

    Tree_2_3_Node(DataStructure k, Tree_2_3_Node *first_, Tree_2_3_Node *second_, Tree_2_3_Node *third_,
                  Tree_2_3_Node *fourth_, Tree_2_3_Node *parent_) :
            size(1), data{k, k, k}, first(first_), second(second_),
            third(third_), fourth(fourth_), parent(parent_) {}
};

class Tree_2_3 : public OrderedListsVirtual {
private:
    Tree_2_3_Node *head = nullptr;

    Tree_2_3_Node *split(Tree_2_3_Node *item) {
        if (item->size < 3) return item;

        Tree_2_3_Node *x = new Tree_2_3_Node(item->data[0], item->first, item->second, nullptr, nullptr,
                                             item->parent);
        Tree_2_3_Node *y = new Tree_2_3_Node(item->data[2], item->third, item->fourth, nullptr, nullptr,
                                             item->parent);
        if (x->first) x->first->parent = x;
        if (x->second) x->second->parent = x;
        if (y->first) y->first->parent = y;
        if (y->second) y->second->parent = y;

        if (item->parent) {
            item->parent->insert_to_node(item->data[1]);

            if (item->parent->first == item) item->parent->first = nullptr;
            else if (item->parent->second == item) item->parent->second = nullptr;
            else if (item->parent->third == item) item->parent->third = nullptr;

            if (item->parent->first == nullptr) {
                item->parent->fourth = item->parent->third;
                item->parent->third = item->parent->second;
                item->parent->second = y;
                item->parent->first = x;
            } else if (item->parent->second == nullptr) {
                item->parent->fourth = item->parent->third;
                item->parent->third = y;
                item->parent->second = x;
            } else {
                item->parent->fourth = y;
                item->parent->third = x;
            }

            Tree_2_3_Node *tmp = item->parent;
            delete item;
            return tmp;
        } else {
            x->parent = item;
            y->parent = item;
            item->become_node2(item->data[1], x, y);
            return item;
        }
    }

    Tree_2_3_Node *insert(Tree_2_3_Node *p, DataStructure k) {
        if (!p) return new Tree_2_3_Node(k);

        if (p->is_leaf()) p->insert_to_node(k);
        else if (k.getValue() <= p->data[0].getValue()) insert(p->first, k);
        else if ((p->size == 1) || ((p->size == 2) && k.getValue() <= p->data[1].getValue())) insert(p->second, k);
        else insert(p->third, k);

        return split(p);
    }

    Tree_2_3_Node *redistribute(Tree_2_3_Node *leaf) {
        Tree_2_3_Node *parent = leaf->parent;
        Tree_2_3_Node *first = parent->first;
        Tree_2_3_Node *second = parent->second;
        Tree_2_3_Node *third = parent->third;

        if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
            if (first == leaf) {
                parent->first = parent->second;
                parent->second = parent->third;
                parent->third = nullptr;
                parent->first->insert_to_node(parent->data[0]);
                parent->first->third = parent->first->second;
                parent->first->second = parent->first->first;

                if (leaf->first != nullptr) parent->first->first = leaf->first;
                else if (leaf->second != nullptr) parent->first->first = leaf->second;

                if (parent->first->first != nullptr) parent->first->first->parent = parent->first;

                parent->remove_from_node(parent->data[0]);
                delete first;
            } else if (second == leaf) {
                first->insert_to_node(parent->data[0]);
                parent->remove_from_node(parent->data[0]);
                if (leaf->first != nullptr) first->third = leaf->first;
                else if (leaf->second != nullptr) first->third = leaf->second;

                if (first->third != nullptr) first->third->parent = first;

                parent->second = parent->third;
                parent->third = nullptr;

                delete second;
            } else if (third == leaf) {
                second->insert_to_node(parent->data[1]);
                parent->third = nullptr;
                parent->remove_from_node(parent->data[1]);
                if (leaf->first != nullptr) second->third = leaf->first;
                else if (leaf->second != nullptr) second->third = leaf->second;

                if (second->third != nullptr) second->third->parent = second;

                delete third;
            }
        } else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
            if (third == leaf) {
                if (leaf->first != nullptr) {
                    leaf->second = leaf->first;
                    leaf->first = nullptr;
                }

                leaf->insert_to_node(parent->data[1]);
                if (second->size == 2) {
                    parent->data[1] = second->data[1];
                    second->remove_from_node(second->data[1]);
                    leaf->first = second->third;
                    second->third = nullptr;
                    if (leaf->first != nullptr) leaf->first->parent = leaf;
                } else if (first->size == 2) {
                    parent->data[1] = second->data[0];
                    leaf->first = second->second;
                    second->second = second->first;
                    if (leaf->first != nullptr) leaf->first->parent = leaf;

                    second->data[0] = parent->data[0];
                    parent->data[0] = first->data[1];
                    first->remove_from_node(first->data[1]);
                    second->first = first->third;
                    if (second->first != nullptr) second->first->parent = second;
                    first->third = nullptr;
                }
            } else if (second == leaf) {
                if (third->size == 2) {
                    if (leaf->first == nullptr) {
                        leaf->first = leaf->second;
                        leaf->second = nullptr;
                    }
                    second->insert_to_node(parent->data[1]);
                    parent->data[1] = third->data[0];
                    third->remove_from_node(third->data[0]);
                    second->second = third->first;
                    if (second->second != nullptr) second->second->parent = second;
                    third->first = third->second;
                    third->second = third->third;
                    third->third = nullptr;
                } else if (first->size == 2) {
                    if (leaf->second == nullptr) {
                        leaf->second = leaf->first;
                        leaf->first = nullptr;
                    }
                    second->insert_to_node(parent->data[0]);
                    parent->data[0] = first->data[1];
                    first->remove_from_node(first->data[1]);
                    second->first = first->third;
                    if (second->first != nullptr) second->first->parent = second;
                    first->third = nullptr;
                }
            } else if (first == leaf) {
                if (leaf->first == nullptr) {
                    leaf->first = leaf->second;
                    leaf->second = nullptr;
                }
                first->insert_to_node(parent->data[0]);
                if (second->size == 2) {
                    parent->data[0] = second->data[0];
                    second->remove_from_node(second->data[0]);
                    first->second = second->first;
                    if (first->second != nullptr) first->second->parent = first;
                    second->first = second->second;
                    second->second = second->third;
                    second->third = nullptr;
                } else if (third->size == 2) {
                    parent->data[0] = second->data[0];
                    second->data[0] = parent->data[1];
                    parent->data[1] = third->data[0];
                    third->remove_from_node(third->data[0]);
                    first->second = second->first;
                    if (first->second != nullptr) first->second->parent = first;
                    second->first = second->second;
                    second->second = third->first;
                    if (second->second != nullptr) second->second->parent = second;
                    third->first = third->second;
                    third->second = third->third;
                    third->third = nullptr;
                }
            }
        } else if (parent->size == 1) {
            leaf->insert_to_node(parent->data[0]);

            if (first == leaf && second->size == 2) {
                parent->data[0] = second->data[0];
                second->remove_from_node(second->data[0]);

                if (leaf->first == nullptr) leaf->first = leaf->second;

                leaf->second = second->first;
                second->first = second->second;
                second->second = second->third;
                second->third = nullptr;
                if (leaf->second != nullptr) leaf->second->parent = leaf;
            } else if (second == leaf && first->size == 2) {
                parent->data[0] = first->data[1];
                first->remove_from_node(first->data[1]);

                if (leaf->second == nullptr) leaf->second = leaf->first;

                leaf->first = first->third;
                first->third = nullptr;
                if (leaf->first != nullptr) leaf->first->parent = leaf;
            }
        }
        return parent;
    }

    Tree_2_3_Node *merge(Tree_2_3_Node *leaf) {
        Tree_2_3_Node *parent = leaf->parent;

        if (parent->first == leaf) {
            parent->second->insert_to_node(parent->data[0]);
            parent->second->third = parent->second->second;
            parent->second->second = parent->second->first;

            if (leaf->first != nullptr) parent->second->first = leaf->first;
            else if (leaf->second != nullptr) parent->second->first = leaf->second;

            if (parent->second->first != nullptr) parent->second->first->parent = parent->second;

            parent->remove_from_node(parent->data[0]);
            delete parent->first;
            parent->first = nullptr;
        } else if (parent->second == leaf) {
            parent->first->insert_to_node(parent->data[0]);

            if (leaf->first != nullptr) parent->first->third = leaf->first;
            else if (leaf->second != nullptr) parent->first->third = leaf->second;

            if (parent->first->third != nullptr) parent->first->third->parent = parent->first;

            parent->remove_from_node(parent->data[0]);
            delete parent->second;
            parent->second = nullptr;
        }

        if (parent->parent == nullptr) {
            Tree_2_3_Node *tmp = nullptr;
            if (parent->first != nullptr) tmp = parent->first;
            else tmp = parent->second;
            tmp->parent = nullptr;
            delete parent;
            return tmp;
        }
        return parent;
    }

    Tree_2_3_Node *fix(Tree_2_3_Node *leaf) {
        if (leaf->size == 0 && leaf->parent == nullptr) {
            delete leaf;
            return nullptr;
        }
        if (leaf->size != 0) {
            if (leaf->parent) return fix(leaf->parent);
            else return leaf;
        }

        Tree_2_3_Node *parent = leaf->parent;
        if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2)
            leaf = redistribute(leaf);
        else if (parent->size == 2 && parent->third->size == 2) leaf = redistribute(leaf);
        else
            leaf = merge(leaf);

        return fix(leaf);
    }

    Tree_2_3_Node *search_min(Tree_2_3_Node *p) {
        if (!p) return p;
        if (!(p->first)) return p;
        else return search_min(p->first);
    }

    Tree_2_3_Node *search(Tree_2_3_Node *p, DataStructure k) {
        if (!p) return nullptr;

        if (p->find(k)) return p;
        else if (k.getValue() < p->data[0].getValue()) return search(p->first, k);
        else if ((p->size == 2) && (k.getValue() < p->data[1].getValue()) || (p->size == 1))
            return search(p->second, k);
        else if (p->size == 2) return search(p->third, k);
    }

    Tree_2_3_Node *remove(Tree_2_3_Node *p, DataStructure k) {
        Tree_2_3_Node *item = search(p, k);

        if (!item) return p;

        Tree_2_3_Node *min = nullptr;
        if (item->data[0].equals(k)) min = search_min(item->second);
        else min = search_min(item->third);

        if (min) {
            DataStructure &z = (k.equals(item->data[0]) ? item->data[0] : item->data[1]);
            item->swap(z, min->data[0]);
            item = min;
        }

        item->remove_from_node(k);
        return fix(item);
    }

public:
    void append(DataStructure dataStructure) {
        head = insert(head, dataStructure);
    }

    string toString() {
        if (head == nullptr)
            return "";
        return head->getNodeWithChildrenInString();
    }

    static Tree_2_3 createRandomListWithSize(int size) {
        Tree_2_3 toReturn;
        for (int i = 0; i < size; ++i) {
            toReturn.append(DataStructure::createRandomPosition());
        }
        return toReturn;
    }

    void removeAll(DataStructure dataStructure) {
        while (!search(dataStructure).empty())
            head = remove(head, dataStructure);
    }

    vector<DataStructure> search(DataStructure dataStructure) {
        vector<DataStructure> result;
        if (head == nullptr) {
            return result;
        }
        head->search(dataStructure, result);
        return result;
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
