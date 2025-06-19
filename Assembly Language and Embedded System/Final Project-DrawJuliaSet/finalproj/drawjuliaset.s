    .data
num: .asciz "%d\n"
wid:    .word 640
hei:    .word 480
hwid:   .word 320
hhei:   .word 240
max:    .word 255
two:    .word 2
a:    .word 1500
b:    .word 1000
c:    .word 4000000
d:    .word 0xffff
e:    .word 0xff
teamnum: .asciz "Team 13\n"
    .text

    .globl drawJuliaSet

drawJuliaSet :
@r4 =x
@r5 =y
@r6 =zx
@r7 =zy
@r8 =cx
@r9 = cy
@r10 = frame
@r11 = i

    ldr r10, [sp, #0]
    stmfd sp!, {r4-r11, lr}
    mov r4, #0 @x=0
    mov r8, r0 @r8=cx
    mov r9, r1 @r9=cy
    mov r2, lr
    add lr, r0, pc  @requirement 3
    mov lr, r2

Xloop:
    mov r1, #2
    cmp r1, #1
    cmpne r4, #640   @requirement2-1
    bge Xdone
    mov r5, #0 @y=0

Yloop:
    cmp r5, #480
    bge Ydone
    @-----------------zx-----------
    ldr r0, =wid
    ldr r1, =two
    ldr r0, [r0]
    ldr r1, [r1]
    bl __aeabi_idiv  @r0 = wid/2
    mov r1, r0		 @r1 = wid/2
    sub r6, r4, r0   @zx = x - (wid/2)
    ldr r2, =a       @r2 = 1500
    ldr r2, [r2]
    mul r6, r2, r6   @zx = 1500*(x - (wid/2))
    mov r0, r6
    ldr r1, =hwid    @wid/2
    ldr r1, [r1]
    bl __aeabi_idiv
    mov r6, r0       @zx = 1500*(x - (wid/2)) / (wid/2)
    @-----------------zy-----------
    ldr r0, =hei
    ldr r1, =two
    ldr r0, [r0]
    ldr r1, [r1]
    bl __aeabi_idiv  @ r0 = hei/2
    mov r1, r0
    sub r7, r5, r0   @ zy = y-hei/2
    ldr r2, =b       @ r2 = 1000
    ldr r2, [r2]
    mul r7, r2, r7   @1000*(y-hei/2)
    mov r0, r7
    ldr r1, =hhei    @hei/2
    ldr r1, [r1]
    bl __aeabi_idiv  @zy = 1000*(y-hei/2) / hei/2
    mov r7, r0
    @-----------------i = maxiter-----------
    ldr r11, =max     @i=255
    ldr r11, [r11]
while:
    @-----------------while-----------
    mul r0, r6, r6    @zx*zx
    mul r1, r7, r7    @zy*zy
    add r3, r1, r0    @zx*zx+zy*zy
    @----------------condition--------
    ldr r2, =c        @ r2 = 4000000
    ldr r2, [r2]
    cmp r3, r2
    bge whiledone
    cmp r11, #0
    ble whiledone
    @-------------temp-----------------
    mul r0, r6, r6    @zx*zx
    mul r1, r7, r7    @zy*zy
    cmphi r0, #0
    sub r0, r0, r1    @zx*zx-zy*zy
    ldr r1, =b        @r1=1000
    ldr r1, [r1]
    bl __aeabi_idiv   @(zx*zx-zy*zy)/1000
    add r3, r0, r8    @@(zx*zx-zy*zy)/1000 + cx
    @-------------zy-----------------
    mul r0, r6, r7    @zx*zy
    mov r6, r3        @zx = temp
    mov r1, #500
    bl __aeabi_idiv   @zx*zy/500
    add r7, r0, r9    @zx*zy/500 + cy
    @-------------(i--)-----------------
    cmp r11, #0
    subge r11, #1   @requirement2-2
    b while

Xdone:
    ldmfd sp!, {r4-r11, lr}
    mov pc, lr

Ydone:
    add r4, #1
    b Xloop

whiledone:
    and r11, r11, #0xff  @ i = i & 0xff
    orr r11, r11, r11, lsl #8  @op2 @ i = (i&0xff)|((i&0xff)<<8)

    ldr r2, =d     @r2=oxffff
    ldr r2, [r2]
    bic r11, r2, r11  @r11 = (~r11) & 0xffff

    mov r0, r10
    mov r1, #1280
    mul r1, r1, r5
    add r0, r1
    add r0, r4, lsl #1        @op2
    strh r11, [r0], #0
    @strh r11, [r0]

    addge r5, #1  @requirement2
    b Yloop


