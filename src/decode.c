#include "decode.h"
#include "memory.h"
#include "register_file.h"
#include <stdio.h>
#include <stdint.h>
#include "inst_type.h"
#include "rv64_opcodes.h"
#include "rv64_syscall.h"
#include <assert.h>
#include <fcntl.h>
#include "elf_helper.h"

int inst_count = 0;

void decode_loop(uint64_t PC)
{
    while(PC)
    {
        inst_t instruction;
        instruction.instruction = read_word(PC);
        PC = dispatch(instruction, PC);
        inst_count++;
    }
}

int dispatch(inst_t instruction, uint64_t PC)
{
    pretty_print(instruction, PC);
    switch(instruction.encoding.opcode)
    {
        case RV64_OP_LOAD:
            switch (instruction.i_type.funct3) {
                case RV64_FUNCT3_LB  :
                    assert(0 && "RV64_OP_LOAD - LB\n");
                    return; //0x0
                case RV64_FUNCT3_LH  :
                    assert(0 && "RV64_OP_LOAD - LH\n");
                    return; //0x1
                case RV64_FUNCT3_LW  :
                    write_reg_long(instruction.i_type.rd, read_word(read_reg_long(instruction.i_type.rs1) + i_imm(instruction.i_type)));
                    return PC + 4; //0x2
                case RV64_FUNCT3_LBU :
                    write_reg_long(instruction.i_type.rd, read_byte(read_reg_long(instruction.i_type.rs1) + i_imm(instruction.i_type)));
                    return PC + 4; //0x4
                case RV64_FUNCT3_LHU :
                    write_reg_long(instruction.i_type.rd, read_half(read_reg_long(instruction.i_type.rs1) + i_imm(instruction.i_type)));
                    return PC + 4; //0x5
                case RV64_FUNCT3_LWU :
                    assert(0 && "RV64_OP_LOAD - LWU\n");
                    return; //0x6

                case RV64_FUNCT3_LD  :
                    write_reg_long(instruction.i_type.rd, read_double_word(read_reg_long(instruction.i_type.rs1) + i_imm(instruction.i_type)));
                    return PC + 4; //0x3

            }
            return 0; //0x03    /* 0000011 */

        case RV64_OP_LOAD_FP:
            assert(0 && "LOAD FP");
            return 0; //0x07    /* 0000111 */
        case RV64_OP_MISC_MEM:
            switch (instruction.i_type.funct3)
            {
                case RV64_FUNCT3_FENCE:
                    return PC + 4;
                default:
                    printf("\n");
                    assert(0 && "UNKNOWN MISC_MEM");
            }
            assert(0 && "RV64_OP_MISC_MEM\n");
            return 0; //0x0f    /* 0001111 */

        case RV64_OP_OP_IMM:
            switch(instruction.i_type.funct3) {
                case RV64_FUNCT3_ADDI :
                    write_reg_long(instruction.i_type.rd,
                                   read_reg_long(instruction.i_type.rs1) + i_imm(instruction.i_type));
                    return PC + 4;// 0x0

                case RV64_FUNCT3_SLTI :
                    assert(0 && "RV64_OP_OP_IMM - SLTI\n");
                    return;// 0x2
                case RV64_FUNCT3_SLTIU:
                    assert(0 && "RV64_OP_OP_IMM - SLTIU\n");
                    return;// 0x3
                case RV64_FUNCT3_XORI :
                    write_reg_long(instruction.i_type.rd,
                                   read_reg_long(instruction.i_type.rs1) ^ i_imm(instruction.i_type));
                    return PC + 4;// 0x0
                case RV64_FUNCT3_ORI  :
                    assert(0 && "RV64_OP_OP_IMM - ORI\n");
                    return;// 0x6

                case RV64_FUNCT3_ANDI :
                    write_reg_long(instruction.i_type.rd,
                                   read_reg_long(instruction.i_type.rs1) & i_imm(instruction.i_type));
                    return PC + 4;// 0x7

                case RV64_FUNCT3_SLLI :
                    write_reg_long(instruction.is_type.rd, read_reg_long(instruction.is_type.rs1) << is_imm_64(instruction.is_type));
                    return PC + 4;
                case RV64_FUNCT3_SRLI :
                    write_reg_long(instruction.is_type.rd, read_reg_long(instruction.is_type.rs1) >> is_imm_64(instruction.is_type));
                    return PC + 4; //0x5
            }
            assert(0 && "UNKNOWN IMM INST");
            return 0; //0x13    /* 0010011 */

        case RV64_OP_AUIPC:
            write_reg_long(instruction.u_type.rd, (u_imm(instruction.u_type) << 12) + PC);
            return PC + 4; //0x17    /* 0010111 */

        case RV64_OP_OP_IMM32:
            switch(instruction.i_type.funct3) {
                case RV64_FUNCT3_ADDIW :
                    uint32_t addiw_val = read_reg_int(instruction.i_type.rs1) + i_imm(instruction.i_type);
                    uint64_t addiw_write = addiw_val;
                    if (addiw_val >> 31 == 1)
                    {
                        addiw_write = 0xFFFFFFFF00000000l | addiw_val;
                    }

                    write_reg_long(instruction.i_type.rd, addiw_write);
                    return PC + 4;// 0x0

                case RV64_FUNCT3_SLLIW :
                    uint32_t slliw_val = read_reg_int(instruction.i_type.rs1) << i_imm(instruction.i_type);
                    uint64_t slliw_write = slliw_val;
                    if (slliw_val >> 31 == 1)
                    {
                        slliw_write = 0xFFFFFFFF00000000l | slliw_val;
                    }

                    write_reg_long(instruction.i_type.rd, slliw_write);
                    return PC + 4;// 0x0
            }
            printf("\n");
            assert(0 && "RV64_OP_OP_IMM32\n");
            return 0; //0x1b    /* 0011011 */

        case RV64_OP_STORE:
            switch (instruction.s_type.funct3) {
                case RV64_FUNCT3_SB :
                    write_byte(read_reg_long(instruction.s_type.rs1) + s_imm(instruction.s_type), read_reg_long(instruction.s_type.rs2));
                    return PC + 4; //0x0
                case RV64_FUNCT3_SH :
                    assert(0 && "RV64_OP_STORE - SH\n");
                    return; //0x1
                case RV64_FUNCT3_SW :
                    write_word(read_reg_long(instruction.s_type.rs1) + s_imm(instruction.s_type), read_reg_long(instruction.s_type.rs2));
                    return PC + 4; //0x3
                case RV64_FUNCT3_SD:
                    write_double_word(read_reg_long(instruction.s_type.rs1) + s_imm(instruction.s_type), read_reg_long(instruction.s_type.rs2));
                    return PC + 4; //0x3
            }
            assert(0 && "RV64_OP_STORE\n");
            return 0; //0x23    /* 0100011 */

        case RV64_OP_STORE_FP:
            assert(0 && "RV64_OP_STORE_FP\n");
            return 0; //0x27    /* 0100111 */

        case RV64_OP_AMO:
            assert(0 && "RV64_OP_AMO\n");
            return 0; //0x2f    /* 0101111 */

        case RV64_OP_OP:

            switch(instruction.r_type.funct3)
            {

                case RV64_FUNCT3_ADD   :
                    switch(instruction.r_type.funct7)
                    {
                        case RV64_FUNCT7_ADD :
                            write_reg_long(instruction.r_type.rd, read_reg_long(instruction.r_type.rs1) + read_reg_long(instruction.r_type.rs2));
                            return PC + 4; //0x00
                        case RV64_FUNCT7_MUL :
                            write_reg_long(instruction.r_type.rd, read_reg_long(instruction.r_type.rs1) * read_reg_long(instruction.r_type.rs2));
                            return PC + 4; //0x01
                        case RV64_FUNCT7_SUB :
                            write_reg_long(instruction.r_type.rd, read_reg_long(instruction.r_type.rs1) - read_reg_long(instruction.r_type.rs2));
                            return PC + 4; //0x20
                    }
                    assert(0 && "Unknown ADD FUNCT7");

                case RV64_FUNCT3_SLL   :
                    assert(0 && "RV64_OP_OP - SLL\n");
                    return PC + 4; // 0x1
                case RV64_FUNCT3_SLT   :
                    assert(0 && "RV64_OP_OP - SLT\n");
                    return PC + 4; // 0x2
                case RV64_FUNCT3_SLTU  :
                    assert(0 && "RV64_OP_OP - SLTU\n");
                    return PC + 4; // 0x3
                case RV64_FUNCT3_XOR   :
                    assert(0 && "RV64_OP_OP - XOR\n");
                    return PC + 4; // 0x4
                case RV64_FUNCT3_SRL   :
                    switch(instruction.r_type.funct7)
                    {
                        case RV64_FUNCT7_SRL :
                            assert(0 && "RV64_OP_OP - SRL\n");
                            return PC + 4;
                        case RV64_FUNCT7_SRA :
                            assert(0 && "RV64_OP_OP - SRA\n");
                            return PC + 4;
                        case RV64_FUNCT7_DIVU :
                            write_reg_long(instruction.r_type.rd, read_reg_long(instruction.r_type.rs1) / read_reg_long(instruction.r_type.rs2));
                            return PC + 4;
                    }
                    assert(0 && "RV64_OP_OP - UNKNOWN\n");
                    return PC + 4; // 0x5
                case RV64_FUNCT3_OR    :
                    write_reg_long(instruction.r_type.rd, read_reg_long(instruction.r_type.rs1) | read_reg_long(instruction.r_type.rs2));
                    return PC + 4; // 0x6
                case RV64_FUNCT3_AND   :
                    switch (instruction.r_type.funct7)
                    {
                        case RV64_FUNCT7_REMU :
                            write_reg_long(instruction.r_type.rd, read_reg_long(instruction.r_type.rs1) % read_reg_long(instruction.r_type.rs2));
                            return PC + 4;

                        case RV64_FUNCT7_AND :
                            write_reg_long(instruction.r_type.rd, read_reg_long(instruction.r_type.rs1) & read_reg_long(instruction.r_type.rs2));
                            return PC + 4;
                    }

            }
            assert(0 && "RV64_OP_OP\n");
            return 0; //0x33    /* 0110011 */

        case RV64_OP_LUI:
            write_reg_long(instruction.u_type.rd, (instruction.u_type.sext << 20 | instruction.u_type.imm) << 12);
            return PC + 4; //0x37    /* 0110111 */

        case RV64_OP_OP32:
            switch (instruction.r_type.funct3) {
                case RV64_FUNCT3_ADDW :
                    uint32_t val = read_reg_int(instruction.r_type.rs1) + read_reg_int(instruction.r_type.rs2);
                    uint64_t write_val = val;
                    if(val >> 31 == 1)
                        write_val = 0xFFFFFFFF00000000l | val;

                    write_reg_long(instruction.i_type.rd, write_val);
                    return PC + 4;// 0x0
            }
            printf("\n");
            assert(0 && "RV64_OP_OP32\n");
            return 0; //0x3b    /* 0111011 */
        case RV64_OP_MADD:
            assert(0 && "RV64_OP_MADD\n");
            return 0; //0x43    /* 1000011 */
        case RV64_OP_MSUB:
            assert(0 && "RV64_OP_MSUB\n");
            return 0; //0x47    /* 1000111 */
        case RV64_OP_NMSUB:
            assert(0 && "RV64_OP_NMSUB\n");
            return 0; //0x4b    /* 1001011 */
        case RV64_OP_NMADD:
            assert(0 && "RV64_OP_NMADD\n");
            return 0; //0x4f    /* 1001111 */
        case RV64_OP_FP:
            assert(0 && "RV64_OP_FP\n");
            return 0; //0x53    /* 1010011 */
        case RV64_OP_BRANCH:
            switch(instruction.b_type.funct3)
            {
                case RV64_FUNCT3_BEQ  :
                    if(read_reg_long(instruction.b_type.rs1) == read_reg_long(instruction.b_type.rs2))
                    {
                        return PC + b_imm(instruction.b_type);
                    }
                    return PC + 4;

                case RV64_FUNCT3_BNE  :
                    if(read_reg_long(instruction.b_type.rs1) != read_reg_long(instruction.b_type.rs2))
                    {
                        return PC + b_imm(instruction.b_type);
                    }
                    return PC + 4;

                case RV64_FUNCT3_BLT  :
                    assert(0 && "RV64_OP_BRANCH - BLT\n");
                    return; //  0x4
                case RV64_FUNCT3_BGE  :
                    assert(0 && "RV64_OP_BRANCH - BGE\n");
                    return; //  0x5
                case RV64_FUNCT3_BLTU :
                    if(read_reg_long(instruction.b_type.rs1) < read_reg_long(instruction.b_type.rs2))
                    {
                        return PC + b_imm(instruction.b_type);
                    }
                    return PC + 4;

                case RV64_FUNCT3_BGEU :
                    if(read_reg_long(instruction.b_type.rs1) >= read_reg_long(instruction.b_type.rs2))
                    {
                        return PC + b_imm(instruction.b_type);
                    }
                    return PC + 4;
            }
            return 0; //0x63    /* 1100011 */

        case RV64_OP_JALR:
            write_reg_long(instruction.i_type.rd, PC + 4);
            PC = read_reg_long(instruction.i_type.rs1);
            return PC; //0x67    /* 1100111 */

        case RV64_OP_JAL:
            write_reg_long(instruction.j_type.rd, PC + 4);
            return PC + j_imm(instruction.j_type);; //0x6f    /* 1101111 */

        case RV64_OP_SYSTEM:
            uint64_t sys = read_reg_long(17);
            switch (sys)
            {
                case RV64_SYS_io_setup:
                    assert(0 && "RV64_SYS_io_setup\n");
                case RV64_SYS_io_destroy:
                    assert(0 && "RV64_SYS_io_destroy\n");
                case RV64_SYS_io_submit:
                    assert(0 && "RV64_SYS_io_submit\n");
                case RV64_SYS_io_cancel:
                    assert(0 && "RV64_SYS_io_cancel\n");
                case RV64_SYS_io_getevents:
                    assert(0 && "RV64_SYS_io_getevents\n");
                case RV64_SYS_setxattr:
                    assert(0 && "RV64_SYS_setxattr\n");
                case RV64_SYS_lsetxattr:
                    assert(0 && "RV64_SYS_lsetxattr\n");
                case RV64_SYS_fsetxattr:
                    assert(0 && "RV64_SYS_fsetxattr\n");
                case RV64_SYS_getxattr:
                    assert(0 && "RV64_SYS_getxattr\n");
                case RV64_SYS_lgetxattr:
                    assert(0 && "RV64_SYS_lgetxattr\n");
                case RV64_SYS_fgetxattr:
                    assert(0 && "RV64_SYS_fgetxattr\n");
                case RV64_SYS_listxattr:
                    assert(0 && "RV64_SYS_listxattr\n");
                case RV64_SYS_llistxattr:
                    assert(0 && "RV64_SYS_llistxattr\n");
                case RV64_SYS_flistxattr:
                    assert(0 && "RV64_SYS_flistxattr\n");
                case RV64_SYS_removexattr:
                    assert(0 && "RV64_SYS_removexattr\n");
                case RV64_SYS_lremovexattr:
                    assert(0 && "RV64_SYS_lremovexattr\n");
                case RV64_SYS_fremovexattr:
                    assert(0 && "RV64_SYS_fremovexattr\n");
                case RV64_SYS_getcwd:
                    assert(0 && "RV64_SYS_getcwd\n");
                case RV64_SYS_lookup_dcookie:
                    assert(0 && "RV64_SYS_lookup_dcookie\n");
                case RV64_SYS_eventfd2:
                    assert(0 && "RV64_SYS_eventfd2\n");
                case RV64_SYS_epoll_create1:
                    assert(0 && "RV64_SYS_epoll_create1\n");
                case RV64_SYS_epoll_ctl:
                    assert(0 && "RV64_SYS_epoll_ctl\n");
                case RV64_SYS_epoll_pwait:
                    assert(0 && "RV64_SYS_epoll_pwait\n");
                case RV64_SYS_dup:
                    assert(0 && "RV64_SYS_dup\n");
                case RV64_SYS_dup3:
                    assert(0 && "RV64_SYS_dup3\n");
                case RV64_SYS_fcntl:
                    assert(0 && "RV64_SYS_fcntl\n");
                case RV64_SYS_inotify_init1:
                    assert(0 && "RV64_SYS_inotify_init1\n");
                case RV64_SYS_inotify_add_watch:
                    assert(0 && "RV64_SYS_inotify_add_watch\n");
                case RV64_SYS_inotify_rm_watch:
                    assert(0 && "RV64_SYS_inotify_rm_watch\n");
                case RV64_SYS_ioctl:
                    assert(0 && "RV64_SYS_ioctl\n");
                case RV64_SYS_ioprio_set:
                    assert(0 && "RV64_SYS_ioprio_set\n");
                case RV64_SYS_ioprio_get:
                    assert(0 && "RV64_SYS_ioprio_get\n");
                case RV64_SYS_flock:
                    assert(0 && "RV64_SYS_flock\n");
                case RV64_SYS_mknodat:
                    assert(0 && "RV64_SYS_mknodat\n");
                case RV64_SYS_mkdirat:
                    assert(0 && "RV64_SYS_mkdirat\n");
                case RV64_SYS_unlinkat:
                    assert(0 && "RV64_SYS_unlinkat\n");
                case RV64_SYS_symlinkat:
                    assert(0 && "RV64_SYS_symlinkat\n");
                case RV64_SYS_linkat:
                    assert(0 && "RV64_SYS_linkat\n");
                case RV64_SYS_renameat:
                    assert(0 && "RV64_SYS_renameat\n");
                case RV64_SYS_umount2:
                    assert(0 && "RV64_SYS_umount2\n");
                case RV64_SYS_mount:
                    assert(0 && "RV64_SYS_mount\n");
                case RV64_SYS_pivot_root:
                    assert(0 && "RV64_SYS_pivot_root\n");
                case RV64_SYS_nfsservctl:
                    assert(0 && "RV64_SYS_nfsservctl\n");
                case RV64_SYS_statfs:
                    assert(0 && "RV64_SYS_statfs\n");
                case RV64_SYS_fstatfs:
                    assert(0 && "RV64_SYS_fstatfs\n");
                case RV64_SYS_truncate:
                    assert(0 && "RV64_SYS_truncate\n");
                case RV64_SYS_ftruncate:
                    assert(0 && "RV64_SYS_ftruncate\n");
                case RV64_SYS_fallocate:
                    assert(0 && "RV64_SYS_fallocate\n");
                case RV64_SYS_faccessat:
                    assert(0 && "RV64_SYS_faccessat\n");
                case RV64_SYS_chdir:
                    assert(0 && "RV64_SYS_chdir\n");
                case RV64_SYS_fchdir:
                    assert(0 && "RV64_SYS_fchdir\n");
                case RV64_SYS_chroot:
                    assert(0 && "RV64_SYS_chroot\n");
                case RV64_SYS_fchmod:
                    assert(0 && "RV64_SYS_fchmod\n");
                case RV64_SYS_fchmodat:
                    assert(0 && "RV64_SYS_fchmodat\n");
                case RV64_SYS_fchownat:
                    assert(0 && "RV64_SYS_fchownat\n");
                case RV64_SYS_fchown:
                    assert(0 && "RV64_SYS_fchown\n");
                case RV64_SYS_openat:
                    assert(0 && "RV64_SYS_openat\n");
                case RV64_SYS_close:
                    assert(0 && "RV64_SYS_close\n");
                case RV64_SYS_vhangup:
                    assert(0 && "RV64_SYS_vhangup\n");
                case RV64_SYS_pipe2:
                    assert(0 && "RV64_SYS_pipe2\n");
                case RV64_SYS_quotactl:
                    assert(0 && "RV64_SYS_quotactl\n");
                case RV64_SYS_getdents64:
                    assert(0 && "RV64_SYS_getdents64\n");
                case RV64_SYS_lseek:
                    assert(0 && "RV64_SYS_lseek\n");
                case RV64_SYS_read:
                    assert(0 && "RV64_SYS_read\n");
                case RV64_SYS_write:
                    assert(0 && "RV64_SYS_write\n");
                case RV64_SYS_readv:
                    assert(0 && "RV64_SYS_readv\n");
                case RV64_SYS_writev:
                    assert(0 && "RV64_SYS_writev\n");
                case RV64_SYS_pread64:
                    assert(0 && "RV64_SYS_pread64\n");
                case RV64_SYS_pwrite64:
                    assert(0 && "RV64_SYS_pwrite64\n");
                case RV64_SYS_preadv:
                    assert(0 && "RV64_SYS_preadv\n");
                case RV64_SYS_pwritev:
                    assert(0 && "RV64_SYS_pwritev\n");
                case RV64_SYS_sendfile:
                    assert(0 && "RV64_SYS_sendfile\n");
                case RV64_SYS_pselect6:
                    assert(0 && "RV64_SYS_pselect6\n");
                case RV64_SYS_ppoll:
                    assert(0 && "RV64_SYS_ppoll\n");
                case RV64_SYS_signalfd4:
                    assert(0 && "RV64_SYS_signalfd4\n");
                case RV64_SYS_vmsplice:
                    assert(0 && "RV64_SYS_vmsplice\n");
                case RV64_SYS_splice:
                    assert(0 && "RV64_SYS_splice\n");
                case RV64_SYS_tee:
                    assert(0 && "RV64_SYS_tee\n");
                case RV64_SYS_readlinkat:
                    char *fullpath = (char*) malloc(4096);
                    fullpath = realpath(get_filename(), fullpath);
                    printf("%s\n", fullpath);
                    if(read_reg_long(10) == AT_FDCWD)
                    {

                    }

                    printf("%.lx\n", read_reg_long(10));
                    printf("%d\n", read_reg_long(11));
                    printf("%d\n", read_reg_long(12));
                    printf("%d\n", read_reg_long(13));
                    printf("%d\n", read_reg_long(14));
                    printf("%d\n", read_reg_long(15));
                    printf("%d\n", read_reg_long(16));
                    assert(0 && "RV64_SYS_readlinkat\n");
                case RV64_SYS_fstatat:
                    assert(0 && "RV64_SYS_fstatat\n");
                case RV64_SYS_fstat:
                    assert(0 && "RV64_SYS_fstat\n");
                case RV64_SYS_sync:
                    assert(0 && "RV64_SYS_sync\n");
                case RV64_SYS_fsync:
                    assert(0 && "RV64_SYS_fsync\n");
                case RV64_SYS_fdatasync:
                    assert(0 && "RV64_SYS_fdatasync\n");
                case RV64_SYS_sync_file_range:
                    assert(0 && "RV64_SYS_sync_file_range\n");
                case RV64_SYS_timerfd_create:
                    assert(0 && "RV64_SYS_timerfd_create\n");
                case RV64_SYS_timerfd_settime:
                    assert(0 && "RV64_SYS_timerfd_settime\n");
                case RV64_SYS_timerfd_gettime:
                    assert(0 && "RV64_SYS_timerfd_gettime\n");
                case RV64_SYS_utimensat:
                    assert(0 && "RV64_SYS_utimensat\n");
                case RV64_SYS_acct:
                    assert(0 && "RV64_SYS_acct\n");
                case RV64_SYS_capget:
                    assert(0 && "RV64_SYS_capget\n");
                case RV64_SYS_capset:
                    assert(0 && "RV64_SYS_capset\n");
                case RV64_SYS_personality:
                    assert(0 && "RV64_SYS_personality\n");
                case RV64_SYS_exit:
                    assert(0 && "RV64_SYS_exit\n");
                case RV64_SYS_exit_group:
                    assert(0 && "RV64_SYS_exit_group\n");
                case RV64_SYS_waitid:
                    assert(0 && "RV64_SYS_waitid\n");
                case RV64_SYS_set_tid_address:
                    write_reg_long(10, 0);
                    return PC + 4;
                case RV64_SYS_unshare:
                    assert(0 && "RV64_SYS_unshare\n");
                case RV64_SYS_futex:
                    assert(0 && "RV64_SYS_futex\n");
                case RV64_SYS_set_robust_list:
                    write_reg_long(10, 0);
                    return PC + 4;
                    printf("%d\n", read_reg_long(10));
                    printf("%d\n", read_reg_long(11));
                    printf("%d\n", read_reg_long(12));
                    printf("%d\n", read_reg_long(13));
                    printf("%d\n", read_reg_long(14));
                    printf("%d\n", read_reg_long(15));
                    printf("%d\n", read_reg_long(16));
                    assert(0 && "RV64_SYS_set_robust_list\n");
                case RV64_SYS_get_robust_list:
                    assert(0 && "RV64_SYS_get_robust_list\n");
                case RV64_SYS_nanosleep:
                    assert(0 && "RV64_SYS_nanosleep\n");
                case RV64_SYS_getitimer:
                    assert(0 && "RV64_SYS_getitimer\n");
                case RV64_SYS_setitimer:
                    assert(0 && "RV64_SYS_setitimer\n");
                case RV64_SYS_kexec_load:
                    assert(0 && "RV64_SYS_kexec_load\n");
                case RV64_SYS_init_module:
                    assert(0 && "RV64_SYS_init_module\n");
                case RV64_SYS_delete_module:
                    assert(0 && "RV64_SYS_delete_module\n");
                case RV64_SYS_timer_create:
                    assert(0 && "RV64_SYS_timer_create\n");
                case RV64_SYS_timer_gettime:
                    assert(0 && "RV64_SYS_timer_gettime\n");
                case RV64_SYS_timer_getoverrun:
                    assert(0 && "RV64_SYS_timer_getoverrun\n");
                case RV64_SYS_timer_settime:
                    assert(0 && "RV64_SYS_timer_settime\n");
                case RV64_SYS_timer_delete:
                    assert(0 && "RV64_SYS_timer_delete\n");
                case RV64_SYS_clock_settime:
                    assert(0 && "RV64_SYS_clock_settime\n");
                case RV64_SYS_clock_gettime:
                    assert(0 && "RV64_SYS_clock_gettime\n");
                case RV64_SYS_clock_getres:
                    assert(0 && "RV64_SYS_clock_getres\n");
                case RV64_SYS_clock_nanosleep:
                    assert(0 && "RV64_SYS_clock_nanosleep\n");
                case RV64_SYS_syslog:
                    assert(0 && "RV64_SYS_syslog\n");
                case RV64_SYS_ptrace:
                    assert(0 && "RV64_SYS_ptrace\n");
                case RV64_SYS_sched_setparam:
                    assert(0 && "RV64_SYS_sched_setparam\n");
                case RV64_SYS_sched_setscheduler:
                    assert(0 && "RV64_SYS_sched_setscheduler\n");
                case RV64_SYS_sched_getscheduler:
                    assert(0 && "RV64_SYS_sched_getscheduler\n");
                case RV64_SYS_sched_getparam:
                    assert(0 && "RV64_SYS_sched_getparam\n");
                case RV64_SYS_sched_setaffinity:
                    assert(0 && "RV64_SYS_sched_setaffinity\n");
                case RV64_SYS_sched_getaffinity:
                    assert(0 && "RV64_SYS_sched_getaffinity\n");
                case RV64_SYS_sched_yield:
                    assert(0 && "RV64_SYS_sched_yield\n");
                case RV64_SYS_sched_get_priority_max:
                    assert(0 && "RV64_SYS_sched_get_priority_max\n");
                case RV64_SYS_sched_get_priority_min:
                    assert(0 && "RV64_SYS_sched_get_priority_min\n");
                case RV64_SYS_sched_rr_get_interval:
                    assert(0 && "RV64_SYS_sched_rr_get_interval\n");
                case RV64_SYS_restart_syscall:
                    assert(0 && "RV64_SYS_restart_syscall\n");
                case RV64_SYS_kill:
                    assert(0 && "RV64_SYS_kill\n");
                case RV64_SYS_tkill:
                    assert(0 && "RV64_SYS_tkill\n");
                case RV64_SYS_tgkill:
                    assert(0 && "RV64_SYS_tgkill\n");
                case RV64_SYS_sigaltstack:
                    assert(0 && "RV64_SYS_sigaltstack\n");
                case RV64_SYS_rt_sigsuspend:
                    assert(0 && "RV64_SYS_rt_sigsuspend\n");
                case RV64_SYS_rt_sigaction:
                    assert(0 && "RV64_SYS_rt_sigaction\n");
                case RV64_SYS_rt_sigprocmask:
                    assert(0 && "RV64_SYS_rt_sigprocmask\n");
                case RV64_SYS_rt_sigpending:
                    assert(0 && "RV64_SYS_rt_sigpending\n");
                case RV64_SYS_rt_sigtimedwait:
                    assert(0 && "RV64_SYS_rt_sigtimedwait\n");
                case RV64_SYS_rt_sigqueueinfo:
                    assert(0 && "RV64_SYS_rt_sigqueueinfo\n");
                case RV64_SYS_rt_sigreturn:
                    assert(0 && "RV64_SYS_rt_sigreturn\n");
                case RV64_SYS_setpriority:
                    assert(0 && "RV64_SYS_setpriority\n");
                case RV64_SYS_getpriority:
                    assert(0 && "RV64_SYS_getpriority\n");
                case RV64_SYS_reboot:
                    assert(0 && "RV64_SYS_reboot\n");
                case RV64_SYS_setregid:
                    assert(0 && "RV64_SYS_setregid\n");
                case RV64_SYS_setgid:
                    assert(0 && "RV64_SYS_setgid\n");
                case RV64_SYS_setreuid:
                    assert(0 && "RV64_SYS_setreuid\n");
                case RV64_SYS_setuid:
                    assert(0 && "RV64_SYS_setuid\n");
                case RV64_SYS_setresuid:
                    assert(0 && "RV64_SYS_setresuid\n");
                case RV64_SYS_getresuid:
                    assert(0 && "RV64_SYS_getresuid\n");
                case RV64_SYS_setresgid:
                    assert(0 && "RV64_SYS_setresgid\n");
                case RV64_SYS_getresgid:
                    assert(0 && "RV64_SYS_getresgid\n");
                case RV64_SYS_setfsuid:
                    assert(0 && "RV64_SYS_setfsuid\n");
                case RV64_SYS_setfsgid:
                    assert(0 && "RV64_SYS_setfsgid\n");
                case RV64_SYS_times:
                    assert(0 && "RV64_SYS_times\n");
                case RV64_SYS_setpgid:
                    assert(0 && "RV64_SYS_setpgid\n");
                case RV64_SYS_getpgid:
                    assert(0 && "RV64_SYS_getpgid\n");
                case RV64_SYS_getsid:
                    assert(0 && "RV64_SYS_getsid\n");
                case RV64_SYS_setsid:
                    assert(0 && "RV64_SYS_setsid\n");
                case RV64_SYS_getgroups:
                    assert(0 && "RV64_SYS_getgroups\n");
                case RV64_SYS_setgroups:
                    assert(0 && "RV64_SYS_setgroups\n");
                case RV64_SYS_uname:
                    assert(0 && "RV64_SYS_uname\n");
                case RV64_SYS_sethostname:
                    assert(0 && "RV64_SYS_sethostname\n");
                case RV64_SYS_setdomainname:
                    assert(0 && "RV64_SYS_setdomainname\n");
                case RV64_SYS_getrlimit:
                    assert(0 && "RV64_SYS_getrlimit\n");
                case RV64_SYS_setrlimit:
                    assert(0 && "RV64_SYS_setrlimit\n");
                case RV64_SYS_getrusage:
                    assert(0 && "RV64_SYS_getrusage\n");
                case RV64_SYS_umask:
                    assert(0 && "RV64_SYS_umask\n");
                case RV64_SYS_prctl:
                    assert(0 && "RV64_SYS_prctl\n");
                case RV64_SYS_getcpu:
                    assert(0 && "RV64_SYS_getcpu\n");
                case RV64_SYS_gettimeofday:
                    assert(0 && "RV64_SYS_gettimeofday\n");
                case RV64_SYS_settimeofday:
                    assert(0 && "RV64_SYS_settimeofday\n");
                case RV64_SYS_adjtimex:
                    assert(0 && "RV64_SYS_adjtimex\n");
                case RV64_SYS_getpid:
                    assert(0 && "RV64_SYS_getpid\n");
                case RV64_SYS_getppid:
                    assert(0 && "RV64_SYS_getppid\n");
                case RV64_SYS_getuid:
                    assert(0 && "RV64_SYS_getuid\n");
                case RV64_SYS_geteuid:
                    assert(0 && "RV64_SYS_geteuid\n");
                case RV64_SYS_getgid:
                    assert(0 && "RV64_SYS_getgid\n");
                case RV64_SYS_getegid:
                    assert(0 && "RV64_SYS_getegid\n");
                case RV64_SYS_gettid:
                    assert(0 && "RV64_SYS_gettid\n");
                case RV64_SYS_sysinfo:
                    assert(0 && "RV64_SYS_sysinfo\n");
                case RV64_SYS_mq_open:
                    assert(0 && "RV64_SYS_mq_open\n");
                case RV64_SYS_mq_unlink:
                    assert(0 && "RV64_SYS_mq_unlink\n");
                case RV64_SYS_mq_timedsend:
                    assert(0 && "RV64_SYS_mq_timedsend\n");
                case RV64_SYS_mq_timedreceive:
                    assert(0 && "RV64_SYS_mq_timedreceive\n");
                case RV64_SYS_mq_notify:
                    assert(0 && "RV64_SYS_mq_notify\n");
                case RV64_SYS_mq_getsetattr:
                    assert(0 && "RV64_SYS_mq_getsetattr\n");
                case RV64_SYS_msgget:
                    assert(0 && "RV64_SYS_msgget\n");
                case RV64_SYS_msgctl:
                    assert(0 && "RV64_SYS_msgctl\n");
                case RV64_SYS_msgrcv:
                    assert(0 && "RV64_SYS_msgrcv\n");
                case RV64_SYS_msgsnd:
                    assert(0 && "RV64_SYS_msgsnd\n");
                case RV64_SYS_semget:
                    assert(0 && "RV64_SYS_semget\n");
                case RV64_SYS_semctl:
                    assert(0 && "RV64_SYS_semctl\n");
                case RV64_SYS_semtimedop:
                    assert(0 && "RV64_SYS_semtimedop\n");
                case RV64_SYS_semop:
                    assert(0 && "RV64_SYS_semop\n");
                case RV64_SYS_shmget:
                    assert(0 && "RV64_SYS_shmget\n");
                case RV64_SYS_shmctl:
                    assert(0 && "RV64_SYS_shmctl\n");
                case RV64_SYS_shmat:
                    assert(0 && "RV64_SYS_shmat\n");
                case RV64_SYS_shmdt:
                    assert(0 && "RV64_SYS_shmdt\n");
                case RV64_SYS_socket:
                    assert(0 && "RV64_SYS_socket\n");
                case RV64_SYS_socketpair:
                    assert(0 && "RV64_SYS_socketpair\n");
                case RV64_SYS_bind:
                    assert(0 && "RV64_SYS_bind\n");
                case RV64_SYS_listen:
                    assert(0 && "RV64_SYS_listen\n");
                case RV64_SYS_accept:
                    assert(0 && "RV64_SYS_accept\n");
                case RV64_SYS_connect:
                    assert(0 && "RV64_SYS_connect\n");
                case RV64_SYS_getsockname:
                    assert(0 && "RV64_SYS_getsockname\n");
                case RV64_SYS_getpeername:
                    assert(0 && "RV64_SYS_getpeername\n");
                case RV64_SYS_sendto:
                    assert(0 && "RV64_SYS_sendto\n");
                case RV64_SYS_recvfrom:
                    assert(0 && "RV64_SYS_recvfrom\n");
                case RV64_SYS_setsockopt:
                    assert(0 && "RV64_SYS_setsockopt\n");
                case RV64_SYS_getsockopt:
                    assert(0 && "RV64_SYS_getsockopt\n");
                case RV64_SYS_shutdown:
                    assert(0 && "RV64_SYS_shutdown\n");
                case RV64_SYS_sendmsg:
                    assert(0 && "RV64_SYS_sendmsg\n");
                case RV64_SYS_recvmsg:
                    assert(0 && "RV64_SYS_recvmsg\n");
                case RV64_SYS_readahead:
                    assert(0 && "RV64_SYS_readahead\n");
                case RV64_SYS_brk:
                    write_reg_long(10, 0);
                    return PC + 4;
                case RV64_SYS_munmap:
                    assert(0 && "RV64_SYS_munmap\n");
                case RV64_SYS_mremap:
                    assert(0 && "RV64_SYS_mremap\n");
                case RV64_SYS_add_key:
                    assert(0 && "RV64_SYS_add_key\n");
                case RV64_SYS_request_key:
                    assert(0 && "RV64_SYS_request_key\n");
                case RV64_SYS_keyctl:
                    assert(0 && "RV64_SYS_keyctl\n");
                case RV64_SYS_clone:
                    assert(0 && "RV64_SYS_clone\n");
                case RV64_SYS_execve:
                    assert(0 && "RV64_SYS_execve\n");
                case RV64_SYS_mmap:
                    if(read_reg_long(10))
                    {
                        assert(0 && "specific address mmap");
                    }
                    if(read_reg_long(14) > -1)
                    {
                        assert(0 && "file backed mmap");
                    }
                    write_reg_long(10, get_program_break());
                    set_program_break(get_program_break() + read_reg_long(11));
                    return PC + 4;
                case RV64_SYS_fadvise64:
                    assert(0 && "RV64_SYS_fadvise64\n");
                case RV64_SYS_swapon:
                    assert(0 && "RV64_SYS_swapon\n");
                case RV64_SYS_swapoff:
                    assert(0 && "RV64_SYS_swapoff\n");
                case RV64_SYS_mprotect:
                    assert(0 && "RV64_SYS_mprotect\n");
                case RV64_SYS_msync:
                    assert(0 && "RV64_SYS_msync\n");
                case RV64_SYS_mlock:
                    assert(0 && "RV64_SYS_mlock\n");
                case RV64_SYS_munlock:
                    assert(0 && "RV64_SYS_munlock\n");
                case RV64_SYS_mlockall:
                    assert(0 && "RV64_SYS_mlockall\n");
                case RV64_SYS_munlockall:
                    assert(0 && "RV64_SYS_munlockall\n");
                case RV64_SYS_mincore:
                    assert(0 && "RV64_SYS_mincore\n");
                case RV64_SYS_madvise:
                    assert(0 && "RV64_SYS_madvise\n");
                case RV64_SYS_remap_file_pages:
                    assert(0 && "RV64_SYS_remap_file_pages\n");
                case RV64_SYS_mbind:
                    assert(0 && "RV64_SYS_mbind\n");
                case RV64_SYS_get_mempolicy:
                    assert(0 && "RV64_SYS_get_mempolicy\n");
                case RV64_SYS_set_mempolicy:
                    assert(0 && "RV64_SYS_set_mempolicy\n");
                case RV64_SYS_migrate_pages:
                    assert(0 && "RV64_SYS_migrate_pages\n");
                case RV64_SYS_move_pages:
                    assert(0 && "RV64_SYS_move_pages\n");
                case RV64_SYS_rt_tgsigqueueinfo:
                    assert(0 && "RV64_SYS_rt_tgsigqueueinfo\n");
                case RV64_SYS_perf_event_open:
                    assert(0 && "RV64_SYS_perf_event_open\n");
                case RV64_SYS_accept4:
                    assert(0 && "RV64_SYS_accept4\n");
                case RV64_SYS_recvmmsg:
                    assert(0 && "RV64_SYS_recvmmsg\n");
                case RV64_SYS_arch_specific_syscall:
                    assert(0 && "RV64_SYS_arch_specific_syscall\n");
                case RV64_SYS_wait4:
                    assert(0 && "RV64_SYS_wait4\n");
                case RV64_SYS_prlimit64:
                    write_reg_long(10, -1);
                    return PC + 4;
                    printf("%d\n", read_reg_long(10));
                    printf("%d\n", read_reg_long(11));
                    printf("%d\n", read_reg_long(12));
                    printf("%d\n", read_reg_long(13));
                    printf("%d\n", read_reg_long(14));
                    printf("%d\n", read_reg_long(15));
                    printf("%d\n", read_reg_long(16));
                    assert(0 && "RV64_SYS_prlimit64\n");
                case RV64_SYS_fanotify_init:
                    assert(0 && "RV64_SYS_fanotify_init\n");
                case RV64_SYS_fanotify_mark:
                    assert(0 && "RV64_SYS_fanotify_mark\n");
                case RV64_SYS_name_to_handle_at        :
                    assert(0 && "RV64_SYS_name_to_handle_at\n");
                case RV64_SYS_open_by_handle_at        :
                    assert(0 && "RV64_SYS_open_by_handle_at\n");
                case RV64_SYS_clock_adjtime:
                    assert(0 && "RV64_OP_SYSTEM\n");
                case RV64_SYS_syncfs:
                    assert(0 && "RV64_OP_SYSTEM\n");
                case RV64_SYS_setns:
                    assert(0 && "RV64_OP_SYSTEM\n");
                case RV64_SYS_sendmmsg:
                    assert(0 && "RV64_OP_SYSTEM\n");
                case RV64_SYS_process_vm_readv:
                    assert(0 && "RV64_SYS_process_vm_readv\n");
                case RV64_SYS_process_vm_writev:
                    assert(0 && "RV64_SYS_process_vm_writev\n");
                case RV64_SYS_kcmp:
                    assert(0 && "RV64_SYS_kcmp\n");
                case RV64_SYS_finit_module:
                    assert(0 && "RV64_SYS_finit_module\n");
                case RV64_SYS_sched_setattr:
                    assert(0 && "RV64_SYS_sched_setattr\n");
                case RV64_SYS_sched_getattr:
                    assert(0 && "RV64_SYS_sched_getattr\n");
                case RV64_SYS_renameat2:
                    assert(0 && "RV64_SYS_renameat2\n");
                case RV64_SYS_seccomp:
                    assert(0 && "RV64_SYS_seccomp\n");
                case RV64_SYS_getrandom:
                    assert(0 && "RV64_SYS_getrandom\n");
                case RV64_SYS_memfd_create:
                    assert(0 && "RV64_SYS_memfd_create\n");
                case RV64_SYS_bpf:
                    assert(0 && "RV64_SYS_bpf\n");
                case RV64_SYS_execveat:
                    assert(0 && "RV64_SYS_execveat\n");
                case RV64_SYS_userfaultfd:
                    assert(0 && "RV64_SYS_userfaultfd\n");
                case RV64_SYS_membarrier:
                    assert(0 && "RV64_SYS_membarrier\n");
                case RV64_SYS_mlock2:
                    assert(0 && "RV64_SYS_mlock2\n");
                case RV64_SYS_copy_file_range:
                    assert(0 && "RV64_SYS_copy_file_range\n");
                case RV64_SYS_preadv2:
                    assert(0 && "RV64_SYS_preadv2\n");
                case RV64_SYS_pwritev2:
                    assert(0 && "RV64_SYS_pwritev2\n");
                case RV64_SYS_pkey_mprotect:
                    assert(0 && "RV64_SYS_pkey_mprotect\n");
                case RV64_SYS_pkey_alloc:
                    assert(0 && "RV64_SYS_pkey_alloc\n");
                case RV64_SYS_pkey_free:
                    assert(0 && "RV64_SYS_pkey_free\n");
                case RV64_SYS_statx:
                    assert(0 && "RV64_SYS_statx\n");
                case RV64_SYS_io_pgetevents:
                    assert(0 && "RV64_SYS_io_pgetevents\n");
                case RV64_SYS_rseq:
                    assert(0 && "RV64_SYS_rseq\n");
                case RV64_SYS_kexec_file_load:
                    assert(0 && "RV64_SYS_kexec_file_load\n");
                case RV64_SYS_clock_gettime64:
                    assert(0 && "RV64_SYS_clock_gettime64\n");
                case RV64_SYS_clock_settime64:
                    assert(0 && "RV64_SYS_clock_settime64\n");
                case RV64_SYS_clock_adjtime64:
                    assert(0 && "RV64_SYS_clock_adjtime64\n");
                case RV64_SYS_clock_getres_time64:
                    assert(0 && "RV64_SYS_clock_getres_time64\n");
                case RV64_SYS_clock_nanosleep_time64:
                    assert(0 && "RV64_SYS_clock_nanosleep_time64\n");
                case RV64_SYS_timer_gettime64:
                    assert(0 && "RV64_SYS_timer_gettime64\n");
                case RV64_SYS_timer_settime64:
                    assert(0 && "RV64_SYS_timer_settime64\n");
                case RV64_SYS_timerfd_gettime64:
                    assert(0 && "RV64_SYS_timerfd_gettime64\n");
                case RV64_SYS_timerfd_settime64:
                    assert(0 && "RV64_SYS_timerfd_settime64\n");
                case RV64_SYS_utimensat_time64:
                    assert(0 && "RV64_SYS_utimensat_time64\n");
                case RV64_SYS_pselect6_time64:
                    assert(0 && "RV64_SYS_pselect6_time64\n");
                case RV64_SYS_ppoll_time64:
                    assert(0 && "RV64_SYS_ppoll_time64\n");
                case RV64_SYS_io_pgetevents_time64:
                    assert(0 && "RV64_SYS_io_pgetevents_time64\n");
                case RV64_SYS_recvmmsg_time64:
                    assert(0 && "RV64_SYS_recvmmsg_time64\n");
                case RV64_SYS_mq_timedsend_time64:
                    assert(0 && "RV64_SYS_mq_timedsend_time64\n");
                case RV64_SYS_mq_timedreceive_time64:
                    assert(0 && "RV64_SYS_mq_timedreceive_time64\n");
                case RV64_SYS_semtimedop_time64:
                    assert(0 && "RV64_SYS_semtimedop_time64\n");
                case RV64_SYS_rt_sigtimedwait_time64:
                    assert(0 && "RV64_SYS_rt_sigtimedwait_time64\n");
                case RV64_SYS_futex_time64:
                    assert(0 && "RV64_SYS_futex_time64\n");
                case RV64_SYS_sched_rr_get_interval_time64:
                    assert(0 && "RV64_SYS_sched_rr_get_interval_time64\n");
                case RV64_SYS_pidfd_send_signal:
                    assert(0 && "RV64_SYS_pidfd_send_signal\n");
                case RV64_SYS_io_uring_setup:
                    assert(0 && "RV64_SYS_io_uring_setup\n");
                case RV64_SYS_io_uring_enter:
                    assert(0 && "RV64_SYS_io_uring_enter\n");
                case RV64_SYS_io_uring_register:
                    assert(0 && "RV64_SYS_io_uring_register\n");
                case RV64_SYS_open_tree:
                    assert(0 && "RV64_SYS_open_tree\n");
                case RV64_SYS_move_mount:
                    assert(0 && "RV64_SYS_move_mount\n");
                case RV64_SYS_fsopen:
                    assert(0 && "RV64_SYS_fsopen\n");
                case RV64_SYS_fsconfig:
                    assert(0 && "RV64_SYS_fsconfig\n");
                case RV64_SYS_fsmount:
                    assert(0 && "RV64_SYS_fsmount\n");
                case RV64_SYS_fspick:
                    assert(0 && "RV64_SYS_fspick\n");
                case RV64_SYS_pidfd_open:
                    assert(0 && "RV64_SYS_pidfd_open\n");
                case RV64_SYS_clone3:
                    assert(0 && "RV64_SYS_clone3\n");
                case RV64_SYS_close_range:
                    assert(0 && "RV64_SYS_close_range\n");
                case RV64_SYS_openat2:
                    assert(0 && "RV64_SYS_openat2\n");
                case RV64_SYS_pidfd_getfd:
                    assert(0 && "RV64_SYS_pidfd_getfd\n");
                case RV64_SYS_faccessat2 :
                    assert(0 && "RV64_SYS_faccessat2\n");
                case RV64_SYS_process_madvise :
                    assert(0 && "RV64_SYS_process_madvise\n");
                case RV64_SYS_epoll_pwait2 :
                    assert(0 && "RV64_SYS_epoll_pwait2\n");
                case RV64_SYS_mount_setattr :
                    assert(0 && "RV64_SYS_mount_setattr\n");
                case RV64_SYS_quotactl_fd :
                    assert(0 && "RV64_SYS_quotactl_fd\n");
                case RV64_SYS_landlock_create_ruleset :
                    assert(0 && "RV64_SYS_landlock_create_ruleset\n");
                case RV64_SYS_landlock_add_rule :
                    assert(0 && "RV64_SYS_landlock_add_rule\n");
                case RV64_SYS_landlock_restrict_self :
                    assert(0 && "RV64_SYS_landlock_restrict_self\n");
                case RV64_SYS_memfd_secret :
                    assert(0 && "RV64_SYS_memfd_secret\n");
                case RV64_SYS_process_mrelease :
                    assert(0 && "RV64_SYS_process_mrelease\n");
                case RV64_SYS_futex_waitv :
                    assert(0 && "RV64_SYS_futex_waitv\n");
                case RV64_SYS_set_mempolicy_home_node :
                    assert(0 && "RV64_SYS_set_mempolicy_home_node\n");
                case RV64_SYS_cachestat :
                    assert(0 && "RV64_SYS_cachestat\n");
                case RV64_SYS_fchmodat2 :
                    assert(0 && "RV64_SYS_fchmodat2\n");
                case RV64_SYS_syscalls :
                    assert(0 && "RV64_SYS_syscalls\n");
            }
            assert(0 && "RV64_OP_SYSTEM\n");
            return 0; //0x73    /* 1110011 */
        default: return 0;
    }
}

