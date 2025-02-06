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
    fr.inst = icache[pc];
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
                    else if (dr.f7 = SUB) {
                        registers[dr.rd] = registers[dr.rs1] - registers[dr.rs2]; 
                    }
                    else throw std::runtime_error("ADD_SUB fail");
                    break;
                case XOR:
                    // Process XOR instruction here
                    break;
                case OR:
                    // Process OR instruction here
                    break;
                case AND:
                    // Process AND instruction here
                    break;
                case SLL:
                    // Process SLL instruction here
                    break;
                case SRL_SRA:
                    break;
                case SLT:
                    // Process SLT instruction here
                    break;
                case SLTU:
                    // Process SLTU instruction here
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
                    // Process XORI instruction here
                    break;
                case ORI:
                    // Process ORI instruction here
                    break;
                case ANDI:
                    // Process ANDI instruction here
                    break;
                case SLLI:
                    // Process SLLI instruction here
                    break;
                case SRLI_SRAI:
                    // Process SRLI instruction here
                    // Process SRAI instruction here
                    break;
                case SLTI:
                    // Process SLTI instruction here
                    break;
                case SLTIU:
                    // Process SLTIU instruction here
                    break;
                default:
                    throw std::runtime_error("Invalid IA-type funct3");
            }
            break;
        case IL:
            switch (dr.f3) {
                case LB:
                    // Process LB instruction here
                    break;
                case LH:
                    // Process LH instruction here
                    break;
                case LW:
                    // Process LW instruction here
                    break;
                case LBU:
                    // Process LBU instruction here
                    break;
                case LHU:
                    // Process LHU instruction here
                    break;
                default:
                    throw std::runtime_error("Invalid IL-type funct3");
            }
            break;
        case S:
            switch (dr.f3) {
                case SB:
                    // Process SB instruction here
                    break;
                case SH:
                    // Process SH instruction here
                    break;
                case SW:
                    // Process SW instruction here
                    break;
                default:
                    throw std::runtime_error("Invalid S-type funct3");
            }
            break;
        case B:
            switch (dr.f3) {
                case BEQ:
                    // Process BEQ instruction here
                    break;
                case BNE:
                    // Process BNE instruction here
                    break;
                case BLT:
                    // Process BLT instruction here
                    break;
                case BGE:
                    // Process BGE instruction here
                    break;
                case BLTU:
                    // Process BLTU instruction here
                    break;
                case BGEU:
                    // Process BGEU instruction here
                    break;
                default:
                    throw std::runtime_error("Invalid B-type funct3");
            }
            break;
        case J:
            // Process J-type instruction here
            break;
        case JR:
            switch (dr.f3) {
                case JALR:
                    // Process JALR instruction here
                    break;
                default:
                    throw std::runtime_error("Invalid JR-type funct3");
            }
            break;
        case U:
            // Process U-type instruction here
            break;
        case EI:
            switch (dr.imm) {
                case 0:
                    // not done
                    break;
                case 1:
                    // not done
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

