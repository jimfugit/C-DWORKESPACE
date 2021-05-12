#ifndef _USER_PROGRAM_H_
#define _USER_PROGRAM_H_


typedef struct {
        unsigned char b0 : 1;
        unsigned char b1 : 1;
        unsigned char b2 : 1;
        unsigned char b3 : 1;
        unsigned char b4 : 1;
        unsigned char b5 : 1;
        unsigned char b6 : 1;
        unsigned char b7 : 1;
} _FLAG_bits;

typedef union {
        _FLAG_bits bits;
        unsigned char   byte;
}_TKS_FLAGA_type;




void user_timer_process(void);
void USER_PROGRAM(void);
void USER_PROGRAM_INITIAL(void);
unsigned char getpresskeycount(void);

#endif


