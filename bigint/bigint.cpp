#include "bigint.hpp"

std::ostream& operator<<(std::ostream& out, const bigint& bigint) {
	
	std::vector<int>::const_reverse_iterator it = bigint.get_digits().rbegin();
	
	for (; it != bigint.get_digits().rend(); ++it)
		out << *it;
	
	return out;
}
