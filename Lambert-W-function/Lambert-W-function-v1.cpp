#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>

const int precision = 100; // CHANGE FOR HIGHER PRECISION
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<precision> > arbFloat;

// Prototypes
bool isStringValid(std::string str);
bool isNumberValid(arbFloat x);

int main() {
    // Multi-precision float declaration
    arbFloat wnew = 0.0;
    
    // Input and check string input
    std::cout << "0 <= x <= 1e9\nW(x), x = ";
    std::string inputStr;
    std::cin >> inputStr;
    if(!isStringValid(inputStr)) return 2;
    
    // Convert to arbFloat and check number
    arbFloat input = static_cast<arbFloat>(inputStr);
    if(!isNumberValid(input)) return 3;
    
    std::cout << std::setprecision(precision) << "\nConvergence:\n";
    
    std::string firstStr, secondStr;
    
    // Calculations
    int i;
    for(i = 0; i <= 1e99; i++){
        firstStr = wnew.convert_to<std::string>();
        firstStr.resize(precision + 2);
        
        wnew = ((wnew * wnew) + input * exp(-wnew))/(1+wnew);
        
        secondStr = wnew.convert_to<std::string>();
        secondStr.resize(precision + 2);
        
        std::cout << '\t' << wnew << '\n';
        
        if(firstStr == secondStr)
            break;
    }
    
    // Print result
    std::cout << "\nW(" << input << ") = " << wnew << "\n\n(rounded up to "
            << precision << " digits, precise after " << i << " iterations)\n";

    return 0;
}

// Check input
bool isStringValid(std::string str){
    // Check string containing multiple .
    std::size_t pos = str.find('.', 0);
    if(pos != std::string::npos){
        pos = str.find('.', pos+1);
        if(pos != std::string::npos){
            std::cout << "\nError: Multiple decimal marks\n";
            return false;
        }
    }
    
    // Check if NaN
    try{
        std::stod(str);
    } catch(...){
        std::cout << "\nError: NaN\n";
    }
    
    return true;
}

// Check number
bool isNumberValid(arbFloat x){
    // Check if result is imaginary
    if(x < 0){
        std::cout << "\nError: Imaginary result\n";
        return false;
    }
    
    // Range check
    if(x > 1e9){
        std::cout << "\nError: Out of bounds\n";
        return false;
    }
    
    return true;
}