void pretty_print(inst_t instruction, uint64_t PC)
{
    printf("%d\t%8x:\t%8x\t", inst_count, PC, instruction.instruction);
    switch(instruction.encoding.opcode)
    {
        case RV64_OP_LOAD:
            switch (instruction.i_type.funct3) {
                case RV64_FUNCT3_LB  :
                    printf("\n");
                    assert(0 && "RV64_OP_LOAD - LB\n");
                    return; //0x0
                case RV64_FUNCT3_LH  :
                    printf("\n");
                    assert(0 && "RV64_OP_LOAD - LH\n");
                    return; //0x1
                case RV64_FUNCT3_LW  :
                    printf("lw\t$r%d, %d($r%d)\n", instruction.i_type.rd, i_imm(instruction.i_type), instruction.i_type.rs1);
                    return; //0x2
                case RV64_FUNCT3_LBU :
                    printf("lbu\t$r%d, %d($r%d)\n", instruction.i_type.rd, i_imm(instruction.i_type), instruction.i_type.rs1);
                    return; //0x4
                case RV64_FUNCT3_LHU :
                    printf("lhu\t$r%d, %d($r%d)\n", instruction.i_type.rd, i_imm(instruction.i_type), instruction.i_type.rs1);
                    return; //0x5
                case RV64_FUNCT3_LWU :
                    printf("\n");
                    assert(0 && "RV64_OP_LOAD - LWU\n");
                    return; //0x6

                case RV64_FUNCT3_LD  :
                    printf("ld\t$r%d, %d($r%d)\n", instruction.i_type.rd, i_imm(instruction.i_type), instruction.i_type.rs1);
                    return; //0x3
            }
            assert(0 && "UNKNOWN LOAD OP");
            return 0; //0x03    /* 0000011 */
        case RV64_OP_LOAD_FP:
            printf("\n");
            assert(0 && "RV64_OP_LOAD_FP\n");
            return 0; //0x07    /* 0000111 */
        case RV64_OP_MISC_MEM:
            switch (instruction.i_type.funct3)
            {
                case RV64_FUNCT3_FENCE:
                    printf("fence\n");
                    return;
                default:
                    printf("\n");
                    assert(0 && "UNKNOWN MISC_MEM");
            }
            printf("\n");
            assert(0 && "UNKNOWN MISC MEM\n");
            return 0; //0x0f    /* 0001111 */

        case RV64_OP_OP_IMM:
            switch(instruction.i_type.funct3)
            {
                case RV64_FUNCT3_ADDI :
                    printf("addi\t$r%d, $r%d, %d\n", instruction.i_type.rd, instruction.i_type.rs1, i_imm(instruction.i_type));
                    return;// 0x0
                case RV64_FUNCT3_SLTI :
                    printf("\n");
                    assert(0 && "RV64_OP_OP_IMM - SLTI\n");
                    return;// 0x2
                case RV64_FUNCT3_SLTIU:
                    printf("\n");
                    assert(0 && "RV64_OP_OP_IMM - SLTIU\n");
                    return;// 0x3
                case RV64_FUNCT3_XORI :
                    printf("xori\t$r%d, $r%d, %d\n", instruction.i_type.rd, instruction.i_type.rs1, i_imm(instruction.i_type));
                    return;// 0x4
                case RV64_FUNCT3_ORI  :
                    printf("\n");
                    assert(0 && "RV64_OP_OP_IMM - ORI\n");
                    return;// 0x6

                case RV64_FUNCT3_ANDI :
                    printf("andi\t$r%d, $r%d, %d\n", instruction.i_type.rd, instruction.i_type.rs1, i_imm(instruction.i_type));
                    return;// 0x7

                case RV64_FUNCT3_SLLI :
                    printf("slli\t$r%d, $r%d, %d\n", instruction.is_type.rd, instruction.is_type.rs1, is_imm_64(instruction.is_type));
                    return;

                case RV64_FUNCT3_SRLI :
                    printf("srli\t$r%d, $r%d, %d\n", instruction.is_type.rd, instruction.is_type.rs1, is_imm_64(instruction.is_type));
                    return; //0x5
            }

            return 0; //0x13    /* 0010011 */

        case RV64_OP_AUIPC:
            printf("auipc\t$r%d, 0x%lx\n", instruction.u_type.rd, u_imm(instruction.u_type));
            return; //0x17    /* 0010111 */

        case RV64_OP_OP_IMM32:
            switch(instruction.i_type.funct3)
            {
                case RV64_FUNCT3_ADDIW :
                    printf("addiw\t$r%d, $r%d, %d\n", instruction.i_type.rd, instruction.i_type.rs1, i_imm(instruction.i_type));
                    return;// 0x0

                case RV64_FUNCT3_SLLIW :
                    printf("slliw\t$r%d, $r%d, %d\n", instruction.i_type.rd, instruction.i_type.rs1, i_imm(instruction.i_type));
                    return;// 0x1
            }
            printf("\n");
            assert(0 && "RV64_OP_OP_IMM32\n");
            return 0; //0x1b    /* 0011011 */

        case RV64_OP_STORE:
            switch (instruction.s_type.funct3) {
                case RV64_FUNCT3_SB :
                    printf("sb\t$r%d, %d($r%d)\n", instruction.s_type.rs2, s_imm(instruction.s_type), instruction.s_type.rs1);
                    return; //0x0
                case RV64_FUNCT3_SH :
                    printf("\n");
                    assert(0 && "RV64_OP_STORE - SH\n");
                    return; //0x1
                case RV64_FUNCT3_SW :
                    printf("sw\t$r%d, %d($r%d)\n", instruction.s_type.rs2, s_imm(instruction.s_type), instruction.s_type.rs1);
                    return; //0x2
                case RV64_FUNCT3_SD:
                    printf("sd\t$r%d, %d($r%d)\n", instruction.s_type.rs2, s_imm(instruction.s_type), instruction.s_type.rs1);
                    return; //0x3
            }
            assert(0 && "RV64_OP_STORE\n");
            return 0; //0x23    /* 0100011 */
        case RV64_OP_STORE_FP:
            printf("\n");
            assert(0 && "RV64_OP_STORE_FP\n");
            return 0; //0x27    /* 0100111 */
        case RV64_OP_AMO:
            printf("\n");
            assert(0 && "RV64_OP_AMO\n");
            return 0; //0x2f    /* 0101111 */
        case RV64_OP_OP:
            switch(instruction.r_type.funct3)
            {
                case RV64_FUNCT3_ADD   :
                    switch(instruction.r_type.funct7)
                    {
                        case RV64_FUNCT7_ADD :
                            printf("add\t$r%d, $r%d, $r%d\n", instruction.r_type.rd, instruction.r_type.rs1, instruction.r_type.rs2);
                            return; //0x00
                        case RV64_FUNCT7_MUL :
                            printf("mul\t$r%d, $r%d, $r%d\n", instruction.r_type.rd, instruction.r_type.rs1, instruction.r_type.rs2);
                            return; //0x01
                        case RV64_FUNCT7_SUB :
                            printf("sub\t$r%d, $r%d, $r%d\n", instruction.r_type.rd, instruction.r_type.rs1, instruction.r_type.rs2);

                            return; //0x20

                    }
                    assert(0 && "Unknown ADD FUNCT7");

                case RV64_FUNCT3_SLL   :
                    printf("\n");
                    assert(0 && "RV64_OP_OP - SLL\n");
                    return PC + 4; // 0x1
                case RV64_FUNCT3_SLT   :
                    printf("\n");
                    assert(0 && "RV64_OP_OP - SLT\n");
                    return PC + 4; // 0x2
                case RV64_FUNCT3_SLTU  :
                    printf("\n");
                    assert(0 && "RV64_OP_OP - SLTU\n");
                    return PC + 4; // 0x3
                case RV64_FUNCT3_XOR   :
                    printf("\n");
                    assert(0 && "RV64_OP_OP - XOR\n");
                    return PC + 4; // 0x4
                case RV64_FUNCT3_SRL   :
                    switch(instruction.r_type.funct7)
                    {
                        case RV64_FUNCT7_SRL :
                            printf("\n");
                            assert(0 && "RV64_OP_OP - SRL\n");
                            return PC + 4;
                        case RV64_FUNCT7_SRA :
                            printf("\n");
                            assert(0 && "RV64_OP_OP - SRA\n");
                            return PC + 4;
                        case RV64_FUNCT7_DIVU :
                            printf("divu\t$r%d, $r%d, $r%d\n", instruction.r_type.rd, instruction.r_type.rs1, instruction.r_type.rs2);
                            return PC + 4;
                    }
                    return PC + 4; // 0x5
                case RV64_FUNCT3_OR    :
                    printf("or\t$r%d, $r%d, $r%d\n", instruction.r_type.rd, instruction.r_type.rs1, instruction.r_type.rs2);
                    return;
                case RV64_FUNCT3_AND   :
                    switch (instruction.r_type.funct7)
                    {
                        case RV64_FUNCT7_REMU :
                            printf("remu\t$r%d, $r%d, $r%d\n", instruction.r_type.rd, instruction.r_type.rs1, instruction.r_type.rs2);
                            return PC + 4;

                        case RV64_FUNCT7_AND :
                            printf("and\t$r%d, $r%d, $r%d\n", instruction.r_type.rd, instruction.r_type.rs1, instruction.r_type.rs2);
                            return;
                    }
                    printf("\n");
                    assert(0 && "UNKNOWN OP INST\n");
                    return; // 0x7
            }

        case RV64_OP_LUI:
            printf("lui\t$r%d, %d\n", instruction.u_type.rd, instruction.u_type.sext << 20 | instruction.u_type.imm);
            return; //0x37    /* 0110111 */

        case RV64_OP_OP32:
            switch (instruction.r_type.funct3) {
                case RV64_FUNCT3_ADDW :
                    printf("addw\t$r%d, $r%d, $r%d\n", instruction.r_type.rd, instruction.r_type.rs1, instruction.r_type.rs2);
                    return; //0x00

            }
            printf("\n");
            assert(0 && "RV64_OP_OP32\n");
            return 0; //0x3b    /* 0111011 */
        case RV64_OP_MADD:
            printf("\n");
            assert(0 && "RV64_OP_MADD\n");
            return 0; //0x43    /* 1000011 */
        case RV64_OP_MSUB:
            printf("\n");
            assert(0 && "RV64_OP_MSUB\n");
            return 0; //0x47    /* 1000111 */
        case RV64_OP_NMSUB:
            printf("\n");
            assert(0 && "RV64_OP_NMSUB\n");
            return 0; //0x4b    /* 1001011 */
        case RV64_OP_NMADD:
            printf("\n");
            assert(0 && "RV64_OP_NMADD\n");
            return 0; //0x4f    /* 1001111 */
        case RV64_OP_FP:
            printf("\n");
            assert(0 && "RV64_OP_FP\n");
            return 0; //0x53    /* 1010011 */
        case RV64_OP_BRANCH:
            switch(instruction.b_type.funct3)
            {
                case RV64_FUNCT3_BEQ  :
                    printf("beq\t$r%d, $r%d, %d\n", instruction.b_type.rs1, instruction.b_type.rs2, b_imm(instruction.b_type));
                    return; //0x0
                case RV64_FUNCT3_BNE  :
                    printf("bne\t$r%d, $r%d, %d\n", instruction.b_type.rs1, instruction.b_type.rs2, b_imm(instruction.b_type));
                    return; //  0x1
                case RV64_FUNCT3_BLT  :
                    printf("\n");
                    assert(0 && "RV64_OP_BRANCH - BLT\n");
                    return; //  0x4
                case RV64_FUNCT3_BGE  :
                    printf("\n");
                    assert(0 && "RV64_OP_BRANCH - BGE\n");
                    return; //  0x5
                case RV64_FUNCT3_BLTU :
                    printf("bltu\t$r%d, $r%d, %d\n", instruction.b_type.rs1, instruction.b_type.rs2, b_imm(instruction.b_type));
                    return; //  0x7
                    return; //  0x6
                case RV64_FUNCT3_BGEU :
                    printf("bgeu\t$r%d, $r%d, %d\n", instruction.b_type.rs1, instruction.b_type.rs2, b_imm(instruction.b_type));
                    return; //  0x7
            }
            assert(0 && "RV64_OP_BRANCH\n");
            return 0; //0x63    /* 1100011 */

        case RV64_OP_JALR:
            printf("jalr\t$r%d, %d($r%d)\n", instruction.i_type.rd, i_imm(instruction.i_type), instruction.i_type.rs1, 0);
            return 0; //0x67    /* 1100111 */

        case RV64_OP_JAL:
            uint64_t imm = j_imm(instruction.j_type);
            printf("jal\t$r%d, 0x%x\n", instruction.j_type.rd, imm + PC);
            return; //0x6f    /* 1101111 */

        case RV64_OP_SYSTEM:
            printf("ecall\n");
            return; //0x73    /* 1110011 */
        default: return 1;
    }
}

