#ifndef K
#define K
typedef enum state {LED_OFF, LED_YELLOW , LED_BLUE} state;
void initialisation();
void allume();
void eteint();
void led(state t);

#endif