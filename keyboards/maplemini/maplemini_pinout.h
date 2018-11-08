/*
const ioportid_t col_pins[MATRIX_COLS]={GPIOB,GPIOB,GPIOB,GPIOB,GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,GPIOC,GPIOC,GPIOC};
const uint8_t col_pads[MATRIX_COLS]={11,10,2,0,7,6,5,4,3,2,1,0,15,14,13};
const ioportid_t row_pins[MATRIX_ROWS]={GPIOB,GPIOB,GPIOB,GPIOA,GPIOA};
const uint8_t row_pads[MATRIX_ROWS]={5,4,3,15,14};
*/
//COLs
#define MP0 PAL_LINE(GPIOB,11)
#define MP1 PAL_LINE(GPIOB,10)
#define MP2 PAL_LINE(GPIOB,2)
#define MP3 PAL_LINE(GPIOB,0)
#define MP4 PAL_LINE(GPIOA,7)
#define MP5 PAL_LINE(GPIOA,6)
#define MP6 PAL_LINE(GPIOA,5)
#define MP7 PAL_LINE(GPIOA,4)
#define MP8 PAL_LINE(GPIOA,3)
#define MP9 PAL_LINE(GPIOA,2)
#define MP10 PAL_LINE(GPIOA,1)
#define MP11 PAL_LINE(GPIOA,0)
#define MP12 PAL_LINE(GPIOC,15)
#define MP13 PAL_LINE(GPIOC,14)
#define MP14 PAL_LINE(GPIOC,13)
//boot button
#define MPBUT PAL_LINE(GPIOB,8)
//others
#define MP15 PAL_LINE(GPIOB,7)
#define MP16 PAL_LINE(GPIOB,6)

//ROWs
#define MP17 PAL_LINE(GPIOB,5)
#define MP18 PAL_LINE(GPIOB,4)
#define MP19 PAL_LINE(GPIOB,3)
#define MP20 PAL_LINE(GPIOA,15)
#define MP21 PAL_LINE(GPIOA,14)
//
//others
#define MP22 PAL_LINE(GPIOA,13)
#define MP23 PAL_LINE(GPIOA,12)
#define MP24 PAL_LINE(GPIOA,11)
#define MP25 PAL_LINE(GPIOA,10)
#define MP26 PAL_LINE(GPIOA,9)
#define MP27 PAL_LINE(GPIOA,8)
#define MP28 PAL_LINE(GPIOB,15)
#define MP29 PAL_LINE(GPIOB,14)
#define MP30 PAL_LINE(GPIOB,13)
#define MP31 PAL_LINE(GPIOB,12)
