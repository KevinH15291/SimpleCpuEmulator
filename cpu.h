#pragma once

#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <stdexcept>

using inst = uint32_t;

// enum INSTS {
// };

enum OPCODE : uint32_t {
    R  = 0b0110011,
    IA = 0b0010011,
    IL = 0b0000011,
    S  = 0b0100011,
    B  = 0b1100011,
    J  = 0b1101111,
    JR = 0b1100111,
    U  = 0b0110111,
    UP = 0b0010111,
    EI = 0b1110011
};

enum F3 : uint32_t {
    // R
    ADD_SUB = 0x0,
    XOR    = 0x4,
    OR     = 0x6,
    AND    = 0x7,
    SLL    = 0x1,
    SRL_SRA = 0x5,

    SLT    = 0x2,
    SLTU   = 0x3,
    // IA
    ADDI   = 0x0,
    XORI   = 0x4,
    ORI    = 0x6,
    ANDI   = 0x7,
    SLLI   = 0x1,
    SRLI_SRAI   = 0x5,
    SLTI   = 0x2,
    SLTIU  = 0x3,
    // IL
    LB     = 0x0,
    LH     = 0x1,
    LW     = 0x2,
    LBU    = 0x4,
    LHU    = 0x5,
    // S
    SB     = 0x0,
    SH     = 0x1,
    SW     = 0x2,
    // B
    BEQ    = 0x0,
    BNE    = 0x1,
    BLT    = 0x4,
    BGE    = 0x5,
    BLTU   = 0x6,
    BGEU   = 0x7,
    // JR
    JALR   = 0x0,
    // EI
    ECALL  = 0x0,
    EBREAK = 0x0
};


enum F7 : uint32_t {
    ADD = 0x0,
    SUB = 0x20,
    SRL = 0x0,
    SRA = 0x20
};


int32_t i_imm (inst i);
int32_t s_imm (inst i);
int32_t b_imm (inst i);
int32_t u_imm (inst i);
int32_t j_imm (inst i);

class cpu {
    public:
        cpu();
        void Fetch();
        void Decode();
        void Execute();
        void Mem();
        void WB();
        void Reg_dump();
        
    uint32_t registers[32];
    uint32_t pc = 0;
    uint32_t icache[512];
    uint32_t dcache[512]; // this ain't happening for awhile
    uint32_t memory[4096];

    struct fetch_register {
        uint32_t inst;
        uint32_t error_flags = 0;
    };
    fetch_register fr;

    struct decode_register {
        OPCODE opcode;
        uint32_t rs1, rs2, rd;
        F3 f3;
        F7 f7;
        uint32_t imm;
        uint32_t error_flags = 0;
    };
    decode_register dr;

    struct execute_register {
        uint32_t inst;
        uint32_t error_flags = 0;
    };
    execute_register er;

    // struct mem_register {
    //     uint32_t inst;
    //     uint32_t error_flags = 0;
    // };
    // mem_register mem;
    
};

int32_t get_opcode (inst i) {
    return (i & 0x7F);
} 

int32_t i_imm (inst i) {
    return (i >> 20);
}
int32_t s_imm (inst i) {
    return ((i << 11) >> 27);
}
int32_t b_imm (inst i) {
    return  ((((i >> 7) & 0x1E)  | 
              ((i >> 20) & 0x7E0) | 
              ((i & 0x00000080) >> 20) | 
              ((i & 0xEFFFFFFF) >> 20)) & 
              ((1U << 12) - 1) ^ 0x800) - 0x800;
}

int32_t u_imm (inst i) {
    return (i & 0xFFFFF000);
}

int32_t j_imm (inst i) {
    return ((((i >> 20) & 0xEFE) |
             ((i >> 9) & 0x000200) |
             ((i & 0xFF00)) |
             ((i  >> 12) & 0x80000))& 
             ((1U << 12) - 1) ^ 0x800) - 0x800;
}

int32_t get_rs1 (inst i) {
    return (i >> 15) & 0x1F;
}

int32_t get_rs2 (inst i) {
    return (i >> 20) & 0x1F;
}

int32_t get_rd (inst i) {
    return (i >> 7) & 0x1F;
}

F3 get_f3 (inst i) {
    return F3((i >> 12) & 0x7);
}
F7 get_f7 (inst i) {
    return F7(i >> 25);
}