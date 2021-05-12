        

message '***************************************************************'
message '*PROJECT NAME :USER PROGRAM CODE                              *'
message '*     VERSION :                                               *'
message '*     IC BODY :                                               *'
message '* ICE VERSION :                                               *'
message '*      REMARK :                                               *'
message '***************************************************************'

                INCLUDE USER_PROGRAM.INC

                PUBLIC  _USER_PROGRAM_INITIAL
                PUBLIC  _USER_PROGRAM 

#define keycnt 80H
                ;========================
                ;=USER DATA DEFINE      =
                ;========================
USER_DATA       .SECTION   'DATA'



                ;========================
                ;=USER PROGRAM          =
                ;========================
USER_PROGRAM    .SECTION   'CODE'
                           
;;***********************************************************                           
;;*SUB. NAME:USER INITIAL PROGRAM                           *                           
;;*INPUT    :                                               *                           
;;*OUTPUT   :                                               *                           
;;*USED REG.:                                               *                           
;;*FUNCTION :                                               *                           
;;***********************************************************                           
                      ;;************************
_USER_PROGRAM_INITIAL:;;* USER_PROGRAM_INITIAL *
                      ;;************************

               CLR     PAC
               CLR     PA
               CLR     PBC
               CLR     PB

                RET




;;***********************************************************                           
;;*SUB. NAME:USER_MAIN                                      *                           
;;*INPUT    :                                               *                           
;;*OUTPUT   :                                               *                           
;;*USED REG.:                                               *                           
;;*FUNCTION :                                               *                           
;;***********************************************************                           
                ;;********************
_USER_PROGRAM:  ;;USER PROGRAM ENTRY *
                ;;********************



                SNZ     _SCAN_CYCLEF;不为0，则跳过，按键扫描完成
                RET
                CLR     PAC.4
                
                SNZ     _ANY_KEY_PRESSF
                CLR     PA.4
                SZ      _ANY_KEY_PRESSF
                SET     PA.4
                RET

_USER_KEYSCAN:
         		SNZ     _SCAN_CYCLEF;不为0，则跳过
                RET		
             ;按键扫描完成
			
                SZ      _ANY_KEY_PRESSF;判断是否有按键按下，不为0，有按键按下；=0，则跳过
                _GET_KEY_BITMAP ;有按键按下
                RET
				
 mov A, _DATA_BUF[0];按键状态值
 xor a,01h;k1
 snz STATUS.2;如果不为0，则跳过下条指令
 ；...jmp k1key
 
  mov A, _DATA_BUF[0];按键状态值
 xor a,02h;k2
 snz STATUS.2;如果不为0，则跳过下条指令
 ；...jmp k2key
 
   mov A, _DATA_BUF[0];按键状态值
 xor a,04h;k3
 snz STATUS.2;如果不为0，则跳过下条指令
 ；...jmp k3key
 
    mov A, _DATA_BUF[0];按键状态值
 xor a,08h;k4
 snz STATUS.2;如果不为0，则跳过下条指令
 ；...jmp k4key
 
     mov A, _DATA_BUF[0];按键状态值
 xor a,010h;k5
 snz STATUS.2;如果不为0，则跳过下条指令
 ；...jmp k5key
 
      mov A, _DATA_BUF[0];按键状态值
 xor a,020h;k6
 snz STATUS.2;如果不为0，则跳过下条指令
 ；...jmp k6key
 
       mov A, _DATA_BUF[0];按键状态值
 xor a,040h;k7
 snz STATUS.2;如果不为0，则跳过下条指令
 ；...jmp k7key
 

 
 sz _DATA_BUF[0].1; 如果bit1为0，则跳过下一条指令
  inc  keycnt
   sz _DATA_BUF[0].2; 如果bit2为0，则跳过下一条指令
  inc  keycnt
   sz _DATA_BUF[0].3; 如果bit3为0，则跳过下一条指令
  inc  keycnt
   sz _DATA_BUF[0].4; 如果bit4为0，则跳过下一条指令
  inc  keycnt
   sz _DATA_BUF[0].5; 如果bit5为0，则跳过下一条指令
  inc  keycnt
   sz _DATA_BUF[0].6; 如果bit0为0，则跳过下一条指令
  inc  keycnt

  mov A,keycnt
  sub A,03h
  
   sz STATUS.0 ;如果为0，则跳过下一条指令
   ；...jmp k7key
 

 
 
 


