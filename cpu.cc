#include "cpu.h"

cpu::cpu() {
    memset(registers, 0, sizeof(registers));
    memset(icache, 0, sizeof(icache));
    memset(dcache, 0, sizeof(dcache));
    memset(memory, 0, sizeof(memory));
}

void cpu::Fetch() {
    #ifdef _DEBUG
    std::cerr << "fetch" << std::endl;
    #endif
    fr.inst = icache[pc/4];
    pc+=4;
}

void cpu::Decode() {
    #ifdef _DEBUG
    std::cerr << "decode" << std::endl;
    #endif
    dr.opcode = OPCODE(get_opcode(fr.inst));
    switch (dr.opcode) {
    case R:
        dr.f3 = get_f3(fr.inst);
        dr.f7 = get_f7(fr.inst);
        dr.rd = get_rd(fr.inst);
        dr.rs1 = get_rs1(fr.inst);
        dr.rs2 = get_rs2(fr.inst);
        break;
    case IA:
        dr.f3 = get_f3(fr.inst);
        dr.f7 = get_f7(fr.inst);
        dr.imm = i_imm(fr.inst);
        dr.rd = get_rd(fr.inst);
        dr.rs1 = get_rs1(fr.inst);
        break;
    case IL:
        dr.f3 = get_f3(fr.inst);
        dr.imm = i_imm(fr.inst);
        dr.rd = get_rd(fr.inst);
        dr.rs1 = get_rs1(fr.inst);
        break;
    case S: 
        dr.f3 = get_f3(fr.inst);
        dr.imm = s_imm(fr.inst);
        dr.rs1 = get_rs1(fr.inst);
        dr.rs2 = get_rs2(fr.inst);
        break;
    case B:
        dr.f3 = get_f3(fr.inst);
        dr.imm = b_imm(fr.inst);
        dr.rs1 = get_rs1(fr.inst);
        dr.rs2 = get_rs2(fr.inst);
        break;
    case J:
        dr.imm = j_imm(fr.inst);
        dr.rd = get_rd(fr.inst);
        break;
    case JR:
        dr.imm = i_imm(fr.inst);
        dr.rd = get_rd(fr.inst);
        dr.rs1 = get_rs1(fr.inst);
        break;
    case U:
    case UP:
        dr.imm = u_imm(fr.inst);
        dr.rd = get_rd(fr.inst);
        break;
    case EI:
        dr.imm = i_imm(fr.inst);
        dr.rd = get_rd(fr.inst);
        dr.rs1 = get_rs1(fr.inst);
        break;
    default:
        throw std::runtime_error("Invalid opcode");
    }
}

