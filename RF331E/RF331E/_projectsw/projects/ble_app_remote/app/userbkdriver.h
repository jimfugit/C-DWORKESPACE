#ifndef __USERBKDRIVER_H
#define __USERBKDRIVER_H

 void rf_packagesend(void);

void user_access_rfaddressInit(void);
 void rf_received_package(void);
 void keylearnprocess(void);
 void IIC_ClrMacaddr(void);
  void user_rftxmode(void);
   void user_readmac_eeprom(void);
    uint8_t user_factorytestiic(void);
#endif



