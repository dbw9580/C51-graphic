#include "keys.h"
#include "vbuf.h"

/* keyboard control port */
volatile uint8_t xdata KEYBOARD_C _at_ 0xA001;
/* ketboard data port */
volatile uint8_t xdata KEYBOARD_D _at_ 0xA000;

/* 
* 键值
* 0C0H    A  |  0C8H    E   |  0D0H   F1(L) |  0D8H  F5(LCLR)
* 0C1H    B  |  0C9H    F   |  0D1H   F2(R) |  0D9H  F6(RCLR)
* 0C2H    C  |  0CAH  SPACE |  0D2H  F3(RTN)|  0DAH   F7(RU)
* 0C3H    D  |  0CBH   RST  |  0D3H  F4(CLR)|  0DBH   F8(RD)
*/
void key_broker() interrupt 0 {
    KEYBOARD_C = 0x80; /* set to FIFO read mode */
    switch(KEYBOARD_D) {
        case 0xC0:
            CURSOR_SET_CHARACTER(CMAP_A);
            break;
        case 0xC1:
            CURSOR_SET_CHARACTER(CMAP_B);
            break;
        case 0xC2:
            CURSOR_SET_CHARACTER(CMAP_C);
            break;
        case 0xC3:
            CURSOR_SET_CHARACTER(CMAP_D);
            break;
        case 0xC8:
            CURSOR_SET_CHARACTER(CMAP_E);
            break;
        case 0xC9:
            CURSOR_SET_CHARACTER(CMAP_F);
            break;
        case 0xCA:
            CURSOR_SET_CHARACTER(CMAP_SPACE);
            break;
        case 0xD0:
            CURSOR_LEFT();
            break;
        case 0xD1:
            CURSOR_RIGHT();
            break;
        case 0xD2:
            CURSOR_RETURN();
            break;
        case 0xD3:
            VBUF_CLEAR_USERSPACE();
            cursor.x = 0;
            cursor.y = USERSPACE_CHAR_ROW;
            break;
        case 0xD8:
            CURSOR_LEFT_CLEAR();
            break;
        case 0xD9:    
            CURSOR_RIGHT_CLEAR();
            break;
        case 0xDA:
            ROLL_UP();
            break;
        case 0xDB:
            ROLL_DOWN();
            break;
    }
}

void ROLL_DOWN(){
    vbufOffset_t offset;
    
    CURSOR_CLR();
    for(offset = VBUF_ROWS * VBUF_COLS - 1; 
        offset >= USERSPACE_OFFSET +  CHAR_ROW_SPAN * VBUF_COLS;
        offset--){
            
        vbuf[offset] = vbuf[offset - CHAR_ROW_SPAN * VBUF_COLS];
    }

    for(offset = USERSPACE_OFFSET; offset <= USERSPACE_OFFSET + VBUF_COLS * CHAR_ROW_SPAN;
    offset++){
        vbuf[offset] = 0;
    }
    if (cursor.y < CHAR_ROWS){
        cursor.y++;
    }
}