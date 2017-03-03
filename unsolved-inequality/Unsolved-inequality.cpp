#include <boost/multiprecision/cpp_dec_float.hpp>
//#include <cmath>
#include <iostream>

const int PRECISION = 10000;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<PRECISION>> arbFloat;

enum returnID {success = 0, precisionExceeded = 1};

int main(){
	arbFloat k = 6, 
		threeK = pow(3, k), 
		twoK = pow(2, k), 
		floorK;
	bool isSolution = false;

	for(; !isSolution; ++k){
		threeK *= 3, twoK *= 2, floorK = floor(threeK / twoK);
		isSolution = threeK - twoK * floorK > twoK - floorK - 2;
	}

	if(threeK - twoK * floorK <= twoK - floorK - 2){
		std::cout << "Solution at k = " << k << "\n";
		return returnID::success;
	} else {
		std::cout << "Error: Precision exceeded at k = " << k << " with " << PRECISION << " digits\n";
		return returnID::precisionExceeded;
	}
}