uint64_t j_imm(j_inst_t j)
{
    uint64_t val4 = 0;
    if(j.imm4 == 1)
    {
        val4 = 0xFFFFFFFFFFFFFFFFl;
    }

    uint64_t val1 = j.imm1;
    uint64_t val2 = j.imm2 << 10;
    uint64_t val3 = j.imm3 << 11;
    val4 = val4 << 19;

    uint64_t val = (val1 | val2 | val3 | val4) << 1;
    return val;
}

uint64_t u_imm(u_inst_t u)
{
    uint64_t val = 0;
    if(u.sext == 1)
    {
        val = 0xFFFFFFFFFFFFFFFFl;
        return (val << 19) | u.imm;
    }

    return u.sext << 20 | u.imm;
}

uint64_t i_imm(i_inst_t i)
{
    uint64_t val = 0;
    if(i.sext == 1)
    {
        val = 0xFFFFFFFFFFFFFFFFl;
    }

    return val << 11 | i.imm;
}

uint64_t is_imm_64(is_inst_t i)
{
    return i.shamt_ext << 6 | i.shamt;
}

uint32_t is_imm_32(is_inst_t i)
{
    return 0;
}

uint64_t s_imm(s_inst_t s)
{
    uint64_t val = 0;
    if(s.sext == 1)
    {
        val = 0xFFFFFFFFFFFFFFFFl;
    }

    return val << 11 | s.imm2 << 5 | s.imm1;
}

uint64_t b_imm(b_inst_t b)
{
    uint64_t val = 0;
    if(b.sext == 1 && b.funct3 != RV64_FUNCT3_BGEU && b.funct3 != RV64_FUNCT3_BLTU)
    {
        val = 0xFFFFFFFFF000l;
    }

    return val | b.sext << 12 | b.imm3 << 11 | b.imm2 << 5 | b.imm1 << 1;
}
