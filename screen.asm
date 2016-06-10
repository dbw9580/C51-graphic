NAME SCREEN

XSCAN           BIT      P3.0              ;X 轴扫描控制信号
ENSHIFT         BIT      P3.1              ;移位寄存器控制信号
OUTDAC          EQU     9000H              ;DAC0832地址，即Y轴扫描信号
VBUFEND         EQU     0590H              ;VBUF最后一行的内存地址

?PR?SCREEN_SCAN_SEG?SCREEN SEGMENT CODE
?PR?DAC_SEG?SCREEN SEGMENT CODE
PUBLIC SCREEN_SCAN

CSEG AT 001BH
    LJMP SCREEN_SCAN

RSEG ?PR?SCREEN_SCAN_SEG?SCREEN

SCREEN_SCAN:
    USING 1
    MOV  TH1,#0A6H
    MOV  TL1,#00H                         ;重置T1定时器计时25ms
    PUSH DPH
    PUSH DPL
    PUSH ACC
    PUSH PSW
    SETB RS0
    CLR  RS1
                        
    MOV DPTR,#VBUFEND                     ;2Tc由最后一行开始扫屏
    MOV R5,#90                            ;1Tc共90 行
    MOV R6,#00H                           ;1TcDAC列扫描从最低开始扫描
    LCALL DACFUNC
LOOP1:                                    ;1Tc 在X_SCAN 口产生低脉宽为192Tc,高脉宽为20Tc 左右的锯齿波控制信号
    MOV R4,#10H                           ;1Tc 
    CLR XSCAN                             ;1Tc 锯齿波控制信号置低
LOOP2:                                    ;在SHIFTREG口产生周期为12Tc,高脉宽为10Tc,低脉宽为2Tc的脉冲波
    MOVX A,@DPTR                          ;2Tc
    MOV P1,A                              ;1Tc 载入字模
    CLR ENSHIFT                           ;1Tc
    NOP                                   ;1Tc 保证SHIFTREG 2Tc的负脉宽
    SETB ENSHIFT                          ;1Tc
    INC DPTR                              ;2Tc
    NOP                                   ;1Tc
    NOP                                   ;1Tc 保证SHIFTREG 10Tc的正脉宽
    DJNZ R4,LOOP2                         ;2Tc
    NOP                                   ;1Tc
    NOP                                   ;1Tc
    NOP                                   ;1Tc 补足最后一个字符的正脉宽
    SETB XSCAN                            ;1Tc 锯齿波控制信号置高
    CLR C                                 ;1Tc
    MOV A,DPL                             ;1Tc
    SUBB A,#20H                           ;2Tc DPTR 指向上一行的起始地址
    MOV DPL,A                             ;1Tc
    MOV A,DPH                             ;1Tc
    SUBB A,#00H                           ;2Tc 是否有借位，扫描数据向上增加一行
    MOV DPH,A                             ;1Tc
    MOV A,R6                              ;1Tc
    ADD A,#02H                            ;2Tc DAC列扫描向上增加一列
    MOV R6,A                              ;1Tc
    LCALL DACFUNC
    DJNZ R5,LOOP1 
    CLR RS0
    CLR RS1
    POP PSW
    POP ACC
    POP DPL
    POP DPH
    RETI

RSEG ?PR?DAC_SEG?SCREEN

DACFUNC:                                  ;共需要15Tc
    PUSH DPH                              ;2Tc
    PUSH DPL                              ;2Tc
    MOV DPTR,#OUTDAC                      ;2Tc
    MOV A,R6                              ;1Tc
    MOVX @DPTR,A                          ;2Tc
    POP DPL                               ;2Tc
    POP DPH                               ;2Tc
    RET                                   ;2Tc

END