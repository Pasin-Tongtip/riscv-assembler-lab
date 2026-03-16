# Find Maximum in Array
setup:
    addi x1, x0, 0      # i = 0
    addi x2, x0, 12     # length = 12
    addi x3, x0, 1024   # Array base address
    lw x4, 0(x3)        # max = array[0]
    
    # Populate array manually for testing
    addi x5, x0, 15
    sw x5, 4(x3)
    addi x5, x0, 42
    sw x5, 8(x3)
    addi x5, x0, 7
    sw x5, 12(x3)

search_loop:
    bge x1, x2, finish  # if i >= length, exit loop
    
    slli x6, x1, 2      # offset = i * 4
    add x7, x3, x6      # address = base + offset
    lw x8, 0(x7)        # current_val = array[i]
    
    # Logical check: if current_val > max
    blt x8, x4, skip_update
    mv x4, x8           # Update max
    
skip_update:
    # Bitwise logic exercise
    andi x9, x8, 1      # Check if even/odd
    ori x9, x9, 2       # Force a bit high
    xori x9, x9, -1     # Flip bits
    
    addi x1, x1, 1      # i++
    jal x0, search_loop # repeat

finish:
    sw x4, 100(x0)      # Store final max at address 100
    
# Extra NOPs and instructions for length
    add x1, x1, x1
    sub x2, x2, x2
    srl x3, x3, x1
    sra x4, x4, x1
    or x5, x1, x2
    and x6, x1, x2
    xor x7, x1, x2
    slt x8, x1, x2
    sltu x9, x1, x2
    
    # Final padding
    addi x0, x0, 0
    addi x0, x0, 0
    addi x0, x0, 0
    addi x0, x0, 0
    addi x0, x0, 0