#include<stdint.h>
//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
//travail sur la gestion des periphérique entré sortie
//gestion "includedes por usb 
#include"pripherique_config.h"

int main()
{
    //uint32_t j;
    initialisation();
    while(1){
        led(LED_OFF);
        allume();
        for(int j=0;j<1000000;j++);
        eteint();
        led(LED_YELLOW);
        for(int j=0;j<1000000;j++);
        //led(LED_OFF);
        led(LED_BLUE);
        for(int j=0;j<1000000;j++);
    }
   return 0; 
}


/*led bright*/

