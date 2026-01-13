#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <vector>

class bigint {

	private:
		int	_num;
		std::vector<int>	_digits;

	public:
		bigint() : _num(0) {
			store_digits();
		};

		bigint(int n) : _num(n) {
			store_digits();
		};
		
		
		bigint(const bigint& other) {
			_num = other._num;
			_digits = other._digits;
		};

		bigint& operator=(const bigint& other) {
			if (this != &other) {
				_num = other._num;
				_digits = other._digits;
			}
		return (*this);
		};
		
		void store_digits() {
			int tmp = _num;
			if (tmp == 0) {
				_digits.push_back(0);
			}
			else {
				while (tmp > 0) {
					_digits.push_back(tmp % 10);
					tmp /= 10;
				}
			}
		}

		const std::vector<int>& get_digits() const {
			return (_digits);
		}

		// arithmetic operators
		bigint operator+(const bigint& other) const {
			bigint result;
			result._digits.clear();
			const std::vector<int>& a = this->_digits;
			const std::vector<int>& b = other._digits;
			int	carry = 0;
			int	sum = 0;
			for (size_t i = 0; i < a.size() || i < b.size(); i++) {
				sum = carry;
				if (i < a.size())
					sum += a[i];
				if (i < b.size())
					sum += b[i];
				result._digits.push_back(sum % 10);
				carry = sum / 10;
			}
			if (carry)
				result._digits.push_back(carry);	
			return (result);
		}

		bigint& operator+=(const bigint& other) {
			bigint result;
			result._digits.clear();
			const std::vector<int>& a = this->_digits;
			const std::vector<int>& b = other._digits;
			int	carry = 0;
			int	sum = 0;
			for (size_t i = 0; i < a.size() || i < b.size(); i++) {
				sum = carry;
				if (i < a.size())
					sum += a[i];
				if (i < b.size())
					sum += b[i];
				result._digits.push_back(sum % 10);
				carry = sum / 10;
			}
			if (carry)
				result._digits.push_back(carry);	
			*this = result;
			return (*this);
		}

		// incrementing & decrementing operators
		bigint& operator++() {
			*this += bigint(1);
			return (*this);
		}
		
		bigint operator++(int) {
			bigint tmp(*this);
			*this += bigint(1);
			return (tmp);
		}

		// comparasion operators
		bool operator<(const bigint& bigint) const {
			if (this->_digits.size() != bigint._digits.size())
				return (this->_digits.size() < bigint._digits.size());
			
			for (int i = this->_digits.size() - 1; i >= 0; --i) {
				if (this->_digits[i] != bigint._digits[i])
					return (this->_digits[i] < bigint._digits[i]);
			}
			return (false);
		}
		bool operator==(const bigint& bigint) const {
			return (this->_digits == bigint._digits);
		}
		bool operator>(const bigint& bigint) const {
			return (bigint < *this);
		}
		bool operator<=(const bigint& bigint) const {
			return (*this < bigint || *this == bigint);
		}
		bool operator>=(const bigint& bigint) const {
			return (bigint < *this || *this == bigint);
		}
		bool operator!=(const bigint& bigint) const {
			return !(this->_digits == bigint._digits);
		}

		// digit shifting operators
		bigint operator<<(int n) const {
			bigint result;
			result._digits.clear();
			for (int i = 0; i < n; i++)
				result._digits.push_back(0);
			for (size_t i = 0; i < this->_digits.size(); i++)
				result._digits.push_back(this->_digits[i]);
			return (result);
		}
		
		bigint& operator<<=(int n) {
			bigint result;
			result._digits.clear();
			for (int i = 0; i < n; i++)
				result._digits.push_back(0);
			for (size_t i = 0; i < this->_digits.size(); i++)
				result._digits.push_back(this->_digits[i]);
			*this = result;
			return (*this);
		}

		bigint operator>>(int n) const {
			bigint result(*this);
			for (int i = 0; i < n && result._digits.size() > 0 ; i++)
				result._digits.erase(result._digits.begin());
			return (result);
		}
		
		bigint& operator>>=(int n) {
			bigint result(*this);
			for (int i = 0; i < n && result._digits.size() > 0 ; i++)
				result._digits.erase(result._digits.begin());
			*this = result;
			return (*this);
		}

		bigint& operator>>=(const bigint& big) {
			return (*this >>= big._num);
		}
};

std::ostream& operator<<(std::ostream& out, const bigint& bigint);

#endif
