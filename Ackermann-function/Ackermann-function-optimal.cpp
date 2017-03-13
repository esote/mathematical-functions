// A majority of this code is from Rosetta Code: https://rosettacode.org/wiki/Ackermann_function#Efficient_version
// This adapatation allows for user input
#include <iostream>
#include <sstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>

using big_int = boost::multiprecision::cpp_int;

big_int ipow(big_int base, big_int exp);
big_int ackermann(unsigned m, unsigned n);

int main(){
	std::string mStr, nStr;
	
	std::cout << "Ack(m,n)\nm = ";
	std::getline(std::cin, mStr);

	std::cout << "n = ";
	std::getline(std::cin, nStr);

	std::cout << "Ack(" + mStr + ',' + nStr + ") = " 
		<< ackermann(boost::lexical_cast<unsigned>(mStr),boost::lexical_cast<unsigned>(nStr)) << '\n';

	return 0;
}

big_int ipow(big_int base, big_int exp){
	big_int result(1);
	while(exp){
		if(exp & 1){
			result *= base;
		}
		exp >>= 1;
		base *= base;
	}
	return result;
}

big_int ackermann(unsigned m, unsigned n){
	static big_int (*ack)(unsigned, big_int) =
		[](unsigned m, big_int n)->big_int {
			switch(m){
				case 0:
					return n+1;
				case 1:
					return n+2;
				case 2:
					return 3+2*n;
				case 3:
					return 5 + 8 * (ipow(big_int(2), n) - 1);
				default:
					return n == 0 ? ack(m - 1, big_int(1)) : ack(m - 1, ack(m, n - 1));
			}
		};
	return ack(m, big_int(n));
}
