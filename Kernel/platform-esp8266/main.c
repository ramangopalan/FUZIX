#include <stdint.h>
#include "esp8266_peri.h"
#include "kernel.h"
#include "kdata.h"
#include "printf.h"
#include "globals.h"
#include "rom.h"
#include "kernel-esp8266.def"

uaddr_t ramtop = DATATOP;
uint8_t need_resched;
uint16_t swap_dev = 0xFFFF;

void map_init(void) {}
void platform_discard(void) {}

void platform_monitor(void)
{
	while(1);
}

void platform_reboot(void)
{
	system_restart();
}

uint_fast8_t platform_param(char* p)
{
	return 0;
}

int main(void)
{
	di();
	/* Check offsets */

	if ((U_DATA__U_SP != offsetof(struct u_data, u_sp)) ||
	    (U_DATA__U_PTAB != offsetof(struct u_data, u_ptab)) ||
	    (P_TAB__P_PID_OFFSET != offsetof(struct p_tab, p_pid)) ||
		(P_TAB__P_STATUS_OFFSET != offsetof(struct p_tab, p_status)))
	{
		kprintf("U_DATA__U_SP = %d\n", offsetof(struct u_data, u_sp));
		kprintf("U_DATA__U_PTAB = %d\n", offsetof(struct u_data, u_ptab));
		kprintf("P_TAB__P_PID_OFFSET = %d\n", offsetof(struct p_tab, p_pid));
		kprintf("P_TAB__P_STATUS_OFFSET = %d\n", offsetof(struct p_tab, p_status));
		panic("bad offsets");
	}
	

	ramsize = 80;
	procmem = 64;
	kputs("\n\n\n");
	sys_cpu_feat = AF_LX106_ESP8266;

	fuzix_main();
}

/* vim: sw=4 ts=4 et: */
