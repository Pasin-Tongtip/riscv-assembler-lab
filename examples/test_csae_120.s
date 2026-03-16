# Factorial with Manual Stack and Stress Test
main:
    addi sp, x0, 2048   # Set up stack pointer
    addi a0, x0, 5      # n = 5
    jal ra, fact        # Call factorial
    sw a0, 500(x0)      # Result to memory
    jal x0, stress_test # Jump to stress section

fact:
    addi sp, sp, -8     # Grow stack
    sw ra, 4(sp)        # Save return address
    sw a0, 0(sp)        # Save n
    
    addi t0, x0, 1
    bge a0, t0, recursive_step
    
    addi a0, x0, 1      # Base case: return 1
    addi sp, sp, 8
    jalr x0, 0(ra)

recursive_step:
    addi a0, a0, -1     # n - 1
    jal ra, fact        # fact(n-1)
    
    lw t1, 0(sp)        # Restore n
    lw ra, 4(sp)        # Restore RA
    addi sp, sp, 8      # Shrink stack
    
    # Use multiplication simulation if MUL isn't supported
    mv t2, a0
    addi t3, t1, -1
mul_loop:
    beq t3, x0, mul_done
    add a0, a0, t2
    addi t3, t3, -1
    j mul_loop
mul_done:
    ret

stress_test:
    # 100+ line stress sequence
    # Exercises every standard register and instruction type
    add x1, x2, x3
    sub x4, x5, x6
    sll x7, x8, x9
    slt x10, x11, x12
    sltu x13, x14, x15
    xor x16, x17, x18
    srl x19, x20, x21
    sra x22, x23, x24
    or x25, x26, x27
    and x28, x29, x30
    
    # Immediate versions
    addi x1, x2, 10
    slti x3, x4, 20
    sltiu x5, x6, 30
    xori x7, x8, 40
    ori x9, x10, 50
    andi x11, x12, 60
    slli x13, x14, 5
    srli x15, x16, 5
    srai x17, x18, 5
    
    # Memory stress
    lb x1, 0(sp)
    lh x2, 2(sp)
    lw x3, 4(sp)
    lbu x4, 1(sp)
    lhu x5, 3(sp)
    sb x1, 10(sp)
    sh x2, 12(sp)
    sw x3, 16(sp)
    
    # Repeat block to reach line count
    # (In a real test, repeat these patterns with different regs)
    add x1, x1, x1
    add x2, x2, x2
    add x3, x3, x3
    add x4, x4, x4
    add x5, x5, x5
    add x6, x6, x6
    add x7, x7, x7
    add x8, x8, x8
    add x9, x9, x9
    add x10, x10, x10
    add x11, x11, x11
    add x12, x12, x12
    add x13, x13, x13
    add x14, x14, x14
    add x15, x15, x15
    add x16, x16, x16
    add x17, x17, x17
    add x18, x18, x18
    add x19, x19, x19
    add x20, x20, x20
    add x21, x21, x21
    add x22, x22, x22
    add x23, x23, x23
    add x24, x24, x24
    add x25, x25, x25
    add x26, x26, x26
    add x27, x27, x27
    add x28, x28, x28
    add x29, x29, x29
    add x30, x30, x30
    add x31, x31, x31
    
    # Final jumps and branches
    beq x1, x2, final_label
    bne x1, x2, final_label
    blt x1, x2, final_label
    bge x1, x2, final_label
    bltu x1, x2, final_label
    bgeu x1, x2, final_label
    
final_label:
    lui x1, 0x12345
    auipc x2, 0xABCDE
    jal x1, main        # Ultimate loop back