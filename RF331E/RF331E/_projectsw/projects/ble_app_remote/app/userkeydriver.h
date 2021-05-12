#ifndef __USERKEYDRIVER__H
#define __USERKEYDRIVER__H

/*
*CH0--3
**io key press change the ch
**kai {ch,0x11,0x00}
**guan{ch,0x11,0x01}
**liangdu + {0x15,0x00}
**liangdu - {0x15,0x01}
**sewen nuan {0x1d,0x00}
**sewen leng {0x1d,0x01}
**mode hui ke{0x0d,0x00}
**     ye deng {0x0d,0x03}
**     ying yuan{0x0d,0x02}
**     yu le {0x0d, 0x01}

[4][5]---[row][col]
H:--[0...4]
L:--[0..3]
**
sw17 0x0101  ----quan kai
sw13 0x0102  ----quan guan
sw9  0x0104---ye deng
sw5  0x0108---yule
sw1  0x0110---se wen leng

sw18 0x0201----ying yuan
sw14 0x0202-----hui ke
sw10 0x0204-----laingdu-
sw6  0x0208-----liangdu +
sw2  0x0210----se wen nuan

sw19  0x0401 --leng key
sw15  0x0402-----1 guan
sw11  0x0404-----3guan
sw7   0x0408  ----3 kai
sw3   0x0410------1 kai


sw16  0x0802-----2 kai
sw12  0x0804-----4kai
sw8   0x0808-----4guan
sw4   0x0810-----2 guan
     
*/
 #define KEYSCAN_ROW_SIZE 4	  //4--2
 #define KEYSCAN_COL_SIZE 5	   //5-1
 
 
#define KEYSW17_QUANKAI           0x0101
#define KEYSW13_QUANGUAN          0x0102
#define KEYSW9_YEDENG_MODE        0x0104
#define KEYSW5_YULE_MODE          0x0108
#define KEYSW1_LENGSEWEN          0x0110

#define KEYSW18_YINGYUAN_MODE     0x0201
#define KEYSW14_HUIKE_MODE        0x0202
#define KEYSW10_LIANGDU_DEC       0x0204
#define KEYSW06_LIANGDU_INC       0x0208
#define KEYSW02_SEWEN_NUAN        0x0210

#define KEYSW19_LEARN             0x0401

#define KEYSW15_GUAN_GROUP0       0x0402   
#define KEYSW11_GUAN_GROUP2       0x0404
#define KEYSW7_KAI_GROUP2         0x0408
#define KEYSW3_KAI_GROUP0         0x0410

#define KEYSW16_KAI_GROUP1        0x0802

#define KEYSW12_KAI_GROUP3        0x0804

#define KEYSW8_GUAN_GROUP3        0x0808
#define KEYSW4_GUAN_GROUP1        0x0810

//-----double key-----
//#define KEY_LDINC_SWLENG      0x0318  //0x0110+0x0208 =0x0318
//#define KEY_LDINC_SWNUAN      0x0218 //0x0210	+ 0x0208 = 0x0218

//#define KEY_LDDEC_SWNUAN	  0x0214//0x0210 + 0x0204
//#define KEY_LDDEC_SWLENG      0x0314	  //0x0110 + 0x0204

//----three key ----
//-#define key_LDINC_SWLENG_SWRUANG	 0x0318//0x0318 + 0x0210
#define KEY_LDINC_LDDEC_SWRUANG	0x021c	//	 0x0218 + 0x0204
//#define key_LDDEC_SWRUANG_SWLENG   0x0314//0x0214 + 0x0110
#define KEY_LDINC_LDDEC_SWLENG	  0x031c//0x0314 +  0x0208

//---wifi linkage---
#define KEY_WIFIRST_LDINC 			0x0319		//0x0311 + 0x0208 liangdu inc 
#define KEY_WIFIRST_LDDEC			0x0315//0x0311 + liangdu dec	  0x0204
#define KEY_WIFIRST_LDDEC_LDINC		0x031d//0x0319 + 0x0204 liangdu dec + inc
							
//----test mode key---
#define KEYSW8SW4_RFWAVE_TST        0x0818//0x0808+	0x0810

#define	KEYSW15SW11_VERSION  	  0x0406//0x0402 + 0x0404

