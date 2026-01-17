#include "searchable_bag.hpp"
#include "array_bag.hpp"
#include "tree_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag {

        public:

        searchable_array_bag() {}
        searchable_array_bag(const searchable_array_bag& other) : array_bag(other){}
        searchable_array_bag &operator=(const searchable_array_bag& other) {
                if (this != &other)
                        array_bag::operator=(other);
                return (*this);
        }
        ~searchable_array_bag() {}

        virtual bool has(int n) const {
                for (int i = 0; i < size; i++) {
                        if (data[i] == n)
                                return true;
                }
                return false;
        }
};

class searchable_tree_bag : public tree_bag, public searchable_bag {

        public:
                searchable_tree_bag() : tree_bag() {}
                searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other) {}
                searchable_tree_bag &operator=(const searchable_tree_bag& other) {
                        if (this != &other)
                                tree_bag::operator=(other);
                        return (*this);
                }
                ~searchable_tree_bag() {}

                virtual bool has(int n) const {
                        return (has_node(this->tree, n));
                }

                bool has_node(node *n, int val) const {
                        if (!n)
                                return false;
                        if (val == n->value)
                                return true;
                        if (val < n->value)
                                return has_node(n->l, val);
                        else
                                return has_node(n->r, val);

                }
};

class set {

        searchable_bag *setbag;

        public:
                set(searchable_bag& b) :setbag(&b) {}
                set(const set& other) : setbag(other.setbag) {}
                set& operator=(const set& other) {
                        if (this != &other)
                                setbag = other.setbag;
                        return (*this);
                }
                ~set() {}

                void insert (int n) {
                        if (!setbag->has(n))
                                setbag->insert(n);
                }

                void insert (int *arr, int size) {
                        for (int i = 0; i < size; i ++) {
                                if (!setbag->has(arr[i]))
                                        setbag->insert(arr[i]);
                        }
                }

                bag& get_bag() const {
                        return (*setbag);
                }

                void clear() {
                        setbag->clear();
                }

                void print() const {
                        setbag->print();
                }

                virtual bool has(int n) const {
                        return (setbag->has(n));
                }

};
