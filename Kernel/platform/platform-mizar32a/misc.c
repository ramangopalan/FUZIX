#include <kernel.h>
#include <kdata.h>
#include <printf.h>
#include <exec.h>

uint8_t sys_cpu = 0;
uint8_t sys_cpu_feat = 0;
uint8_t need_resched;
uaddr_t ramtop = (uaddr_t) PROGTOP;
uint8_t sys_stubs[sizeof(struct exec)];
uint16_t swap_dev = 0xffff;

/* Unused on this port */

void set_cpu_type(void) {}
void map_init(void) {}
void plt_discard(void) {}
void plt_monitor(void) {}
void plt_reboot(void) {}
void program_vectors(uint16_t* pageptr) {}

// Raman: Fool for now.
void plt_idle(void) {}
void plt_switchout(void) {}
void switchin(ptptr process) {}
	
uint_fast8_t plt_param(char *p)
{
	return 0U;
}

uaddr_t pagemap_base(void)
{
	return PROGBASE;
}

usize_t valaddr(const uint8_t *base, usize_t size, uint_fast8_t is_write)
{
	if (base + size < base)
	size = MAXUSIZE - (usize_t)base + 1;
	if (!base || base < (const uint8_t *)PROGBASE)
	size = 0;
	else if (base + size > (const uint8_t *)(size_t)udata.u_ptab->p_top)
	size = (uint8_t *)(size_t)udata.u_ptab->p_top - base;
	if (size == 0)
	udata.u_error = EFAULT;
	return size;
}

usize_t valaddr_r(const uint8_t *pp, usize_t l)
{
	return valaddr(pp, l, 0);
}

usize_t valaddr_w(const uint8_t *pp, usize_t l)
{
	return valaddr(pp, l, 1);
}

void swap_blocks(void* p1, void* p2, size_t len)
{
    uint32_t* u1 = p1;
    uint32_t* u2 = p2;

    while (len != 0)
    {
        uint32_t t = *u1;
        *u1 = *u2;
        *u2 = t;
        u1++;
        u2++;
        len -= 4;
    }
}

/* vim: sw=4 ts=4 et: */


