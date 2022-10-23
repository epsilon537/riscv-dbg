// See LICENSE.SiFive for license details.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "remote_bitbang.h"
#include "sim_jtag.h"

static int init = 0;
static int bypass = 1;

int jtag_tick(int port, unsigned char *jtag_TCK, unsigned char *jtag_TMS,
              unsigned char *jtag_TDI, unsigned char *jtag_TRSTn,
              unsigned char jtag_TDO)

{
    if (bypass)
      return 0;
    
    if (!init) {
	if (port < 0 || port > UINT16_MAX)
	    fprintf(stderr, "Port number of out range: %d\n", port);
        init = rbs_init(port);
    }

    rbs_tick(jtag_TCK, jtag_TMS, jtag_TDI, jtag_TRSTn, jtag_TDO);
    if (0)
        fprintf(
            stderr,
            "Tick with: TCK=%hhd TMS=%hhd TDI=%hhd TRSTn=%hhd --> TDO=%hhd\n",
            *jtag_TCK, *jtag_TMS, *jtag_TDI, *jtag_TRSTn, jtag_TDO);

    return rbs_done() ? (rbs_exit_code() << 1 | 1) : 0;
}

void jtag_set_bypass(int set_bypass) {
  bypass = set_bypass;
}
  
