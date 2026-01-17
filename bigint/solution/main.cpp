#include "bigint.hpp"
#include "iostream"
int main() {
	
	const bigint a(42);
	bigint b(21), c, d(1337), e(d), x(999);
	
	std::cout << "x = " << x << std::endl;
	std::cout << "++x = " << ++x << std::endl;
	std::cout << "x << 3 = " << (x << 3) << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "x = " << x << std::endl;
	std::cout << "a + b = " << a + b << std::endl;
	std::cout << "b + a = " << b + a << std::endl;
	std::cout << "b + d = " << b + d << std::endl;
	std::cout << "d + b = " << d + b << std::endl;
	std::cout << "c += a " << (c += a) << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "++b = " << ++b << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "b++ = " << b++ << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(d < a)  = " << (d < a) << std::endl;
	std::cout << "(d > a)  = " << (d > a) << std::endl;
	std::cout << "(d == a)  = " << (d == a) << std::endl;
	std::cout << "(d != a)  = " << (d != a) << std::endl;
	std::cout << "(d <= a)  = " << (d <= a) << std::endl;
	std::cout << "(d >= a)  = " << (d >= a) << std::endl;
	std::cout << "(b << 10)  = " << (b << 10) << std::endl;
	std::cout << "(b << 10) + 42 = " << (b << 10) + 42 << std::endl;
	std::cout << "(d <<= 4) " << (d <<= 4) << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(d >> 2)  = " << (d >> 2) << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "(b >> 4)  = " << (b >> 4) << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "(b >>= 4)  = " << (b >>= 4) << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(d >>= 2) " << (d >>=(const bigint)2) << std::endl;
}
