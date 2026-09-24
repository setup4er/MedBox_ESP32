#include "board.h"

//Project headers
#include "drivers/dbg_led.h"
#include "drivers/rtc.h"
#include "config.h"

void board_init(){
    led_dbg_init();
    rtc_init();
}