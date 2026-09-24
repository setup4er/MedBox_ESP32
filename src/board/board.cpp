#include "board.h"

//Project headers
#include "drivers/dbg_led.h"
#include "drivers/rtc.h"
#include "config.h"

void init_board(){
    init_dbg_led();
    init_rtc();
}