#include "cursor.h"
#include <reg51.h>

Cursor data cursor;
uint8_t data blink_delay = 10; /* software counter to make blink intervals longer */
bit cursor_is_set = 0;

void cursor_blink() interrupt 1{
    TH0 = 0x4C; /* reload T0 */
    TL0 = 0x00;
    if( blink_delay == 0){
        blink_delay = 10;
        if( cursor_is_set ){
            CURSOR_CLR();
        }
        else{
            CURSOR_SET();
        }
    }
    else{
        blink_delay--;
    }
    return;
}