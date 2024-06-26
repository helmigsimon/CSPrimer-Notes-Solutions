# General Purpose Registers
- Registers
    - Memory on the CPU
    - Faster to access than RAM
- If you have a particular variable, it'll be added into one of the 64 bit GPRs
    - Excluding floating points and larger values (these go into SIMD)
- How to see the registers
    - Open LLDB for an object or binary file
    - Enter `register read`
- History
    - Original 8086 -> 16 Bit machine
        - A lot of complexity in this instruction set comes from being backwards compatible with the 8086
        - Had 16 bit registers
            - ax
            - bx
            - cx
            - dx
            - Stream Processing
                - di (destination)
                - si (source)
            - Pointers
                - sp (stack pointer)
                    - Current location of the stack
                - bp (base pointer)
                    - Optionally used to indicate the top of the last stack frame
                    - sp and bp should diverge as more things are added to the stack
                        - not strictly needed since compiler often knows what was just pushed on the stack
                        - So can figure out
                    - Essentially sp - bp gives an indication of what the current size of data most recently pushed onto the stack
                - ip (instruction pointer)
                    - Currently executing instruction
            - flags
                - Consequences of previously executed instructions (i.e. did the last instruction overflow, or last comparison equal 0)
        - You *can* use the 16 bit registers
            - But on a 64 bit machine, they are aliases for the low order 16 bits for what is physically a 64 bit register
        - 32 bit registers 
            - Intel added a register with prefix `e` (extended) to maintian backwards compatability with programs compiled for 8086
                - eax
                - bax
                - ...
        - NOTE: 16 bit registers behave as if there is no further space available
            - For ax: 0xf and bx: 0x1
                - ax + bx will overflow!
            - Even though on a 32 or 64 bit architecture, there will be enough space available in the eax/rax register
            - Why?
                - Backwards compatability
        - Why use smaller registers?
            - They behave like larger ones (see overflow)
            - The restrictions of the smaller register force you to encode data into smaller containers (i.e. single byte values/shorts instead of four byte ints/8 byte longs)
                - Better cache performance and better performance overall
                - So you may have instructions that operate over parts of a register in order to do arithmetic correctly for these smaller values
        - 64 Bit Registers
            - Talking about the entire register
                - Prefixed with `r` (register)
            - Additional Registers
                - r8-r15
                    - Added with x86-64 to make more registers available
                    - Didn't exist on 32bit or 16 bit architectures
                        - But can still reference smaller portions of them
                            - r8d -> 32 bit
                            - r8w -> 16 bit
                            - r8b -> 8 bit
        - Higher and Lower Order Parts of a Register
            - ax
                - ah (upper half)
                - al (lower half)
        - Note
            - If you have bits on in rax and then you do a 32 bit addition on that register
                - What happens to the higher order bits?
                    - There is an automatic zeroing for historical reasoning when you do 32 bit arithmetic on a 64 bit register
                - This is NOT the case for 16 bit arithmetic
                - Downside
                    - Slows down program execution
                    - CPU is not able to do some out-of-order execution, b/c it doesn't know if you need those bits or not
- General Purpose Registers
    - Conventions
        - People may say you need to put accumulation into ax, subtraction into bx, etc.
            - These are largely not followed anymore
        - One thing to follow:
            - Put return value into RAX on unix derived Operating Systems
            - It's a calling convention for syscalls
- How to see all registers in lldb
    - reg re --all
        - Shows floating point registers / SIMD registers and all versions of 16 bit/32 bit and 64 bit versions of GPRs


