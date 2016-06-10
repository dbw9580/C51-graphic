#include "defs.h"

#ifndef _VBUF_H
#define _VBUF_H

#define BANNER_LEN 480
extern unsigned char xdata vbuf[VBUF_ROWS * VBUF_COLS];
extern unsigned char code cmap[7][9];
extern unsigned char code banner[BANNER_LEN];

#define CMAP_A cmap[1]
#define CMAP_B cmap[2]
#define CMAP_C cmap[3]
#define CMAP_D cmap[4]
#define CMAP_E cmap[5]
#define CMAP_F cmap[6]
#define CMAP_SPACE cmap[0]

/* converts coordinates to memory index of vbuf */
#define BUFPOS(x, y) \
    (((vbufOffset_t)y) * CHAR_ROW_SPAN * VBUF_COLS + ((vbufOffset_t)x))

extern void vbuf_block_write(
    vbufOffset_t top_left, 
    uint8_t width,
    uint8_t height,
    uint16_t buflen, 
    unsigned char *buf,
    uint8_t fillwith
) reentrant;

#define VBUF_INIT() \
    vbuf_block_write(0, VBUF_COLS, VBUF_ROWS, BANNER_LEN, banner, 0)
    
#define VBUF_SET_CHARACTER(x, y, cmap) \
    vbuf_block_write(BUFPOS((x), (y)), 1, CHAR_ROW_SPAN, CHAR_ROW_SPAN, (cmap), 0)
    
#define VBUF_CLEAR_CHARACTER(x, y)     \
    vbuf_block_write(BUFPOS((x), (y)), 1, CHAR_ROW_SPAN, 0, NULL, 0)
    
#define VBUF_CLEAR_USERSPACE()         \
    vbuf_block_write(USERSPACE_OFFSET, VBUF_COLS, USERSPACE_ROWS, \
        0, NULL, 0)

/* for debug use */
#define VBUF_BLACK_OUT(mask)               \
    vbuf_block_write(0, VBUF_COLS, VBUF_ROWS, 0, NULL, (mask))

#endif