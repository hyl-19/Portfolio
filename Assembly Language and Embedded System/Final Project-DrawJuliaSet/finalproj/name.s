.data
    str0: .asciz "*****Print Name*****\n"
    teamnum: .asciz "Team 13\n"
    name1: .asciz "Akira Huang"
    name2: .asciz "Cliff Lin"
    name3: .asciz "Sylvia Lin"
    nextline: .asciz "\n"
    str5: .asciz "*****End Print*****\n"
    n1a:   .word 0
    n2a:   .word 0
    n3a:   .word 0
    ta:   .word 0
.text
  .globl name1
  .globl name2
  .globl name3
  .globl teamnum

.globl name
  name:
    stmfd sp!,{lr}

    ldr r4, =n1a
    str r0, [r4]
    ldr r4, =n2a
    str r1, [r4]
    ldr r4, =n3a
    str r2, [r4]
    ldr r4, =ta
    str r3, [r4]

    ldr r0, =str0
    bl printf

    ldr r4, =teamnum
    ldr r5, =name1
    ldr r6, =name2
    ldr r7, =name3
    ldr r8, =str5
    ldr r9, =nextline
    @------------------print teamnum
    mov r0, r4, LSL #1
    mov r0, r0, LSR #1
    bl printf
    @------------------print name1
    mov r0, r5
    bl printf
    mov r0, r9
    bl printf
    @------------------print name2
    mov r0, r6
    bl printf
    mov r0, r9
    bl printf
    @------------------print name3
    mov r0, r7
    bl printf
    mov r0, r9
    bl printf
    @------------------prtin end
    mov r0, r8
    bl printf


    ldr r0, =n1a
    ldr r0, [r0]
    ldr r1, =name1
    ldr r1, [r1]
    str r1, [r0]

    ldr r0, =n2a
    ldr r0, [r0]
    ldr r1, =name2
    ldr r1, [r1]
    str r1, [r0]

    ldr r0, =n3a
    ldr r0, [r0]
    ldr r1, =name3
    ldr r1, [r1]
    str r1, [r0]

    ldr r0, =ta
    ldr r0, [r0]
    ldr r1, =teamnum
    ldr r1, [r1]
    str r1, [r0]

    mov r0, #0         @return 0
    ldmfd sp!,{lr}
    mov pc, lr
  .end



