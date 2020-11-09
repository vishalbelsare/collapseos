#include <stdint.h>
#include <stdbool.h>

#define SP_ADDR 0xffff
#define RS_ADDR 0xff00
#define SYSVARS RS_ADDR-0x80
#define MEMSIZE 0x10000

typedef uint8_t byte;
typedef uint16_t word;
// Native words in this C Forth VMs are indexed in an array. The word in memory
// is the typical 0x00 to indicate native, followed by an index byte. The
// Execute routine will then know which native word to execute.
typedef void (*NativeWord) ();
typedef byte (*IORD) ();
typedef void (*IOWR) (byte data);

typedef struct {
    byte mem[MEMSIZE];
    word SP; // parameter Stack Pointer
    word RS; // Return Stack pointer
    word IP; // Interpreter Pointer
    // A list of native words' code. This is filled in VM_init() by calls to
    // native(). The order is very important because we refer to these elements
    // by index. For example, "0x42 CODE FOO" in Forth creates the native word
    // FOO which, when executed, will call the code at index 0x42 in this array.
    NativeWord nativew[0x100];
    byte nativew_count;
    // Array of 0x100 function pointers to IO read and write routines. Leave to
    // NULL when IO port is unhandled.
    IORD iord[0x100];
    IOWR iowr[0x100];
    // Used for keeping track of max RS and min SP during the lifetime of the
    // program. Useful for debugging.
    word maxRS;
    word minSP;
    bool running;
    // Whether we're in stack underflow situation. Alters the behavior of some
    // core action, notably popping. Doesn't stay set for more than a single
    // execute cycle. The goal is to avoid over-popping in native words that
    // pop more than once and thus corrupt memory.
    bool uflw;
    // Same as uflw, but for stack overflow. However, we behave differently with
    // oflw than with uflw. We can't prevent push() and pushRS() because it
    // would prevent us from calling (oflw). Instead, we clear both stacks on
    // oflw conditions, which gives us the room to maneuver.
    bool oflw;
} VM;

VM* VM_init(char *blkfs_path);
void VM_deinit();
bool VM_steps(int n);
void VM_memdump();
void VM_debugstr(char *s);
void VM_printdbg();
