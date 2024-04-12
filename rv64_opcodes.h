
typedef enum {
    /* RV32I */
    inst_lui = 3,   // arbitrary, but non-zero
    inst_auipc,
    inst_jal,
    inst_jalr,
    inst_beq,
    inst_bne,
    inst_blt,
    inst_bge,
    inst_bltu,
    inst_bgeu,
    inst_lb,
    inst_lh,
    inst_lw,
    inst_lbu,
    inst_lhu,
    inst_sb,
    inst_sh,
    inst_sw,
    inst_addi,
    inst_slti,
    inst_sltiu,
    inst_xori,
    inst_ori,
    inst_andi,
    inst_slli,
    inst_srli,
    inst_srai,
    inst_add,
    inst_sub,
    inst_sll,
    inst_slt,
    inst_sltu,
    inst_xor,
    inst_srl,
    inst_sra,
    inst_or,
    inst_and,
    inst_fence,
    inst_ecall,
    inst_ebreak,
    /* RV64I */
    inst_lwu,
    inst_ld,
    inst_sd,
    inst_addiw,
    inst_slliw,
    inst_srliw,
    inst_sraiw,
    inst_addw,
    inst_subw,
    inst_sllw,
    inst_srlw,
    inst_sraw,
    /* RV64 Zifencei */
    inst_fencei,
    /* RV64 Zicsr */
    inst_csrrw,
    inst_csrrs,
    inst_csrrc,
    inst_csrrwi,
    inst_csrrsi,
    inst_csrrci,
    /* RV32M */
    inst_mul,
    inst_mulh,
    inst_mulhsu,
    inst_mulhu,
    inst_div,
    inst_divu,
    inst_rem,
    inst_remu,
    /* RV64M */
    inst_mulw,
    inst_divw,
    inst_divuw,
    inst_remw,
    inst_remuw,
    /* RV32A */
    inst_lrw,
    inst_scw,
    inst_amoswapw,
    inst_amoaddw,
    inst_amoxorw,
    inst_amoandw,
    inst_amoorw,
    inst_amominw,
    inst_amomaxw,
    inst_amominuw,
    inst_amomaxuw,
    /* RV64A */
    inst_lrd,
    inst_scd,
    inst_amoswapd,
    inst_amoaddd,
    inst_amoxord,
    inst_amoandd,
    inst_amoord,
    inst_amomind,
    inst_amomaxd,
    inst_amominud,
    inst_amomaxud,
    /* RV32F */
    inst_flw,
    inst_fsw,
    inst_fmadds,
    inst_fmsubs,
    inst_fnmsubs,
    inst_fnmadds,
    inst_fadds,
    inst_fsubs,
    inst_fmuls,
    inst_fdivs,
    inst_fsqrts,
    inst_fsgnjs,
    inst_fsgnjns,
    inst_fsgnjxs,
    inst_fmins,
    inst_fmaxs,
    inst_fcvtws,
    inst_fcvtwus,
    inst_fmvxw,
    inst_feqs,
    inst_flts,
    inst_fles,
    inst_fclasss,
    inst_fcvtsw,
    inst_fcvtswu,
    inst_fmvwx,
    /* RV64F */
    inst_fcvtls,
    inst_fcvtlus,
    inst_fcvtsl,
    inst_fcvtslu,
    /* RV32D */
    inst_fld,
    inst_fsd,
    inst_fmaddd,
    inst_fmsubd,
    inst_fnmsubd,
    inst_fnmaddd,
    inst_faddd,
    inst_fsubd,
    inst_fmuld,
    inst_fdivd,
    inst_fsqrtd,
    inst_fsgnjd,
    inst_fsgnjnd,
    inst_fsgnjxd,
    inst_fmind,
    inst_fmaxd,
    inst_fcvtsd,
    inst_fcvtds,
    inst_feqd,
    inst_fltd,
    inst_fled,
    inst_fclassd,
    inst_fcvtwd,
    inst_fcvtwud,
    inst_fcvtdw,
    inst_fcvtdwu,
    /* RV64D */
    inst_fcvtld,
    inst_fcvtlud,
    inst_fmvxd,
    inst_fcvtdl,
    inst_fcvtdlu,
    inst_fmvdx
} sane_mnemonics_t;


/* OPCODE MAP */
/* Not too many actual opcodes, most of the action 
 * is in the various function codes. */
