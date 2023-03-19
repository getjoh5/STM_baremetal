.syntax unified
.global _start
.thumb
_start:
    ldr sp, =_stack
    bl Reset_handler
    ldr r0, =main
    bx r0

_exit:
    b _exit
