#pragma once

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

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
