#include <iostream>
#include "arithmetics.h"

void printError(int s, int m){
    std::cout << "Unexpected error:\nsum is: " << s << "\nmul is: " << m << '\n';
}

void printSuccess(){
    std::cout << "OK";
}

int main() {
    int x, y;
    std::cin >> x >> y;
    int s = sum(x, y);
    int m = mul(x, y);
    if(s == x + y && m == x * y){
        printSuccess();
    }
    else{
        printError(s, m);
    }
}