#define	KEYSW16SW12_FACTORYWAVE  	  0x0806//0x0802 + 0x0804

//----------wifi rest key---
#define	KEYSW18SW1_WIFIRST 		   0x0311//0x0201+ 0x0110

//-----------RF331E----KEY difine
#define KEYSW12_KAI_GROUP0         0x0804//0x0410
#define KEYSW8_GUAN_GROUP0         0x0808//0x0402  
#define KEYSW5_KAI_GROUP1          0x0108//0x0802
#define KEYSW9_GUAN_GROUP1         0x0104//0x0810
#define KEYSW16_KAI_GROUP2         0x0802//0x0408
#define KEYSW4_GUAN_GROUP2         0x0810//0x0404
#define KEYSW1_KAI_GROUP3          0x0110//0x0804
#define KEYSW13_GUAN_GROUP3        0x0102//0x0808
#define KEYSW17_LIANGDU_INC        0x0101//0x0208
#define KEYSW10_SEWEN_NUAN         0x0204 //0x0210
#define KEYSW11_LENGSEWEN          0x0404//0x0110
#define KEYSW18_LIANGDU_DEC        0x0201//0x0204
#define KEYSW02_HUIKE_MODE         0x0210//0x0202
#define KEYSW03_YULE_MODE          0x0410//0x0108
#define KEYSW14_YINGYUAN_MODE      0x0202//0x0201
#define KEYSW15_YEDENG_MODE        0x0402//0x0104
#define KEYSW6_QUANKAI             0x0208//0x0101
#define KEYSW7_QUANGUAN            0x0408//0x0102
//#define KEYSW19_LEARN             0x0401
//-----double key-----
#define KEY_LDINC_SWLENG      0x0505//0x0318  //  0x0404+0x0101=0x0505 0x0110+0x0208 =0x0318

#define KEY_LDINC_SWNUAN      0x0305//0x0218 //0x0204+0x0101=0x0305     0x0210	+ 0x0208 = 0x0218

#define KEY_LDDEC_SWNUAN	    0x0205//0x0214//0x0201 +0x0204=0x0205          + 0x0210 + 0x0204
#define KEY_LDDEC_SWLENG      0x0605//0x0314	  //0x0404+0x0201=0x0605  0x0110 + 0x0204

//----three key ----

//#define KEY_LDINC_LDDEC_SWRUANG	0x0305//0x021c	//	0x0305+0x0201=0x0305              0x0218 + 0x0204
#define key_LDINC_SWLENG_SWRUANG	 0x0705//0x0318//    0x0505 +0x0204=0x0705             0x0318 + 0x0210
//#define KEY_LDINC_LDDEC_SWLENG	  0x031c//           0x0605 + 0x0101 =0x0705            0x0314 +  0x0208
#define key_LDDEC_SWRUANG_SWLENG   0x0605//0x0314//            0x0205 + 0x0404 = 0x0605            0x0214 + 0x0110
//---wifi linkage---
#define KEY_WIFIRST_LDINC 			0x0319		//0x0311 + 0x0208 liangdu inc 
#define KEY_WIFIRST_LDDEC			0x0315//0x0311 + liangdu dec	  0x0204
#define KEY_WIFIRST_LDDEC_LDINC		0x031d//0x0319 + 0x0204 liangdu dec + inc

//----test mode key---
#define KEYSW13SW9_RFWAVE_TST        0x0106//0x0818//0x0102 + 0x0104 =0x0106  0x0808+	0x0810

#define	KEYSW8SW4_VERSION  	        0x0818 //0x0406//0x0808 + 0x0810 = 0x0818  0x0402 + 0x0404

#define	KEYSW5SW1_FACTORYWAVE  	    0x0118//0x0806//0x0108 + 0x0110 = 0x0118 0x0802 + 0x0804

//----------wifi rest key---
#define	KEYSW14SW11_WIFIRST 		   0x0606//0x0311//0x0202 + 0x0404=0x0606   0x0201+ 0x0110


void vuserkeyinit(void);
void keyvaluehandle(void);
void vkeyscan(void);
void keyrowstatus(bool up20, bool up21, bool up31, bool up32);
 void clr_longkeysteprfsend(void);
void clr_keylinkage(void);
//---------void user_setup_rfpackage(void);
void clr_keypeidui(void);


















#endif


















