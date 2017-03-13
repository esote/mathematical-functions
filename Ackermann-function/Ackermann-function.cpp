#include <iostream>
#include <cmath>
#include <limits>

unsigned int ackermann(unsigned int m, unsigned int n){
    if(m == 0)
        return n+1;
    if(n == 0)
        return ackermann(m-1,1);
    return ackermann(m-1,ackermann(m,n-1));
}

enum var {M, N};
bool SOProtection;

bool isInvalidCheck(double i, var name){
    if(!std::cin){
        std::cout << "Non-number (NaN)\n";
        return true;
    }
    
    if(floor(i) != i){
        std::cout << "Non-integer (\u2124)\n";
        return true;
    }
    
    if(i < 0){
        std::cout << "Non-natural (\u2115)\n";
        return true;
    }
    
    if(name == M && i > 3 && SOProtection){
        std::cout << "Out of Bounds (m > 3) with SO Protection\n";
        return true;
    }
    
    if(name == N && i > 12 && SOProtection){
        std::cout << "Out of Bounds (n > 12) with SO Protection\n";
        return true;
    }
    
    return false;
}

bool isInvalid(double i, var name){
    bool result = isInvalidCheck(i, name);
    
    std::cin.clear();
    std::cin.ignore();
    
    return result;
}

int main(){
    double m, n;
    bool validM, validN;
    char checkSOProtection;
    
    std::cout << "Warning: If large values are entered, stack overflow and segmentation fault will occur!\n";
    
    while(true){
        std::cout << "Enable stack overflow protection? Y/N: ";
        std::cin >> checkSOProtection;
        
        if(checkSOProtection == 'Y' || checkSOProtection == 'y'){
            SOProtection = true;
            break;
        }
        
        if(checkSOProtection == 'N' || checkSOProtection == 'n'){
            SOProtection = false;
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    do{
        std::cout << "\nm = ";
        std::cin >> m;
        validM = isInvalid(m, M);
    } while(validM);
    
    do{
        std::cout << "\nn = ";
        std::cin >> n;
        validN = isInvalid(n, N);
    } while(validN);
    
    std::cout << "\nCALCULATING" << std::endl;
    
    std::cout << "\nA(" << m << ',' << n << ") = "
            << ackermann(m,n) << std::endl;
    
    return 0;
}
