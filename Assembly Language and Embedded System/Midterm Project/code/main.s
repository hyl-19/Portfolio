.data
    str1: .asciz "Function1: Name\n"
    str2: .asciz "Function2: ID\n"
    str3: .asciz "Main Function:\n*****Print All*****\n"
    idandname: .asciz "%d %s\n"

.text


.globl main
  main:
    stmfd sp!, {lr}
    @----------------------name.s
    ldr r0, =str1
    bl printf
    bl name
    @----------------------id.s
    ldr r0, =str2
    bl printf
    bl id
    ldr r0, =nextline
    bl printf
    @----------------------main.s
    ldr r0, =str3
    bl printf
    ldr r0, =teamnum
    bl printf
    @----------------------print id1 name1
    ldr r0, =idandname
    ldr r1, =id1
    ldr r1, [r1]
    ldr r2, =name1
    bl printf
    @######################## print id2 name2
    ldr r0, =idandname
    ldr r1, =id2
    ldr r1, [r1]
    ldr r2, =name2
    bl printf
    @######################## print id3 name3
    ldr r0, =idandname
    ldr r1, =id3
    ldr r1, [r1]
    ldr r2, =name3
    bl printf
    @--------------------
    ldr r0, =printTotal
    ldr r1, =total
    ldr r1, [r1]
    bl printf

    ldr r0, =endprint
    bl printf

    mov r0, #0
    ldmfd sp!,{lr}
  mov pc, lr
  .end

