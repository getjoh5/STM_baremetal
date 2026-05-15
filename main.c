#include <stdint.h>
#include "gpio.h"
#include "led_service.h"
#include "Timer.h"
#include "timer_service.h"
#include "stm32l475xx.h"

int main()
{
    int errors = 0;
    int led_on = 0;

    if(GPIO_int() == -1){
        LED_TurnOn(LED_START_FINISH_BAD);
        errors++;
    }
    if(timer_init() == -1){
        LED_TurnOn(LED_START_FINISH_BAD);
        errors++;
    }
    /* Utilise SysTick comme source de temps du service timer. */
    if(timer_init_serv(&oTimer, &GlobalSystick/*&TIM2->CNT*/) == -1){
        LED_TurnOn(LED_START_FINISH_BAD);
        errors++;
    }

    if(errors > 0){
        while(1){
           LED_TurnOn(LED_START_FINISH_BAD); 
        }
    }

    LED_TurnOn(LED_START_FINISH_GOOD);

    /* Premier delai avant le basculement de la LED utilisateur. */
    timer_reset_serv(&oTimer, 1000);

    while(1){
        if(timer_expired_serv(&oTimer) == 1){
            if(led_on == 0){
                LED_TurnOn(LED_USER);
                led_on = 1;
            }else{
                LED_TurnOff(LED_USER);
                led_on = 0;
            }

            /* Relance un delai de 1 seconde apres chaque basculement. */
            timer_reset_serv(&oTimer, 1000);
        }
    }
   return 0;
}


/*led bright*/
