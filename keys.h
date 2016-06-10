#include "defs.h"
#include "vbuf.h"
#include "cursor.h"

#ifndef _KEYS_H
#define _KEYS_H
    
#define CURSOR_LEFT()                         \
    CURSOR_CLR();                             \
    if(cursor.x > 0){                         \
        cursor.x--;                           \
    }                                         \
    else if (cursor.y > USERSPACE_CHAR_ROW){  \
        cursor.y--;                           \
        cursor.x = CHAR_COLS - 1;             \
    }                                         \
    
    
#define CURSOR_RIGHT()                        \
    CURSOR_CLR();                             \
    if(cursor.x < CHAR_COLS - 1){             \
        cursor.x++;                           \
    }                                         \
    else if (cursor.y < CHAR_ROWS - 1){       \
        cursor.y++;                           \
        cursor.x = 0;                         \
    }                                         \
    
    
#define CURSOR_RETURN()                       \
    CURSOR_CLR();                             \
    if (cursor.y < CHAR_ROWS - 1){            \
        cursor.y++;                           \
        cursor.x = 0;                         \
    }                                         \
    
#define CURSOR_LEFT_CLEAR()                   \
    CURSOR_LEFT();                            \
    VBUF_CLEAR_CHARACTER(cursor.x, cursor.y)
    
#define CURSOR_RIGHT_CLEAR()                  \
    CURSOR_RIGHT();                           \
    VBUF_CLEAR_CHARACTER(cursor.x, cursor.y)
    
#define ROLL_UP()                                           \
    CURSOR_CLR();                                           \
    vbuf_block_write(                                       \
        USERSPACE_OFFSET,                                   \
        VBUF_COLS,                                          \
        USERSPACE_ROWS,                                     \
        VBUF_COLS * (USERSPACE_ROWS - CHAR_ROW_SPAN),       \
        vbuf + USERSPACE_OFFSET + CHAR_ROW_SPAN * CHAR_COLS,\
        0                                                   \
    );                                                      \
    if (cursor.y > USERSPACE_CHAR_ROW){                     \
        cursor.y--;                                         \
    }                                                       \

#define CURSOR_SET_CHARACTER(cmap)                      \
    CURSOR_CLR();                                       \
    if( cursor.x == CHAR_COLS - 1){                     \
        if ( cursor.y < CHAR_ROWS - 1){                 \
            cursor.x = 0;                               \
            cursor.y++;                                 \
        }                                               \
        else{                                           \
            ROLL_UP();                                  \
            cursor.x = 0;                               \
        }                                               \
    }                                                   \
    VBUF_SET_CHARACTER(cursor.x, cursor.y, (cmap));     \
    CURSOR_RIGHT()

extern volatile uint8_t xdata KEYBOARD_C;
extern volatile uint8_t xdata KEYBOARD_D;    
extern void ROLL_DOWN();
extern void key_broker();
#endif    