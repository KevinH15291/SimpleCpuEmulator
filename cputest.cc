#include <iostream>
#include <bitset>
#include "cpu.cc" 

int main() {
    cpu mycpu;
    mycpu.icache[0] = 0x02028293;
    mycpu.Fetch();
    mycpu.Decode();
    mycpu.Execute();
    std::cout << mycpu.registers[5];
    std::cout << mycpu.registers[7];

    mycpu.icache[0] = 0x00528393;
    mycpu.Fetch();
    mycpu.Decode();
    mycpu.Execute();

    std::cout << mycpu.registers[5] << std::endl;
    std::cout << mycpu.registers[7];
}