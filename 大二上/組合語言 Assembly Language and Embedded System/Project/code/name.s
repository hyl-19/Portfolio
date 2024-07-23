.data
    str0: .asciz "*****Print Name*****\n"
    teamnum: .asciz "Team 13\n"
    name1: .asciz "Akira Huang"
    name2: .asciz "Cliff Lin"
    name3: .asciz "Sylvia Lin"
    nextline: .asciz "\n"
    str5: .asciz "*****End Print*****\n"
.text
  .globl name1
  .globl name2
  .globl name3
  .globl teamnum

.globl name
  name:
    stmfd sp!,{lr}
    ldr r0, =str0
    ldr r4, =teamnum
    ldr r5, =name1
    ldr r6, =name2
    ldr r7, =name3
    ldr r8, =str5
    ldr r9, =nextline
    bl printf
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

    mov r0, #0         @return 0
    ldmfd sp!,{lr}
    mov pc, lr
  .end

