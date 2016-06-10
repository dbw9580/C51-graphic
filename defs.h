#ifndef _DEFS_H
#define _DEFS_H

#define NULL 0
#define VBUF_ROWS 90
#define VBUF_COLS 16
#define CHAR_ROWS 10
#define CHAR_COLS 16
#define CHAR_ROW_SPAN 9
#define USERSPACE_ROW 36
#define USERSPACE_ROWS (VBUF_ROWS - USERSPACE_ROW)
#define USERSPACE_CHAR_ROW 4
#define USERSPACE_CHAR_ROWS (CHAR_ROWS - USERSPACE_CHAR_ROW)
#define USERSPACE_OFFSET (USERSPACE_ROW * VBUF_COLS)  

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned char curPos_t;
typedef unsigned int vbufOffset_t; 

#endif