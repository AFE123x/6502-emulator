#include<iostream>
#include<cstdint>
/**
 * @brief This is an experimental file containing bitshift 
 * calculations to ensure mistakes aren't made
 * @return int 
 */
int main(){
    uint8_t test = 0x44;
    uint8_t test1 = 0x45;
    //0000000100000000
    std::cout<<static_cast<int>((test1) | (test<<8))<<"vs."<<0x4445<<std::endl;
    return 0;
}