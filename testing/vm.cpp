#include <stdio.h>
#include <stdint.h>
#include <signal.h>
/* windows only */
#include <Windows.h>
#include <conio.h>  // _kbhit

using namespace std;

#define MEMORY_MAX (1 << 16)
unsigned short memory[MEMORY_MAX];


enum registers {
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
};

#define R_COUNT 10
unsigned short reg[R_COUNT];

enum opcodes {
    OP_BR = 0, // branch
    OP_ADD, // add
    OP_LD, // load
    OP_ST, // store
    OP_JSR, // jump register
    OP_AND, // bitwise and
    OP_LDR, // load register
    OP_STR, // store register
    OP_RTI, // unused
    OP_NOT, // bitwise not
    OP_LDI, // load indirect
    OP_STI, // store indirect
    OP_JMP, // jump
    OP_RES, // reserved (unused)
    OP_LEA, // load effective address
    OP_TRAP // execute trap
};

enum condition_flags {
    FL_POS = 1 << 0,
    FL_ZRO = 1 << 1,
    FL_NEG = 1 << 2
};


// DUMB STUFF :):):)

HANDLE hStdin = INVALID_HANDLE_VALUE;
DWORD fdwMode, fdwOldMode;

void disable_input_buffering()
{
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &fdwOldMode); /* save old mode */
    fdwMode = fdwOldMode
            ^ ENABLE_ECHO_INPUT  /* no input echo */
            ^ ENABLE_LINE_INPUT; /* return when one or
                                    more characters are available */
    SetConsoleMode(hStdin, fdwMode); /* set new mode */
    FlushConsoleInputBuffer(hStdin); /* clear buffer */
}

void restore_input_buffering()
{
    SetConsoleMode(hStdin, fdwOldMode);
}

uint16_t check_key()
{
    return WaitForSingleObject(hStdin, 1000) == WAIT_OBJECT_0 && _kbhit();
}

void handle_interrupt(int signal)
{
    restore_input_buffering();
    printf("\n");
    exit(-2);
}

// END DUMB STUFF :):):)

uint16_t sign_extend(uint16_t x, int bit_count)
{
    if ((x >> (bit_count - 1)) & 1) {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

void update_flags(unsigned short r) {
    if(reg[r] == 0) {
        reg[R_COND] = FL_ZRO;
    }
    else if(reg[r] > 0) {
        reg[R_COND] = FL_POS;
    }
    else {
        reg[R_COND] = FL_NEG;
    }
}

void add(unsigned short instruction) {
    unsigned short Rd = instruction & 0x0e00;
    // ..........
    
    update_flags(Rd);
}

int main(int argc, const char* argv[]) {
    // begin argc argv stuff that i dont understand
    if (argc < 2) {
        /* show usage string */
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; ++j) {
        if (!read_image(argv[j])) {
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }
    // end argc argv stuff that i dont understand
    // disables input buffering at the beginning of main
    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    // initialize zero flag, keeping all other flags off
    reg[R_COND] = FL_ZRO;

    // set origin of program to $3000
    enum {PC_START = 0x3000};
    reg[R_PC] = PC_START;

    int running = 1;
    while(running) {
        // fetch
        unsigned short instruction = mem_read(reg[R_PC]++);
        unsigned short op = instruction >> 12; // right shifting isolates the 4 left-most bits
        // execute
        switch(op) {
            case OP_ADD:
                add(unsigned short instruction);
                break;
            case OP_AND:

                break;
            case OP_NOT:

                break;
            case OP_BR:

                break;
            case OP_JMP:

                break;
            case OP_JSR:

                break;
            case OP_LD:

                break;
            case OP_LDI:

                break;
            case OP_LDR:

                break;
            case OP_LEA:

                break;
            case OP_ST:

                break;
            case OP_STI:

                break;
            case OP_STR:

                break;
            case OP_TRAP:

                break;
            case OP_RES:
            case OP_RTI:
            default:

                break;
        }
    }

    // restores input buffering at the beginning of main
    restore_input_buffering();
    return 0;
}