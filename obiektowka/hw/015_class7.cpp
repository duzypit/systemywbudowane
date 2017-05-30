/*
 * @author Tomasz Piątek
 * @brief Class 2-points Fix a class using initializer list(C++11 recommended)
 */
#include <iostream>

int main() {
    File f {"/tmp/aa", O_WRONLY | O_APPEND}; 

    File f2 { f } ; 

    File f3 = f2; 

    File f4; 

    f = f3; 
}