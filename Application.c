#include "Application.h"


uint32_t HOUR = 0;
uint32_t MIN  = 0;
uint32_t SEC  = 0;

static void restore_photo_area(uint16_t x, uint16_t y, uint16_t w, uint16_t h,const uint16_t image[240][240]);


/**
 * @brief Copy a C string into a fixed-size destination buffer.
 *
 * The project is linked with -nostdlib, so this helper replaces strcpy while
 * keeping the destination buffer null-terminated.
 *
 * @param dst Destination buffer.
 * @param dst_size Size of the destination buffer in bytes.
 * @param src Source null-terminated string.
 */
static void app_copy_string(char *dst, uint32_t dst_size, const char *src)
{
    if (dst == NULL || dst_size == 0U || src == NULL) {
        return;
    }

    uint32_t i = 0U;
    while ((i + 1U) < dst_size && src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

/**
 * @brief Convert an integer to a null-terminated decimal string.
 *
 * The project is linked without the standard library, so this helper replaces
 * formatting calls such as sprintf for small display strings.
 *
 * @param nombre Integer value to convert.
 * @param tmp Destination buffer.
 * @param separator Optional character appended after the number, or 0 for none.
 * @return Number of characters written including the null terminator.
 */
static uint8_t IntToChar(int nombre, char * tmp,char separator){
    uint8_t chiffre = 0;
    uint8_t counter = 0;
    int divisor = 1, i = 0;
    while(nombre/divisor >= 10)divisor *= 10;

    while(divisor > 0){
        chiffre = nombre/divisor;
        tmp[i++] = chiffre + 48;
        nombre %= divisor;
        divisor /= 10;
        counter++;
    }
    if(separator != 0){
        tmp[i]=separator;
        counter++;
        tmp[i+1]='\0';
    }else{
        tmp[i]='\0';
        counter++;
    }
    return counter;
}

/**
 * @brief Update the software clock and refresh the displayed time.
 *
 * The function uses TimeractualHourUpdate as a non-blocking 1 second timer.
 * Hours and minutes are drawn only when their value changes, while the colon is
 * toggled every second to keep the clock visibly alive.
 *
 * @param app Application object that owns the timer and display flags.
 */
static void Udapte_hour(Application_t * app){
    static uint8_t stepHour = 0;
    static uint8_t secIncrement = FALSE;
    static uint8_t toggle = FALSE;

    uint8_t j = 0;
    uint8_t update_SEC = FALSE;
    uint8_t update_MIN = FALSE;
    uint8_t update_HOUR = FALSE;

    char msg[3];
    switch (stepHour)
    {
    case 0:
        timer_reset_serv(&app->TimeractualHourUpdate,1000);
        stepHour = 1;
        secIncrement = FALSE;
        break;
    case 1:
        if(timer_expired_serv(&app->TimeractualHourUpdate) == TRUE){
          secIncrement = TRUE;  
          stepHour = 0;

        }
        break;
    
    default:
        break;
    }

    //incrementation des secondes
    if(secIncrement == TRUE){
        SEC++;
        update_SEC = TRUE;
        toggle = 0xFF ^ toggle;
    }

    //incrementation des minutes
    if(SEC == 60){
        MIN ++;
        SEC = 0;
        update_MIN = TRUE;
    }

    //incremention des heures 
    if(MIN == 60){
        HOUR++;
        MIN = 0;
        update_HOUR = TRUE;
    }

    if(HOUR == 24){
        HOUR = 0;
    }
    
    //ST7789_WriteStringTransparent(100 + j,198,"00:00",Font_16x26,WHITE,image_240x240);

    for(int i = 0; (i < PART_OF_TIME)&&(update_SEC);i++){
        char msgtmp[3];
        if(i == 0){
            if(app->flag.bit.init_time_done == 1 && update_HOUR == FALSE )continue;
            IntToChar(HOUR,msg,0);
            msgtmp[0]= (HOUR/10 > 0)? msg[0]:'0';
            msgtmp[1]= (HOUR/10 > 0)? msg[1]:msg[0];
            msgtmp[2]= '\0';
            ST7789_WriteStringTransparent(X_REF_POS_TIME +j,Y_REF_POS_TIME,msgtmp,Font_16x26,WHITE,image_240x240);
        }
        if(i == 1){
            j += SPACE_BETWN_PART_OF_TIME + WIDTH_FONT*2;
            if(toggle)ST7789_WriteStringTransparent(X_REF_POS_TIME + j,Y_REF_POS_TIME,":",Font_16x26,WHITE,image_240x240);
            else restore_photo_area(X_REF_POS_TIME + j,Y_REF_POS_TIME,WIDTH_FONT,HEIGHT_FONT,image_240x240);
        }
        if(i == 2){
            if(app->flag.bit.init_time_done == 1 && update_MIN == FALSE )continue;
            IntToChar(MIN,msg,0);
            msgtmp[0]= (MIN/10 > 0)? msg[0]:'0';
            msgtmp[1]= (MIN/10 > 0)? msg[1]:msg[0];
            msgtmp[2]= '\0';
            j += SPACE_BETWN_PART_OF_TIME + WIDTH_FONT;
            ST7789_WriteStringTransparent(X_REF_POS_TIME + j,Y_REF_POS_TIME,msgtmp,Font_16x26,WHITE,image_240x240);
        }


    }

    if(update_SEC)app->flag.bit.init_time_done = 1;




    



    
}

/**
 * @brief Restore a rectangular area from the 240x240 background image.
 *
 * ST7789_DrawImage expects a compact pixel buffer. A rectangular crop inside a
 * larger 240x240 image is not compact in memory, so this function restores one
 * row at a time.
 *
 * @param x Left coordinate of the area on screen and in the source image.
 * @param y Top coordinate of the area on screen and in the source image.
 * @param w Width of the area in pixels.
 * @param h Height of the area in pixels.
 * @param image Source RGB565 image with 240 rows and 240 columns.
 */
static void restore_photo_area(uint16_t x, uint16_t y, uint16_t w, uint16_t h,const uint16_t image[240][240])
{
    for (uint16_t row = 0; row < h; row++) {
        ST7789_DrawImage(
            x,
            y+row,
            w,
            1,
            &image[y+row][x]
        );
    }
}

/**
 * @brief Count the number of characters in a null-terminated string.
 *
 * @param msg String to count.
 * @return Number of characters, or -1 if msg is NULL.
 */
static int8_t numberOfChar( char* msg){
    if(msg == NULL)return -1;
    uint8_t i=0;
    while(msg[i] != '\0'){
        i++;
    }
    return i;
}

/**
 * @brief Initialize the application state and draw the startup screen.
 *
 * This function initializes the ST7789 display, draws the startup image,
 * initializes the application timer service, displays a welcome sequence, and
 * fills the loading bar progressively.
 *
 * @param app Application object to initialize.
 * @param Tim Tick source used by the timer service, for example GlobalSystick.
 * @return 0 on success, -1 if an input pointer is invalid or timer setup fails.
 */
int App_init(Application_t * app, volatile uint32_t* Tim ){
    
    if(app == NULL || Tim == NULL)return -1;

    char msg[SIZE_MESSAGE];
    int8_t tmpNumberOfChar = -1;

    ST7789_Init();
    ST7789_DrawImage(0,0,240,240,&StartImage[0][0]);
    
    app->StepInit = STEP_INIT_DISPLAY_FIRST_IMAGE;
    app->Error[0] = '\0';
    app->rectPercentage = 0;

    char count[50];
    app->StepRun = 0;
    app->flag.all = 0;

    app_copy_string(app->Message, SIZE_MESSAGE, BIENVENUE);

    if(timer_init_serv(&app->ApplicationTimer, Tim) == -1){
        app_copy_string(app->Error, SIZE_ERROR_MESSAGE, ERROR_002);
        ST7789_WriteStringTransparent(20,20,app->Error,Font_11x18,WHITE,StartImage);
        return -1;
    }

    if(timer_init_serv(&app->TimeractualHourUpdate, Tim) == -1){
        app_copy_string(app->Error, SIZE_ERROR_MESSAGE, ERROR_002);
        ST7789_WriteStringTransparent(20,20,app->Error,Font_11x18,WHITE,StartImage);
        return -1;
    }

    app_copy_string(msg, SIZE_MESSAGE,"WELCOMES TO");
    ST7789_WriteStringTransparent(60,180,msg,Font_11x18,WHITE,StartImage);
    timer_delay_ms(1000);

    //clean msg
    tmpNumberOfChar = numberOfChar(msg);
    restore_photo_area(70, 180, tmpNumberOfChar*11 ,18,StartImage);

    //New message
    app_copy_string(msg, SIZE_MESSAGE, "THE GWETH FAM'S");
    ST7789_WriteStringTransparent(38,180,msg,Font_11x18,WHITE,StartImage);    

    //Draw the rectangle
    timer_delay_ms(1000);
    //ST7789_DrawRectangle(0,221,239,239,WHITE);

    //float a = 239.0f/100.0f;
    //while(app->rectPercentage <= 100){
        
    ST7789_DrawRectangle(BAR_X, BAR_Y, BAR_X + BAR_W - 1, BAR_Y + BAR_H, BAR_BORDER);        timer_delay_ms(200);
    uint16_t previous_width = 0;
    //}
    if(IntToChar(0,count,'%')>0)app_copy_string(msg, SIZE_MESSAGE, count);

    for (uint8_t percent = 0; percent <= 100; ) {
        uint16_t current_width = ((BAR_W - 2) * percent) / 100;

        if (current_width > previous_width) {
            ST7789_DrawFilledRectangle(
                BAR_X + 1 + previous_width,
                BAR_Y + 1,
                current_width - previous_width,
                BAR_H - 1,
                BAR_FILL
            );

            previous_width = current_width;
        }
        //clean msg

        tmpNumberOfChar = numberOfChar(msg);
        restore_photo_area(100, 198, tmpNumberOfChar*11 ,18,StartImage);
        if(IntToChar(percent,count,'%')>0)app_copy_string(msg, SIZE_MESSAGE,count);
        ST7789_WriteStringTransparent(100,198,msg,Font_11x18,WHITE,StartImage);
        
        percent+=5;

        timer_delay_ms(200);
    }
    //Todo: try to implement feature that trnasform int to char
    //next step
    return 0;

}


/**
 * @brief Execute one iteration of the application state machine.
 *
 * INIT_RUN draws the main background once, then EXEC_RUN keeps the displayed
 * clock updated without blocking the main loop.
 *
 * @param app Application object to run.
 */
void App_run(Application_t * app){
    if(app == NULL)return;

    switch (app->StepRun)
    {
    case INIT_RUN:
        App_start(app);
        if(app->flag.bit.init_done == TRUE){
            app->StepRun = EXEC_RUN;
        }
        break;
    case EXEC_RUN:
        Udapte_hour(app);
        break;
    
    default:
        break;
    }

}

/**
 * @brief Draw the main application screen after the startup sequence.
 *
 * The function displays the 240x240 background image and marks the application
 * as initialized so App_run can enter the execution state.
 *
 * @param app Application object to start.
 */
void App_start(Application_t * app){
    if(app == NULL)return;
    ST7789_DrawImage(0,0,240,240,&image_240x240[0][0]);
    app->flag.bit.init_done = TRUE;
    
}
