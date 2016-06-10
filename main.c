#include <reg51.h>

#include "keys.h"
#include "vbuf.h"
#include "cursor.h"


sbit XSCAN = 0xB0;
sbit ENSHIFT = 0xB1;

extern void SCREEN_SCAN();

void sys_init(){
    uint8_t i = 0xff;
    KEYBOARD_C = 0xD3;  /* clear ram and FIFO */
    for( ; i > 0; i--); /* delay to wait for 8279 getting ready*/ 
    KEYBOARD_C = 0x00;  /* set scan mode */
    KEYBOARD_C = 0x32;  /* set freq */
    
    VBUF_INIT();        /* initializing video buffer */
    cursor.x = 0;       /* put cursor at the first character of the first 
                           userspace line */
    cursor.y = USERSPACE_CHAR_ROW;
 
    XSCAN = 1;
    ENSHIFT = 1;

    /* Timer math:
     * fc (CPU frequency) = 11.052MHz, so Tc = 1.0858us
     * T0 times the blinking cursor with a period of 50ms
     * T1 times the screen refreshing function with a period of 25ms
     * 50ms = 46079 * 1.0858us, 25ms = 23040 * 1.0858us
     */
    TMOD = 0x11;        /* both timers in 16-bit mode */
    TH0 = 0x4c;         /* T0: 4C00H = 19456D = 65536 - 46079 */
    TL0 = 0x00;         
    TH1 = 0xa6;         /* T1: A600H = 42496D = 65536 - 23040 */
    TL1 = 0x00;

    PT1 = 1;            /* timer1 has priority */
    IE = 0x8b;          /* Interrupts: INT0, T0, T1*/
    TR0 = 1;            /* start timers */
    TR1 = 1;
}


int main(){
    sys_init();
    
    /* tests
    //cursor moves at margins 
    cursor.x = 0;
    cursor.y = USERSPACE_CHAR_ROW + 1;
    CURSOR_SET();
    CURSOR_LEFT();
    CURSOR_SET();
    
    cursor.x = CHAR_COLS - 1;
    cursor.y = USERSPACE_CHAR_ROW + 2;
    CURSOR_SET();
    CURSOR_RIGHT();
    CURSOR_SET();
     
    cursor.x = 1;
    cursor.y = CHAR_ROWS - 1;
    CURSOR_SET();
    CURSOR_RETURN();
    CURSOR_SET();
    
    //roll up and down 
    VBUF_BLACK_OUT(0xff);
    VBUF_CLEAR_CHARACTER(4, 6);
    ROLL_UP();
    VBUF_CLEAR_CHARACTER(4, 4);
    ROLL_DOWN();
    
    //clear userspace 
    VBUF_CLEAR_USERSPACE();
    */
    
    while(1);
    
    return 0;
}