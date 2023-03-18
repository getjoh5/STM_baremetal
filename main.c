#include<stdint.h>

//travail sur la gestion des periphérique entré sortie
//gestion "includedes por usb 
#include"pripherique_config.h"
int a=12;
int b=15;
int main()
{
    //uint32_t j;
    initialisation();
    while(1){
        allume();
        for(int j=0;j<100000;j++)asm volatile("nop");
        eteint();
        //for(int j=0;j<100000;j++)asm volatile("nop");
    }
   return 0; 
}


/*led bright*/

