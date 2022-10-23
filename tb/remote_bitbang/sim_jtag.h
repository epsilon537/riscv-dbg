#ifndef SIM_JTAG_H
#define SIM_JTAG_H

#ifdef __cplusplus
extern "C" {
#endif
  
  int jtag_tick(int port, unsigned char *jtag_TCK, unsigned char *jtag_TMS,
		unsigned char *jtag_TDI, unsigned char *jtag_TRSTn,
		unsigned char jtag_TDO);

  //When invoked with set_bypass=1, jtag_tick() will do nothing. Otherwise
  //jtag_tick will open openocd remote_bitbang socket.
  void jtag_set_bypass(int set_bypass);
  
#ifdef __cplusplus
}
#endif

#endif /*SIM_JTAG_H*/
