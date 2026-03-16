# RISC-V Two-Pass Assembler
A lightweight C-based assembler that translates RISC-V assembly language into machine code. The project utilizes a two-pass architecture to resolve label addresses for branches and jumps.

## 🚀 Features
Two-Pass Pipeline:

Pass 1: Scans the source file to build a Symbol Table, recording the addresses of all labels.

Pass 2: Re-reads the file to encode instructions and calculate relative offsets for branches.

Symbol Management: Robust label tracking with duplicate detection and address mapping.

Binary Output: Generates .bin files containing the encoded machine instructions.

## 📁 Project Structure
The project is organized based on the modular architecture defined in the Makefile:

File	Description
src/main.c	Entry point; handles command-line arguments and invokes the pipeline.
src/assembler.c	Coordinates the transition between Pass 1 and Pass 2.
src/symbols.c	
Implementation of the Symbol Table (add, find, reset).

src/parser.c	Handles string tokenization and instruction identification.
src/encode.c	Translates parsed instructions into 32-bit RISC-V machine code.
src/instr_table.c	Look-up table for RISC-V opcodes, funct3, and funct7 values.

## 💻 Usage
The assembler accepts a single RISC-V assembly file as an argument:

Bash
./assembler examples/test_case_20.s

The output will be saved as examples/test_case_20.bin.

## 🧪 Test Cases
The following test cases are included to verify assembler stability:

Basic Arithmetic (test_case_20.s): ~20 lines testing R-type and I-type instructions.

Array Logic (test_case_50.s): ~50 lines exercising loops and memory access (sw/lw).

Stress Test (test_case_120.s): 120+ lines featuring recursive factorial logic, deep stack usage, and long-distance label resolution.

## ⚠️ Implementation Notes
Symbol Limits: The table supports up to 256 unique labels.

Label Length: Maximum label length is 50 characters.

Instruction Size: Assumes a standard 4-byte instruction alignment for PC incrementing.
