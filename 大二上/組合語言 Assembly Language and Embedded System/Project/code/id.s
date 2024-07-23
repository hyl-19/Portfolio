.data
    str0: .asciz "*****Input ID*****\n"
    strinput: .asciz "** Please Enter Member %d ID:**\n"
    id1: .word 0
    id2: .word 0
    id3: .word 0
    total: .word 0
    command: .word 0
    input: .asciz "%d"
    enterp: .asciz "** Please Enter Command **\n"
    comm: .space 80
    strin: .asciz "%s"
    nextline: .asciz "\n"
    p: .asciz "p"
    printID: .asciz "*****Print Team Member ID and ID Summation*****\n"
    printone: .asciz "%d\n"
    printTotal: .asciz "ID Summation = %d\n"
    endprint: .asciz"*****End Print*****\n"

.text
  .globl id1
  .globl id2
  .globl id3
  .globl total
  .globl printTotal
  .globl endprint
  .globl nextline

.globl id

  printlast:
    ldr r0, =printTotal
    ldr r1, =total
    ldr r1, [r1]
    bl printf
    ldr r0, =endprint
    bl printf
    ldmfd sp! ,{lr}
    mov pc ,lr


  Isp:     @ == p, add id in total

    ldr r0, =printID
    bl printf
    @---------------------print id1
    ldr r0, =printone
    ldr r1, =id1
    ldr r1, [r1]
    bl printf
    @---------------------print id2
    ldr r0, =printone
    ldr r1, =id2
    ldr r1, [r1]
    bl printf
    @---------------------print id3
    ldr r0, =printone
    ldr r1, =id3
    ldr r1, [r1]
    bl printf
    ldr r0, =nextline  @ "\n"
    bl printf
    @---------------------ldr id address and get it's value
    ldr r8, =id1
    ldr r9, =id2
    ldr r10, =id3
    ldr r8, [r8]
    ldr r9, [r9]
    ldr r10, [r10]
    @--------------------- to sum up
    add r8, r8, r9
    add r8, r8, r10
    add r8, r8, #1
    sub r8, #1
    @---------------------
    ldr r1, =total
    str r8, [r1], #4   @store total

    cmp r8, #0
    blpl printlast



  Isnotp:    @ != p, print end
    ldr r0, =endprint
    bl printf
    ldmfd sp! ,{lr}
    mov pc ,lr

  id:
    stmfd sp!,{lr}
    ldr r0, =str0
    bl printf
    @----------------------------sacnf id1
    ldr r0, =strinput
    subs r1, pc, lr   @line 5 require
    mov r1, #1
    bl printf
    ldr r0, =input
    ldr r1, =id1
    bl scanf
    @----------------------------scanf id2
    ldr r0, =strinput
    mov r1, #2
    bl printf
    ldr r0, =input
    ldr r1, =id2
    bl scanf
    @----------------------------scanf id3
    ldr r0, =strinput
    mov r1, #3
    bl printf
    ldr r0, =input
    ldr r1, =id3
    bl scanf
    @----------------------------
    ldr r0, =enterp
    bl printf
    ldr r0, =strin   @"%s"
    ldr r1, =command @store input in command
    bl scanf
    @----------------------------
    ldr r0, =command
    ldr r0, [r0]
    ldr r1, =p
    ldrb r1, [r1]

    strb r1, [r8, #4]
    ldrb r2, [r8, #4]!

    cmp r2, r0    @compare input == command
    blne Isnotp   @ != p
    cmp r2, r0
    bleq Isp      @ == p

    mov r0, #0
    ldmfd sp!,{lr}
    mov pc, lr
  .end

