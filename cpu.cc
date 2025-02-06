#include "cpu.h"


int32_t 
cpu::cpu() {
    memset(registers, 0, sizeof(registers));
    memset(icache, 0, sizeof(icache));
    memset(dcache, 0, sizeof(dcache));
    memset(memory, 0, sizeof(memory));
}

void cpu::fetch() {
    icache[pc];
}

void cpu::decode() {
    switch ( ((fr.inst << 25) >> 25) ) {
        case R:
            dr.opcode = R;
            break;
        case IA:
            dr.opcode = IA;
            break;
        case S:
            dr.opcode = S;
            break;
        case B:
            dr.opcode = B;
            break;
        case J:
            dr.opcode = J;
            break;
        case I:
            dr.opcode = I;
            break;
        case U:
            dr.opcode = U;
            break;
        case EI:
            dr.opcode = EI;
            break;
    }
    
}

void cpu::execute() {

}

void cpu::mem() {

}

void cpu::wb() {

}
