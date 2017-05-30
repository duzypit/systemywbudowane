/*
 * @author Tomasz Piątek
 * @brief Class 7-points Write a class to handle a file with all constructors, destructor, operators... (C++11 recommended)
 */
#include <iostream>

int main() {
    File f {"/tmp/aa", O_WRONLY | O_APPEND}; 

    File f2 { f } ; 

    File f3 = f2; 

    File f4; 

    f = f3; 
}