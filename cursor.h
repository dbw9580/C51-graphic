#include "defs.h"
#include "vbuf.h"

#ifndef _CURSOR_H
#define _CURSOR_H

struct _Cursor {
    curPos_t x;
    curPos_t y;
};
typedef struct _Cursor Cursor;

/* global variable indicates the current position of the cursor */
extern Cursor data cursor; 
extern uint8_t data blink_delay;
extern bit cursor_is_set;
extern void cursor_blink();

/* this macsro converts cursor coordinates to vbuf memory index */
/* the difference between BUFPOS is that cursor is always at the last line 
   pixels of a character */
#define CURPOS(x, y) \
    (BUFPOS((x), (y)) + (CHAR_ROW_SPAN - 1) * VBUF_COLS)

#define CURSOR_SET()     \
    cursor_is_set = 1;   \
    vbuf_block_write(CURPOS(cursor.x, cursor.y), 1, 1, 0, NULL, 0xff)

#define CURSOR_CLR()     \
    cursor_is_set = 0;   \
    vbuf_block_write(CURPOS(cursor.x, cursor.y), 1, 1, 0, NULL, 0)

#endif