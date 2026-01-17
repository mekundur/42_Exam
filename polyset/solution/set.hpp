#pragma once

#include "searchable_bag.hpp"

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