#define RV64_OP_LOAD     0x03    /* 0000011 */
#define RV64_OP_LOAD_FP  0x07    /* 0000111 */
#define RV64_OP_MISC_MEM 0x0f    /* 0001111 */
#define RV64_OP_OP_IMM   0x13    /* 0010011 */
#define RV64_OP_AUIPC    0x17    /* 0010111 */
#define RV64_OP_OP_IMM32 0x1b    /* 0011011 */
#define RV64_OP_STORE    0x23    /* 0100011 */
#define RV64_OP_STORE_FP 0x27    /* 0100111 */
#define RV64_OP_AMO      0x2f    /* 0101111 */
#define RV64_OP_OP       0x33    /* 0110011 */
#define RV64_OP_LUI      0x37    /* 0110111 */
#define RV64_OP_OP32     0x3b    /* 0111011 */
#define RV64_OP_MADD     0x43    /* 1000011 */
#define RV64_OP_MSUB     0x47    /* 1000111 */
#define RV64_OP_NMSUB    0x4b    /* 1001011 */
#define RV64_OP_NMADD    0x4f    /* 1001111 */
#define RV64_OP_FP       0x53    /* 1010011 */
#define RV64_OP_BRANCH   0x63    /* 1100011 */
#define RV64_OP_JALR     0x67    /* 1100111 */
#define RV64_OP_JAL      0x6f    /* 1101111 */
#define RV64_OP_SYSTEM   0x73    /* 1110011 */

/* --------------------RV32I-------------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_JALR   0x0
#define RV64_FUNCT3_BEQ    0x0
#define RV64_FUNCT3_BNE    0x1
#define RV64_FUNCT3_BLT    0x4
#define RV64_FUNCT3_BGE    0x5
#define RV64_FUNCT3_BLTU   0x6
#define RV64_FUNCT3_BGEU   0x7

#define RV64_FUNCT3_LB     0x0
#define RV64_FUNCT3_LH     0x1
#define RV64_FUNCT3_LW     0x2
#define RV64_FUNCT3_LBU    0x4
#define RV64_FUNCT3_LHU    0x5

#define RV64_FUNCT3_SB     0x0
#define RV64_FUNCT3_SH     0x1
#define RV64_FUNCT3_SW     0x2

#define RV64_FUNCT3_ADDI   0x0
#define RV64_FUNCT3_SLTI   0x2
#define RV64_FUNCT3_SLTIU  0x3
#define RV64_FUNCT3_XORI   0x4
#define RV64_FUNCT3_ORI    0x6
#define RV64_FUNCT3_ANDI   0x7

#define RV64_FUNCT3_SLLI   0x1 // see note below about shift-imm instructions
#define RV64_FUNCT3_SRLI   0x5 
#define RV64_FUNCT3_SRAI   0x5

#define RV64_FUNCT3_ADD    0x0
#define RV64_FUNCT3_SUB    0x0
#define RV64_FUNCT3_SLL    0x1
#define RV64_FUNCT3_SLT    0x2
#define RV64_FUNCT3_SLTU   0x3
#define RV64_FUNCT3_XOR    0x4
#define RV64_FUNCT3_SRL    0x5
#define RV64_FUNCT3_SRA    0x5
#define RV64_FUNCT3_OR     0x6
#define RV64_FUNCT3_AND    0x7

#define RV64_FUNCT3_FENCE  0x0
#define RV64_FUNCT3_ECALL  0x0
#define RV64_FUNCT3_EBREAK 0x0

/* FUNCT7 CODES */
#define RV64_FUNCT7_ADD    0x00
#define RV64_FUNCT7_SUB    0x20
#define RV64_FUNCT7_SLL    0x00
#define RV64_FUNCT7_SLT    0x00
#define RV64_FUNCT7_SLTU   0x00
#define RV64_FUNCT7_XOR    0x00
#define RV64_FUNCT7_SRL    0x00
#define RV64_FUNCT7_SRA    0x20
#define RV64_FUNCT7_OR     0x00
#define RV64_FUNCT7_AND    0x00

/* FUNCT12 CODES */
#define RV64_FUNCT12_ECALL   0x000
#define RV64_FUNCT12_EBREAK  0x001


