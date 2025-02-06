#pragma once

#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <cstring>
using inst = uint32_t;
enum INSTS {

};
enum OPCODE {
    R = 0b0110011,
    IA = 0b0010011,
    IL = 0b0000011,
    S = 0b0100011,
    B = 0b1100011,
    J = 0b1101111,
    I = 0b1100111,
    U = 0b0110111,
    EI = 0b1110011
};
int32_t i_imm (inst i);
int32_t s_imm (inst i);
int32_t b_imm (inst i);
int32_t u_imm (inst i);
int32_t j_imm (inst i);

class cpu {
    public:
        cpu();
        void fetch();
        void decode();
        void execute();
        void mem();
        void wb();
        
    private:
    uint32_t registers[32];
    uint32_t pc;
    uint32_t icache[512];
    uint32_t dcache[512];
    uint32_t memory[4096];

    struct fetch_register {
        uint32_t inst;
        uint32_t error_flags;
    };

    fetch_register fr;
    struct decode_register {
        OPCODE opcode;
        uint32_t error_flags;
    };

    decode_register dr;
    struct execute_register {
        uint32_t inst;
        uint32_t error_flags;
    };

    struct mem_register {
        uint32_t inst;
        uint32_t error_flags;
    };
};

int32_t i_imm (inst i) {
    return (i >> 20);
}
int32_t s_imm (inst i) {
    return ((i << 11) >> 27);
}
int32_t b_imm (inst i) {
    return  ((((i >> 7) & 0x00000F00)  | 
            ((i >> 20) & 0x7E0) | 
            ((i & 0x00000080) >> 20) | 
            ((i & 0xEFFFFFFF) >> 20)) & 
            ((1U << 12) - 1) ^ 0x800) - 0x800;
}
int32_t u_imm (inst i) {
    return (i & 0xFFFFF000);
}

int32_t j_imm (inst i) {
    return (((i & 0xEFE00000) >> 20) |
            ((i & 0x00010000) >> 9) |
            ((i & 0x0000FF00)) |
            ((i & 0x80000000) >> 12) 
            );
}