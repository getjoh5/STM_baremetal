#include <stdint.h>
#include<stdio.h>

int main(int argc,char *argv[])
{
    uint32_t var1=0x44511458;
    uint8_t var2=(uint8_t)var1;
    printf("helloworld la variable recherché est %x ", var2);
    return 0;
    
}