void cpu::Execute() {
    #ifdef _DEBUG
    std::cerr << "execute" << std::endl;
    #endif
    switch (dr.opcode) {
        case R:
            switch (dr.f3) {
                case ADD_SUB:
                    if (dr.f7 == ADD) {
                        registers[dr.rd] = registers[dr.rs1] + registers[dr.rs2]; 
                    }
                    else if (dr.f7 == SUB) {
                        registers[dr.rd] = registers[dr.rs1] - registers[dr.rs2]; 
                    }
                    else throw std::runtime_error("ADD_SUB fail");
                    break;
                case XOR:
                    registers[dr.rd] = registers[dr.rs1] ^ registers[dr.rs2]; 
                    break;
                case OR:
                    registers[dr.rd] = registers[dr.rs1] | registers[dr.rs2]; 
                    break;
                case AND:
                    registers[dr.rd] = registers[dr.rs1] & registers[dr.rs2]; 
                    break;
                case SLL:
                    registers[dr.rd] = registers[dr.rs1] << registers[dr.rs2]; 
                    break;
                case SRL_SRA:
                    // have to do sign extension, will do later
                    registers[dr.rd] = registers[dr.rs1] >> registers[dr.rs2]; 
                    break;
                case SLT:
                    registers[dr.rd] = ((int32_t)registers[dr.rs1] < (int32_t)registers[dr.rs2]); 
                    break;
                case SLTU:
                    registers[dr.rd] = (registers[dr.rs1] < registers[dr.rs2]); 
                    break;
                default:
                    throw std::runtime_error("Invalid R-type funct3");
            }
            break;
        case IA:
            switch (dr.f3) {
                case ADDI:
                    registers[dr.rd] = registers[dr.rs1] + dr.imm; 
                    break;
                case XORI:
                    registers[dr.rd] = registers[dr.rs1] ^ dr.imm; 
                    break;
                case ORI:
                    registers[dr.rd] = registers[dr.rs1] | dr.imm; 
                    break;
                case ANDI:
                    registers[dr.rd] = registers[dr.rs1] & dr.imm; 
                    break;
                case SLLI:
                    registers[dr.rd] = registers[dr.rs1] << dr.imm; 
                    break;
                case SRLI_SRAI:
                    registers[dr.rd] = registers[dr.rs1] >> dr.imm; 
                    break;
                case SLTI:
                    registers[dr.rd] = ((int32_t)registers[dr.rs1] < (int32_t)dr.imm); 
                    break;
                case SLTIU:
                    registers[dr.rd] = (registers[dr.rs1] < dr.imm); 
                    break;
                default:
                    throw std::runtime_error("Invalid IA-type funct3");
            }
            break;
        case IL:
            switch (dr.f3) {
                case LB:
                    registers[dr.rd] = (memory[dr.imm + registers[dr.rs1]] & 0xF);
                    break;
                case LH:
                    registers[dr.rd] = (memory[dr.imm + registers[dr.rs1]] & 0xFFFF);

                    break;
                case LW:
                    registers[dr.rd] = (memory[dr.imm + registers[dr.rs1]] & 0xFFFFFFFF);

                    break;
                case LBU:
                    registers[dr.rd] = (memory[dr.imm + registers[dr.rs1]] & 0xF);
                    // have to do sign extension, will do later

                    break;
                case LHU:
                    registers[dr.rd] = (memory[dr.imm + registers[dr.rs1]] & 0xFFFF);
                    // have to do sign extension, will do later

                    break;
                default:
                    throw std::runtime_error("Invalid IL-type funct3");
            }
            break;
        case S:
            switch (dr.f3) {
                case SB:
                    memory[dr.imm + dr.rd] = (registers[dr.rs1] & 0xF);
                    break;
                case SH:
                    memory[dr.imm + dr.rd] = (registers[dr.rs1] & 0xFFFF);
                    break;
                case SW:
                    memory[dr.imm + dr.rd] = (registers[dr.rs1] & 0xFFFFFFFF);
                    break;
                default:
                    throw std::runtime_error("Invalid S-type funct3");
            }
            break;
        case B:
        // THESE SHOULD SEND HELLA CONTROL SIGNALS LATER!!!!
            switch (dr.f3) {
                case BEQ:
                    pc+=dr.imm*(registers[dr.rs1] == registers[dr.rs2]);
                    break;
                case BNE:
                    pc+=dr.imm*(registers[dr.rs1] != registers[dr.rs2]);
                    break;
                case BLT:
                    pc+=dr.imm*((int32_t)registers[dr.rs1] < (int32_t)registers[dr.rs2]);
                    break;
                case BGE:
                    pc+=dr.imm*((int32_t)registers[dr.rs1] >= (int32_t)registers[dr.rs2]);
                    break;
                case BLTU:
                    pc+=dr.imm*(registers[dr.rs1] < registers[dr.rs2]);
                    break;
                case BGEU:
                    pc+=dr.imm*(registers[dr.rs1] >= registers[dr.rs2]);
                    break;
                default:
                    throw std::runtime_error("Invalid B-type funct3");
            }
            break;
        case J:
            registers[dr.rd] = pc+4;
            pc+=dr.imm;
            break;
        case JR:
            switch (dr.f3) {
                case JALR:
                    registers[dr.rd] = pc+4;
                    pc+=dr.imm+registers[dr.rs1];
                    break;
                default:
                    throw std::runtime_error("Invalid JR-type funct3");
            }
            break;
        case U:
            registers[dr.rd] = (dr.imm << 12);
            break;
        case UP:
            registers[dr.rd] = (dr.imm << 12)+pc;
        case EI:
            switch (dr.imm) {
                case 0:
                    // ECALL
                    break;
                case 1:
                    // EBREAK (trap handler)
                    break;
                default:
                    throw std::runtime_error("Invalid ECALL/EBREAK   function");
            }
            break;
        default:
            throw std::runtime_error("ISSUE WITH DECODE!!!!!");
    }
    registers[0] = 0;
}

void cpu::Mem() {

}

void cpu::WB() {

}


void cpu::Reg_dump() {
    for (int i = 0; i < 32; ++i) {
        std::cout << "reg " << i << ": " << registers[i] << " | ";
        if (i%4 == 0) std::cout << '\n';
    }
}