/* --------------------RV64I-------------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_LWU    0x6
#define RV64_FUNCT3_LD     0x3
#define RV64_FUNCT3_SD     0x3
#define RV64_FUNCT3_ADDIW  0x0
#define RV64_FUNCT3_SLLIW  0x1
#define RV64_FUNCT3_SRLIW  0x5
#define RV64_FUNCT3_SRAIW  0x5
#define RV64_FUNCT3_ADDW   0x0
#define RV64_FUNCT3_SUBW   0x0
#define RV64_FUNCT3_SLLW   0x1
#define RV64_FUNCT3_SRLW   0x5
#define RV64_FUNCT3_SRAW   0x5

/* IMM SHIFT CODES (FUNCT6) */
/* This field is 7 bits in RV32I, but only 6 in RV64I, to
 * account for a wider shamt. So for our VM, it's not 
 * possible to get a 7 bit function code, as defined in 
 * RV32I, which is why these codes didn't get defined in 
 * the RV32I section above. */
#define RV64_SHIFT_IMM_SLLI  0x00
#define RV64_SHIFT_IMM_SRLI  0x00
#define RV64_SHIFT_IMM_SRAI  0x10
#define RV64_SHIFT_IMM_SLLIW 0x00

/* FUNCT7 CODES */
#define RV64_FUNCT7_SLLIW  0x00
#define RV64_FUNCT7_SRLIW  0x00
#define RV64_FUNCT7_SRAIW  0x20
#define RV64_FUNCT7_ADDW   0x00
#define RV64_FUNCT7_SUBW   0x20
#define RV64_FUNCT7_SLLW   0x00
#define RV64_FUNCT7_SRLW   0x00
#define RV64_FUNCT7_SRAW   0x20

/* --------------------RV64Zifencei------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_FENCEI 0x1

/* --------------------RV64Zicsr---------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_CSRRW  0x1
#define RV64_FUNCT3_CSRRS  0x2
#define RV64_FUNCT3_CSRRC  0x3
#define RV64_FUNCT3_CSRRWI 0x5
#define RV64_FUNCT3_CSRRSI 0x6
#define RV64_FUNCT3_CSRRCI 0x7

/* --------------------RV32M-------------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_MUL    0x0
#define RV64_FUNCT3_MULH   0x1
#define RV64_FUNCT3_MULHSU 0x2
#define RV64_FUNCT3_MULHU  0x3
#define RV64_FUNCT3_DIV    0x4
#define RV64_FUNCT3_DIVU   0x5
#define RV64_FUNCT3_REM    0x6
#define RV64_FUNCT3_REMU   0x7

/* FUNCT7 CODES */
#define RV64_FUNCT7_MUL    0x01
#define RV64_FUNCT7_MULH   0x01
#define RV64_FUNCT7_MULHSU 0x01
#define RV64_FUNCT7_DIV    0x01
#define RV64_FUNCT7_DIVU   0x01
#define RV64_FUNCT7_REM    0x01
#define RV64_FUNCT7_REMU   0x01

/* --------------------RV64M-------------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_MULW   0x0
#define RV64_FUNCT3_DIVW   0x4
#define RV64_FUNCT3_DIVUW  0x5
#define RV64_FUNCT3_REMW   0x6
#define RV64_FUNCT3_REMUW  0x7

/* --------------------RV32A-------------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_LRW        0x2
#define RV64_FUNCT3_SCW        0x2
#define RV64_FUNCT3_AMOSWAPW   0x2
#define RV64_FUNCT3_AMOADDW    0x2
#define RV64_FUNCT3_AMOXORW    0x2
#define RV64_FUNCT3_AMOANDW    0x2
#define RV64_FUNCT3_AMOORW     0x2
#define RV64_FUNCT3_AMOMINW    0x2
#define RV64_FUNCT3_AMOMAXW    0x2
#define RV64_FUNCT3_AMOMINUW   0x2
#define RV64_FUNCT3_AMOMAXUW   0x2

/* FUNCT5 CODES */
/* We won't need the aq or rl bit positions, so I 
 * shortened the funct7 to 5 bits in these constants,
 * let's call the field funct5. */
#define RV64_FUNCT5_LRW        0x02
#define RV64_FUNCT5_SCW        0x03
#define RV64_FUNCT5_AMOSWAPW   0x01
#define RV64_FUNCT5_AMOADDW    0x00
#define RV64_FUNCT5_AMOXORW    0x04
#define RV64_FUNCT5_AMOANDW    0x0c
#define RV64_FUNCT5_AMOORW     0x08
#define RV64_FUNCT5_AMOMINW    0x10
#define RV64_FUNCT5_AMOMAXW    0x14
#define RV64_FUNCT5_AMOMINUW   0x18
#define RV64_FUNCT5_AMOMAXUW   0x1c

