#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "error.h"
#include "elf_helper.h"
#include "memory.h"

static int fd = -1;
char* filename;

int check_elf(char* file) {
    filename = file;
    char *magic = NULL;
    fd = open(file, O_RDONLY);
    magic = (char *) mmap(NULL, 16, PROT_READ, MAP_SHARED, fd, 0);

    if (magic[EI_MAG0] != ELFMAG0 || magic[EI_MAG1] != ELFMAG1 || magic[EI_MAG2] != ELFMAG2 ||
        magic[EI_MAG3] != ELFMAG3)
    {
        THROW_ERROR("Not an ELF formatted file");
    }

    if (magic[EI_DATA] != ELFDATA2LSB)
    {
        THROW_ERROR("Not Little Endian");
    }

    if (magic[EI_CLASS] == ELFCLASSNONE)
    {
        THROW_ERROR("Invalid Class");
    }
    else if (magic[EI_CLASS] == ELFCLASS32)
    {
        munmap(magic, 16);
        return 32;
    }
    else if (magic[EI_CLASS] == ELFCLASS64)
    {
        munmap(magic, 16);
        return 64;
    }
    return -1;
}

void* create_hdr(char* file)
{
    fd = open(file, O_RDONLY);

    Elf64_Ehdr *header = (Elf64_Ehdr*) malloc(sizeof(Elf64_Ehdr));
    read(fd, header, sizeof(Elf64_Ehdr));
    return header;
}

void* create_phdr(void* header)
{
    int er = 0;
    Elf64_Ehdr* temp = (Elf64_Ehdr*) header;
    Elf64_Phdr *phdr = (Elf64_Phdr*) malloc(temp->e_phentsize * temp->e_phnum);
    lseek(fd, temp->e_phoff, SEEK_SET);
    er = read(fd, phdr, temp->e_phentsize * temp->e_phnum);
    if(er == -1)
    {
        THROW_ERROR("Problem Reading Program Header");
    }
    return phdr;
}

void get_loadable_segment(void* header)
{
    int er = 0;
    Elf64_Ehdr* temp = (Elf64_Ehdr*) header;
    Elf64_Phdr *temp_phdr = (Elf64_Phdr*) create_phdr(header);

    for (int i = 0; i < temp->e_phnum; i++)
    {
        uint64_t addr;
        if(temp_phdr[i].p_type == PT_LOAD || temp_phdr[i].p_type == PT_TLS)
        {
            uint8_t bytes[temp_phdr[i].p_memsz];
            lseek(fd, temp_phdr[i].p_offset, SEEK_SET);
            er = read(fd, bytes, temp_phdr[i].p_filesz);

            if(er == -1)
            {
                THROW_ERROR("Problem Reading Program Header");
            }

            if(temp_phdr[i].p_filesz < temp_phdr[i].p_memsz)
            {
                for (int j = temp_phdr[i].p_filesz; j < temp_phdr[i].p_memsz; j++)
                {
                    bytes[j] = 0;
                }
            }

            addr = write_arbitrary_bytes(bytes, temp_phdr[i].p_vaddr, temp_phdr[i].p_memsz);
        }
        set_program_break((addr + 4096) & 0xffffffffffff0000l);
    }
}

void* create_shdr(void* header)
{
    int er = 0;
    Elf64_Ehdr* temp = (Elf64_Ehdr*) header;
    Elf64_Shdr *sec = (Elf64_Shdr*) malloc(temp->e_shentsize * temp->e_shnum);
    lseek(fd, temp->e_shoff, SEEK_SET);
    er = read(fd, sec, temp->e_shentsize * temp->e_shnum);
    if(er == -1)
    {
        THROW_ERROR("Problem Reading Section Header");
    }
    return sec;
}

char* get_filename()
{
    return filename;
}
