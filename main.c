#include<stdint.h>
//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
//travail sur la gestion des periphérique entré sortie
//gestion "includedes por usb 
#include"pripherique_config.h"
#include "startup_filel.h"
#include "button_configuration.h"

int main()
{

    //uint32_t j;
    //irq_init();
    initialisation();
    int_button();


    //uint32_t val_button=0;
    
    while(1){
        // led(LED_OFF);
        // allume();
        // for(int j=0;j<1000000;j++);
        // eteint();
        // led(LED_YELLOW);
        // for(int j=0;j<1000000;j++);
        // //led(LED_OFF);
        // led(LED_BLUE);
        // for(int j=0;j<1000000;j++);
       // val_button=(uint32_t)*GPIOC_IDR;
        
    }
   return 0; 
}


/*led bright*/

