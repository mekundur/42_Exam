#pragma once

#include "array_bag.hpp"
#include "searchable_bag.hpp"

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