/* --------------------RV64A-------------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_LRD        0x3
#define RV64_FUNCT3_SCD        0x3
#define RV64_FUNCT3_AMOSWAPD   0x3
#define RV64_FUNCT3_AMOADDD    0x3
#define RV64_FUNCT3_AMOXORD    0x3
#define RV64_FUNCT3_AMOANDD    0x3
#define RV64_FUNCT3_AMOORD     0x3
#define RV64_FUNCT3_AMOMIND    0x3
#define RV64_FUNCT3_AMOMAXD    0x3
#define RV64_FUNCT3_AMOMINUD   0x3
#define RV64_FUNCT3_AMOMAXUD   0x3

/* FUNCT5 CODES */
/* See note above for RV32A about shortening the 
 * funct7 field to only 5 bits in these constants. */
#define RV64_FUNCT5_LRD        0x02
#define RV64_FUNCT5_SCD        0x03
#define RV64_FUNCT5_AMOSWAPD   0x01
#define RV64_FUNCT5_AMOADDD    0x00
#define RV64_FUNCT5_AMOXORD    0x04
#define RV64_FUNCT5_AMOANDD    0x0c
#define RV64_FUNCT5_AMOORD     0x08
#define RV64_FUNCT5_AMOMIND    0x10
#define RV64_FUNCT5_AMOMAXD    0x14
#define RV64_FUNCT5_AMOMINUD   0x18
#define RV64_FUNCT5_AMOMAXUD   0x1c

/* --------------------RV32F-------------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_FLW        0x2
#define RV64_FUNCT3_FSW        0x2
#define RV64_FUNCT3_FSGNJS     0x0
#define RV64_FUNCT3_FSGNJNS    0x1
#define RV64_FUNCT3_FSGNJXS    0x2
#define RV64_FUNCT3_FMINS      0x0
#define RV64_FUNCT3_FMAXS      0x1
#define RV64_FUNCT3_FMVXW      0x0
#define RV64_FUNCT3_FEQS       0x2
#define RV64_FUNCT3_FLTS       0x1
#define RV64_FUNCT3_FLES       0x0
#define RV64_FUNCT3_FCLASSS    0x1
#define RV64_FUNCT3_FMVWX      0x0

/* FUNCT2 CODES */
#define RV64_FUNCT2_FMADDS     0x0
#define RV64_FUNCT2_FMSUBS     0x0
#define RV64_FUNCT2_FNMSUBS    0x0
#define RV64_FUNCT2_FNMADDS    0x0

/* FUNCT7 CODES */
#define RV64_FUNCT7_FADDS      0x00
#define RV64_FUNCT7_FSUBS      0x00
#define RV64_FUNCT7_FMULS      0x08
#define RV64_FUNCT7_FDIVS      0x0c
#define RV64_FUNCT7_FSQRTS     0x2c
#define RV64_FUNCT7_FSGNJS     0x10
#define RV64_FUNCT7_FSGNJNS    0x10
#define RV64_FUNCT7_FSGNJXS    0x10
#define RV64_FUNCT7_FMINS      0x14
#define RV64_FUNCT7_FMAXS      0x14
#define RV64_FUNCT7_FCVTWS     0x60
#define RV64_FUNCT7_FCVTWUS    0x60
#define RV64_FUNCT7_FMVXW      0x70
#define RV64_FUNCT7_FEQS       0x50
#define RV64_FUNCT7_FLTS       0x50
#define RV64_FUNCT7_FLES       0x50
#define RV64_FUNCT7_FCLASSS    0x70
#define RV64_FUNCT7_FCVTSW     0x68
#define RV64_FUNCT7_FCVTSWU    0x68
#define RV64_FUNCT7_FMVWX      0x78

/* FUNCT5 CODES */
/* Bits position 24...20 for a handful of instructions, 
 * yet another "specialization" of one of the normal 
 * instruction formats. */
#define RV64_FUNCT5_FSQRTS     0x00
#define RV64_FUNCT5_FCVTWS     0x00
#define RV64_FUNCT5_FCVTWUS    0x01
#define RV64_FUNCT5_FMVXW      0x00
#define RV64_FUNCT5_FCLASSS    0x00
#define RV64_FUNCT5_FCVTSW     0x00
#define RV64_FUNCT5_FCVTSWU    0x01
#define RV64_FUNCT5_FMVWX      0x00

