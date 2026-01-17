#include "bigint.hpp"

std::ostream& operator<<(std::ostream& out, const bigint& bigint) {
	std::vector::const_reverse_iterator it = bigint.digits.rbegin();
	for(; it != digits.rend(); it++)
		out << bigint.digits;
	return (out);
}
