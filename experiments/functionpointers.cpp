#include<iostream>
/**
 * @brief Function that adds two numbers.
 * 
 * @param a 
 * @param b 
 * @return int, the sum of a and b.
 */
int sum(int a, int b){
    return a + b;
}
/**
 * @brief Wanted to experiment with function pointers
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv){ 
    int (*buch)(int a, int b) = &sum; //we define function pointers via :  return_type (*function_name)(arguments) = &function
    std::cout<<buch(5,5)<<std::endl;
    return 0;
}