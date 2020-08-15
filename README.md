# CHIP-8

## Systems memory map

- 0x000 - 0x1FF: CHIP-8 interpreter (contains font set in emu)
- 0x200 - 0xFFF: Program ROM and work RAM

Details:
- 0x050 - 0x0A0: Used for the built in 4x5 pixel font set (0-F)
- 0xEA0 - 0xEFF: Reserved for the call stack, internal use, and other variables
- 0xF00 - 0xFFF: Reserved for display refresh

## Memory

- Most commonly implemented on 4K systems (f.e. Cosmac VIP, Telmac 1800)
- These machines had 4096 (0x1000) memory locations
- Each location with 8 bits (a byte)
  --> 4096 * 8 = 32768 bits = 4096 byte = 
- The CHIP-8 interpreter itself occupies the first 512 bytes of the memory space
- Most programs written for the original system begin at memory location 512 (0x200)
- The uppermost 256 bytes (0xF00-0xFFF) are reserved for display refresh
- The 96 bytes below that (0xEA0-0xEFF) were reserved for the call stack, internal use, and other variables.
- In modern CHIP-8 implementations, where the interpreter is running natively 
outside the 4K memory space, there is no need to avoid the lower 512 bytes 
of memory (0x000-0x200), and it is common to store font data there.

## Registers

- 16 * 8-bit data registers named V0 to VF.
- The VF register doubles as a flag for some instructions; thus, it should be avoided.
- In an addition operation, VF is the carry flag, while in subtraction, it is 
  the "no borrow" flag. In the draw instruction VF is set upon pixel collision.
- The address register, which is named I, is 16 bits wide and is used with 
  several opcodes that involve memory operations.

## Stack

- The stack is only used to store return addresses when subroutines are called
- The original RCA 1802 version allocated 48 bytes for up to 12 levels of nesting
- Modern implementations usually have more

## Timers

- Two timers
- They both count down at 60 hertz, until they reach 0.
- Delay timer: This timer is intended to be used for timing the events of games. 
  Its value can be set and read.
- Sound timer: This timer is used for sound effects. When its value is nonzero, 
  a beeping sound is made.

## Input

- Input is done with a hex keyboard that has 16 keys ranging 0 to F
- The '8', '4', '6', and '2' keys are typically used for directional input
- Three opcodes are used to detect input
  - One skips an instruction if a specific key is pressed, 
  - while another does the same if a specific key is not pressed
  - The third waits for a key press, and then stores it in one of the data registers.

## Graphics and sound

- Original CHIP-8 Display resolution is 64×32 pixels (= 2048) 
  and color is monochrome (= black and white)
- Graphics are drawn to the screen solely by drawing sprites,
  which are 8 pixels wide and may be from 1 to 15 pixels in height
- Sprite pixels are XOR'd with corresponding screen pixels. In other words, 
  sprite pixels that are set flip the color of the corresponding screen pixel,
  while unset sprite pixels do nothing
- The carry flag (VF) is set to 1 if any screen pixels are flipped from set to 
  unset when a sprite is drawn and set to 0 otherwise.
  This is used for collision detection.

As previously described, a beeping sound is played when the value of the sound timer is nonzero.

## Opcode table

- 35 / each two bytes long and stored big-endian
- Big-endian is an order in which the "big end" 
  (most significant value in the sequence) is stored first 
  (at the lowest storage address).
- Use on of these types:
    unsigned short
    unsigned short int
    uint16_t
    u_int16_t
  -->	0 to 65,535

- NNN: address
- NN: 8-bit constant
- N: 4-bit constant
- X and Y: 4-bit register identifier
- PC : Program Counter
- I : 16bit register (For memory address) (Similar to void pointer)
- VN: One of the 16 available variables. N may be 0 to F (hexadecimal)

