# Fibonacci Sequence Generator
start:
    addi x1, x0, 0      # f0 = 0
    addi x2, x0, 1      # f1 = 1
    addi x3, x0, 10     # counter = 10
    addi x4, x0, 0      # memory pointer
    
loop:
    beq x3, x0, end     # If counter == 0, jump to end (Forward Ref)
    add x5, x1, x2      # next = f0 + f1
    sw x5, 0(x4)        # Store result in memory
    
    # Update values
    mv x1, x2           # f0 = f1
    mv x2, x5           # f1 = next
    
    # Decrement counter
    addi x3, x3, -1     # counter--
    addi x4, x4, 4      # move pointer
    jal x0, loop        # Jump back to loop (Backward Ref)

end:
    lw x10, -4(x4)      # Load last calculated value
    ebreak              # Exit program

# Padding for line count
nop
nop
nop
nop