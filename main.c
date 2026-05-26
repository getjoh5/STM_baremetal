#include <stdint.h>
#include "gpio.h"
#include "led_service.h"
#include "Timer.h"
#include "timer_service.h"
#include "spi.h"
#include "st7789.h"
#include "stm32l475xx.h"

#define ST7789_DEBUG_MODE_COLOR      0
#define ST7789_DEBUG_MODE_RAW_SPI    1
#define ST7789_DEBUG_MODE_CTRL_PINS  2

#define ST7789_DEBUG_MODE -1//ST7789_DEBUG_MODE_RAW_SPI

static void debug_blink_user_led(uint32_t count)
{
    for(uint32_t i = 0; i < count; i++){
        LED_TurnOn(LED_USER);
        timer_delay_ms(100);
        LED_TurnOff(LED_USER);
        timer_delay_ms(100);
    }
}

int main()
{
    int errors = 0;

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

    //LED_TurnOn(LED_START_FINISH_GOOD); //ne peux plus etre utilisé car meme pin que SPI
    debug_blink_user_led(1);
    spi_init();
    debug_blink_user_led(2);

#if ST7789_DEBUG_MODE == ST7789_DEBUG_MODE_CTRL_PINS
    while(1){
        GPIO_PA3_ON();
        GPIO_PA4_ON();
        LED_TurnOn(LED_USER);
        timer_delay_ms(500);

        GPIO_PA3_OFF();
        GPIO_PA4_OFF();
        LED_TurnOff(LED_USER);
        timer_delay_ms(500);
    }
#elif ST7789_DEBUG_MODE == ST7789_DEBUG_MODE_RAW_SPI
    uint8_t test = 0xAA;

    while(1){
        GPIO_PA3_ON();
        spi_write(&test, 1);
        LED_TurnOn(LED_USER);
        timer_delay_ms(10);
        LED_TurnOff(LED_USER);
        timer_delay_ms(10);
    }
#endif

    ST7789_Init();
    debug_blink_user_led(3);

    while(1){
        LED_TurnOn(LED_USER);
        ST7789_Fill_Color(RED);
        LED_TurnOff(LED_USER);
        timer_delay_ms(1000);

        LED_TurnOn(LED_USER);
        ST7789_Fill_Color(GREEN);
        LED_TurnOff(LED_USER);
        timer_delay_ms(1000);

        LED_TurnOn(LED_USER);
        ST7789_Fill_Color(BLUE);
        LED_TurnOff(LED_USER);
        timer_delay_ms(1000);
    }
   return 0;
}


/*led bright*/
