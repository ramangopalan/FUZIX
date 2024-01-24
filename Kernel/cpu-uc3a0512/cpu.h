#include <string.h>
#include "compiler.h"

#undef  LITTLE_ENDIAN
#define BIG_ENDIAN

#ifndef __packed
#define __packed  __attribute__((packed))
#endif

#define ALIGNUP(v)   alignup(v, 4)
#define ALIGNDOWN(v) aligndown(v, 4)

#define uputp    uputl          /* Copy user pointer type */
#define ugetp(x) ugetl(x)       /* between user and kernel */
#define uputi    uputl          /* Copy user int type */
#define ugeti(x) ugetl(x)	/* between user and kernel */

#define brk_limit() (udata.u_ptab->p_top)

extern void* memcpy(void*, const void*, size_t);
extern void* memset(void*, int, size_t);
extern size_t strlen(const char *);
extern uint16_t swab(uint16_t);

/* ARM M0 doesn't benefit from making a few key variables in
   non-reentrant functions static */
#define staticfast auto

typedef union {            /* this structure is endian dependent */
    clock_t  full;         /* 32-bit count of ticks since boot */
    struct {
      uint16_t low;
      uint16_t high;         /* 16-bit count of ticks since boot */
    } h;
} ticks_t;

#define used(x)

#define Swap16(u16) ((U16)(((U16)(u16) >> 8) |\
((U16)(u16) << 8)))

#define Swap32(u32) ((U32)(((U32)Swap16((U32)(u32) >> 16)) |\
((U32)Swap16((U32)(u32)) << 16)))

#define cpu_to_le16(x)	Swap16(x)
#define le16_to_cpu(x)	Swap16(x)
#define cpu_to_le32(x)  Swap32(x)
#define le32_to_cpu(x)  Swap32(x)

#ifndef __STRINGIFY
#define __STRINGIFY(a) #a
#endif

#define barrier() asm volatile("":::"memory")

#define cpu_irq_enable()\
do {\
    barrier();\
    __builtin_csrf(AVR32_SR_GM_OFFSET);\
} while (0)

#define cpu_irq_disable()\
do {\
    __builtin_ssrf(AVR32_SR_GM_OFFSET);\
    barrier();\
} while (0)

inline static uint32_t __hard_di(void)
{
    volatile uint32_t flags;

    flags = __builtin_mfsr(AVR32_SR);
    cpu_irq_disable();

    return flags;
}

inline static void __hard_ei(void)
{
    cpu_irq_enable();
}

static inline bool cpu_irq_is_enabled_flags(irqflags_t flags)
{
    return !(flags & AVR32_SR_GM_MASK);
}

inline static void __hard_irqrestore(uint32_t ps)
{
    barrier();

    /* Restore the global IRQ mask status flag if it was previously set */
    if ( cpu_irq_is_enabled_flags(ps) ) {
        cpu_irq_enable();
    }

    barrier();
}

/* jmp over the Fuzix header. Will need updating if the header size changes */
#define EMAGIC   0x08
#define EMAGIC_2 0x3c

#define no_cache_udata()

#define ntohs(x) ((uint16_t)(__builtin_bswap16((uint16_t)(x))))
#define ntohl(x) ((uint32_t)(__builtin_bswap32((uint32_t)(x))))

#define CPUTYPE	CPUTYPE_ARMM0

/* Memory helpers: Max of 32767 blocks (16MB) as written */
extern void copy_blocks(void *, void *, unsigned int);
extern void swap_blocks(void *, void *, size_t);

#define NORETURN __attribute__((__noreturn__))
#undef __fastcall
#define __fastcall /* nothing */

