#include "Application.h"

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
            (uint16_t *)&image[y+row][x]
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
    ST7789_DrawImage(0,0,240,240,(uint16_t*)StartImage);
    
    app->StepInit = STEP_INIT_DISPLAY_FIRST_IMAGE;
    app->Error[0] = '\0';
    app->rectPercentage = 0;

    app_copy_string(app->Message, SIZE_MESSAGE, BIENVENUE);

    if(timer_init_serv(&app->ApplicationTimer, Tim) == -1){
        app_copy_string(app->Error, SIZE_ERROR_MESSAGE, ERROR_002);
        ST7789_WriteStringTransparent(20,20,app->Error,Font_11x18,WHITE);
        return -1;
    }

    app_copy_string(msg, SIZE_MESSAGE,"WELCOMES TO");
    ST7789_WriteStringTransparent(70,180,msg,Font_11x18,WHITE);
    timer_delay_ms(1000);

    //clean msg
    tmpNumberOfChar = numberOfChar(msg);
    restore_photo_area(70, 180, tmpNumberOfChar*11 ,18,StartImage);

    //New message
    app_copy_string(msg, SIZE_MESSAGE, "THE GWETH FAM'S");
    ST7789_WriteStringTransparent(30,180,msg,Font_11x18,WHITE);    

    //Draw the rectangle
    timer_delay_ms(1000);
    //ST7789_DrawRectangle(0,221,239,239,WHITE);

    //float a = 239.0f/100.0f;
    //while(app->rectPercentage <= 100){
        
    ST7789_DrawRectangle(BAR_X, BAR_Y, BAR_X + BAR_W - 1, BAR_Y + BAR_H, BAR_BORDER);        timer_delay_ms(200);
    uint16_t previous_width = 0;
    //}
    for (uint8_t percent = 0; percent <= 100; percent++) {
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

        timer_delay_ms(200);
    }

    return 0;

}
