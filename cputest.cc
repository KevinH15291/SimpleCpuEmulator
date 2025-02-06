#include <iostream>
#include <bitset>
#include "cpu.h" 

int main() {
    std::cout << std::bitset<32>(b_imm(0xfe0288e3)) << '\n' << b_imm(0xfe0288e3) << '\n';
    std::cout << std::bitset<32>(j_imm(0xfe0288e3)) << '\n' << j_imm(0x004000ef); 
}