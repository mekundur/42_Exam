#pragma once

#include <vector>
#include <iosteram>

class bigint {
	
	private:
		int num;
		std::vector digits;
	
	public:
		bigint() : num(0) {}
		bigint(const bigint &big) {}
		bigint& operator=(const bigint& big) {
			if (this != &big) {
				this->num = big.num;
				this->digits = digits.num;
			}
			return (*this);
		}		
		~bigint();


};
