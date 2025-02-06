#include <iostream>
#include <bitset>
#include "cpu.cc" 

int main() {
    cpu mycpu;
    uint32_t insts[] = {0x02028293, 
                        0x00530313,
                        0x006283b3,
                        0x40538333,
                        0x00631333,
                        0x00231313};
    for (int i = 0; i < 6; ++i) {
        mycpu.icache[i] = insts[i];
        mycpu.Fetch();
        mycpu.Decode();
        mycpu.Execute();
        mycpu.Reg_dump();
    }

   
}