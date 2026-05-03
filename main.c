#include <stdint.h>
#include "gpio.h"
#include "led_service.h"


int main()
{
    int i =0;
    if(GPIO_int() == -1){
        LED_TurnOn(LED_START_FINISH_BAD);
        i++;
    }

    if(i > 0){
        while(1){
           LED_TurnOn(LED_START_FINISH_BAD); 
        }
    }

    LED_TurnOn(LED_START_FINISH_GOOD);
    
    
    while(1){
        LED_TurnOn(LED_USER);
        for(int i = 0; i < 10000;i++);

        LED_TurnOff(LED_USER);
        for(int i = 0; i < 10000;i++);
        
    }
   return 0; 
}


/*led bright*/
