.syntax unified
.section .text_crt0, "ax"
.global _start
.type _start, %function
.thumb
.thumb_func
_start:
    #ldr sp, =_stack
    bl Reset_handler
    ldr r0, =main
    bx r0

_exit:
    b _exit
