#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <exception>

const int PRECISION = 100;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<PRECISION> > arbFloat;

bool isStringValid(const std::string & str);
bool isNumberValid(const arbFloat & x);
inline std::string resizeArbtoString(const arbFloat & x);

int main() {
    arbFloat wnew;
    
    // Input and check string
    std::cout << "0 <= x < inf\nW(x), x = ";
    std::string inputStr;
    std::getline(std::cin, inputStr);
    
    if(!isStringValid(inputStr)) return 2;
    
    arbFloat input = static_cast<arbFloat>(inputStr);
    
    if(!isNumberValid(input)) return 3;
    
    // Starting guess
    if(input >= 2) wnew = log(input) - log(log(input)) + (log(log(input)) / log(input));
    
    std::cout << std::setprecision(PRECISION)
            << "\nInitial Guess: " << wnew << "\nConvergence:\n";
    
    std::string preComp, postComp;
    
    // Calculations
    int i;
    do{
        std::cout << '\t' << wnew << '\n';
        
        preComp = resizeArbtoString(wnew);
        
        wnew -= ((wnew * exp(wnew)) - input) /
                (exp(wnew) * (wnew + 1) - ((wnew + 2) * (wnew * exp(wnew) - input) / ((2 * wnew) + 2)));
        
        postComp = resizeArbtoString(wnew);
        
        i++;
    } while(preComp != postComp);
    
    std::cout << "\nW(" + inputStr + ") = " << wnew << "\n(rounded up to "
            << PRECISION << " digits, precise after " << i << " iterations)\n";

    return 0;
}

// Check input
bool isStringValid(const std::string & str){
    // Check if string contains spaces
    if(std::count(str.begin(), str.end(), ' ') > 0){
        std::cout << "\nError: Input contains spaces\n";
        return false;
    }
    
    // Check if string contains multiple .
    if(std::count(str.begin(), str.end(), '.') > 1){
        std::cout << "\nError: Input contains multiple decimal marks\n";
        return false;
    }
    
    // Check if NaN or Out of bounds (due to parsing failure)
    try{
        boost::lexical_cast<arbFloat>(str);
    } catch(std::runtime_error){
        std::cout << "\nError: Unable to parse (value too large or incorrect number type)\n";
        return false;
    } catch(...){
        std::cout << "\nError: Input is NaN\n";
        return false;
    }
    
    // Check if intentional NaN
    if(boost::icontains(str, "nan")){
        std::cout << "\nError: Intentional NaN\n";
        return false;
    }
    
    return true;
}

// Check number
bool isNumberValid(const arbFloat & x){
    // Check if result is imaginary
    if(x < 0){
        std::cout << "\nError: Complex result\n";
        return false;
    }
    
    // Range check
    if(x == std::numeric_limits<arbFloat>::infinity()){
        std::cout << "\nError: Input is out of bounds\n";
        return false;
    }
    
    return true;
}

// Convert to string and resize using correct precision
inline std::string resizeArbtoString(const arbFloat & x){
    std::string resizedStr = static_cast<std::string>(x);
    resizedStr.resize(PRECISION + 2);
    return resizedStr;
}
