#include<stdint.h>

//travail sur la gestion des periphérique entré sortie
//gestion "includedes por usb 
#include"pripherique_config.h"

int main()
{
    //uint32_t j;
    initialisation();
    while(1){
        allume();
        for(int j=0;j<1000000;j++);
        eteint();
        for(int j=0;j<1000000;j++);
    }
   return 0; 
}


/*led bright*/