/* --------------------RV64F-------------------- */
/* FUNCT7 CODES */
#define RV64_FUNCT7_FCVTLS     0x60
#define RV64_FUNCT7_FCVTLUS    0x60
#define RV64_FUNCT7_FCVTSL     0x68
#define RV64_FUNCT7_FCVTSLU    0x68

/* FUNCT5 CODES */
/* See note about funct5 for RV32F above. */
#define RV64_FUNCT5_FCVTLS     0x02
#define RV64_FUNCT5_FCVTLUS    0x03
#define RV64_FUNCT5_FCVTSL     0x02
#define RV64_FUNCT5_FCVTSLU    0x03

/* --------------------RV32D-------------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_FLD        0x03
#define RV64_FUNCT3_FSD        0x03
#define RV64_FUNCT3_FSGNJD     0x00
#define RV64_FUNCT3_FSGNJND    0x01
#define RV64_FUNCT3_FSGNJNX    0x02
#define RV64_FUNCT3_FMIND      0x00
#define RV64_FUNCT3_FMAXD      0x01
#define RV64_FUNCT3_FEQD       0x02
#define RV64_FUNCT3_FLTD       0x01
#define RV64_FUNCT3_FLED       0x00
#define RV64_FUNCT3_FCLASSD    0x01

/* FUNCT2 CODES */
#define RV64_FUNCT3_FMADDD     0x1
#define RV64_FUNCT3_FMSUBD     0x1
#define RV64_FUNCT3_FNMSUBD    0x1
#define RV64_FUNCT3_FNMADDD    0x1

/* FUNCT7 CODES */
#define RV64_FUNCT7_FADDD      0x01
#define RV64_FUNCT7_FSUBD      0x05
#define RV64_FUNCT7_FMULD      0x09
#define RV64_FUNCT7_FDIVD      0x0d
#define RV64_FUNCT7_FSQRTD     0x0d
#define RV64_FUNCT7_FSGNJD     0x11
#define RV64_FUNCT7_FSGNJND    0x11
#define RV64_FUNCT7_FSGNJXD    0x11
#define RV64_FUNCT7_FMIND      0x15
#define RV64_FUNCT7_FMAXD      0x15
#define RV64_FUNCT7_FCVTSD     0x20
#define RV64_FUNCT7_FCVTDS     0x21
#define RV64_FUNCT7_FEQD       0x51
#define RV64_FUNCT7_FLTD       0x51
#define RV64_FUNCT7_FLED       0x51
#define RV64_FUNCT7_FCLASSD    0x71
#define RV64_FUNCT7_FCVTWD     0x61
#define RV64_FUNCT7_FCVTWUD    0x61
#define RV64_FUNCT7_FCVTDW     0x69
#define RV64_FUNCT7_FCVTDWU    0x69

/* FUNCT5 CODES */
/* See note about funct5 for RV32F above. */
#define RV64_FUNCT5_FSQRTD     0x00
#define RV64_FUNCT5_FCVTSD     0x01
#define RV64_FUNCT5_FCVTDS     0x00
#define RV64_FUNCT5_FCLASSD    0x00
#define RV64_FUNCT5_FCVTWD     0x00
#define RV64_FUNCT5_FCVTWUD    0x01
#define RV64_FUNCT5_FCVTDW     0x00
#define RV64_FUNCT5_FCVTDWU    0x01

/* --------------------RV64D-------------------- */
/* FUNCT3 CODES */
#define RV64_FUNCT3_FMVXD      0x0
#define RV64_FUNCT3_FMVDX      0x0

/* FUNCT7 CODES */
#define RV64_FUNCT7_FCVTLD     0x61
#define RV64_FUNCT7_FCVTLUD    0x61
#define RV64_FUNCT7_FCVTXD     0x71
#define RV64_FUNCT7_FCVTDL     0x69
#define RV64_FUNCT7_FCVTDLU    0x69
#define RV64_FUNCT7_FCVTDX     0x79

/* FUNCT5 CODES */
/* See note about funct5 for RV32F above. */
#define RV64_FUNCT5_FCVTLD     0x02
#define RV64_FUNCT5_FCVTLUD    0x03
#define RV64_FUNCT5_FCVTXD     0x00
#define RV64_FUNCT5_FCVTDL     0x02
#define RV64_FUNCT5_FCVTDLU    0x03
#define RV64_FUNCT5_FCVTDX     0x00

