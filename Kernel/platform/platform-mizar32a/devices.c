#include <kernel.h>
#include <version.h>
#include <kdata.h>
#include <devsys.h>
#include <blkdev.h>
#include <tty.h>
#include <devtty.h>
#include <devsd.h>
#include <printf.h>
#include "pm.h"
#include "intc.h"
#include "compiler.h"
//#include <hardware/irq.h>
//#include <hardware/structs/timer.h>
//#include <pico/multicore.h>
//#include "core1.h"

#define FCPU 66000000

struct devsw dev_tab[] =  /* The device driver switch table */
{
// minor    open         close        read      write           ioctl
// ---------------------------------------------------------------------
  /* 0: /dev/hd - block device interface */
  {  blkdev_open,   no_close,   blkdev_read,    blkdev_write,	blkdev_ioctl},  
  /* 1: /dev/fd - Floppy disk block devices */
  {  nxio_open,	    no_close,	no_rdwr,	no_rdwr,	no_ioctl},
  /* 2: /dev/tty	TTY devices */
  {  tty_open,     tty_close,   tty_read,  tty_write,  tty_ioctl },
  /* 3: /dev/lpr	Printer devices */
  {  no_open,     no_close,   no_rdwr,   no_rdwr,  no_ioctl  },
  /* 4: /dev/mem etc	System devices (one offs) */
  {  no_open,      no_close,    sys_read, sys_write, sys_ioctl  },
  /* Pack to 7 with nxio if adding private devices and start at 8 */
};

//static absolute_time_t now;

bool validdev(uint16_t dev)
{
    /* This is a bit uglier than needed but the right hand side is
       a constant this way */
    if(dev > ((sizeof(dev_tab)/sizeof(struct devsw)) << 8) - 1)
	return false;
    else
        return true;
}

/**
 * System tick interrupt handler.
 */
static void fuzix_timer_handler(void)
{
    // Clears the interrupt request.
    Set_system_register(AVR32_COMPARE, FCPU / TICKSPERSEC);

    timer_interrupt();
}

/**
 * Initialize CPU cycle counter for system tick.
 */
static void cpu_counter_init(void)
{
    INTC_register_interrupt(&fuzix_timer_handler, AVR32_CORE_COMPARE_IRQ, AVR32_INTC_INT3);
    Set_system_register(AVR32_COMPARE, FCPU / TICKSPERSEC);
    Set_system_register(AVR32_COUNT, 0);
}

void timer_tick_cb(unsigned alarm)
{
    timer_interrupt();
	//uint8_t c = platform_s_uart_recv(1, 1);
	//tty_inproc(minor(BOOT_TTY), c);
}

struct u_data *udata_ptr = NULL;
static u_block udata_blocks[PTABSIZE];

void mizar32_init (void) {
	  udata_ptr = &(udata_blocks[0].u_d);
	  ramsize = 256U;
	  procmem = 256U;
}

void device_init(void)
{
    sd_rawinit();
    devsd_init();
	//Disable_global_interrupt();
	//cpu_counter_init();
	//Enable_global_interrupt();
	//timer_init();
    /* The flash device is too small to be useful, and a corrupt flash will
     * cause a crash on startup... oddly. */
#if (0)
	flash_dev_init();
    
	sd_rawinit();
	devsd_init();

    hardware_alarm_claim(0);
    update_us_since_boot(&now, time_us_64());
    hardware_alarm_set_callback(0, timer_tick_cb);
    timer_tick_cb(0);
#endif

}

