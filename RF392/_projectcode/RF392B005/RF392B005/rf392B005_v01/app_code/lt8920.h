#ifndef _LT8920_H_
#define _LT8920_H_


//void SPI_WriteReg(void);
void SPI_WriteReg(unsigned char regval, unsigned char hval,unsigned char lval);
void SPI_WriteFifo(void);
void LT8900_Reset(void);
void LT8900Reg_Init(void);
void It8920_ResetFifo(void);
void It8920_Idle(void);
void LT8900rf_test(void);
void It8920_EnterRx(void);
void It892_EnterTx(void);
void LT8900_txdata(void);
void It8920_filldata(void);
void It8920_encryptdata(void);
void It8920_Sleep(void);
void user8920_txdata(void);
void SPI_ReadReg(unsigned char ltreg);
#endif

