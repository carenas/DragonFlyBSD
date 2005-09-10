/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)isa.c	7.2 (Berkeley) 5/13/91
 * $FreeBSD: src/sys/i386/isa/intr_machdep.c,v 1.29.2.5 2001/10/14 06:54:27 luigi Exp $
 * $DragonFly: src/sys/platform/pc32/isa/intr_machdep.c,v 1.32 2005/09/10 06:48:08 dillon Exp $
 */
/*
 * This file contains an aggregated module marked:
 * Copyright (c) 1997, Stefan Esser <se@freebsd.org>
 * All rights reserved.
 * See the notice for details.
 */

#include "use_isa.h"
#include "opt_auto_eoi.h"

#include <sys/param.h>
#ifndef SMP
#include <machine/lock.h>
#endif
#include <sys/systm.h>
#include <sys/syslog.h>
#include <sys/malloc.h>
#include <sys/errno.h>
#include <sys/interrupt.h>
#include <machine/ipl.h>
#include <machine/md_var.h>
#include <machine/segments.h>
#include <sys/bus.h> 
#include <machine/globaldata.h>
#include <sys/proc.h>
#include <sys/thread2.h>

#include <machine/smptests.h>			/** FAST_HI */
#include <machine/smp.h>
#include <bus/isa/i386/isa.h>
#include <i386/isa/icu.h>

#if NISA > 0
#include <bus/isa/isavar.h>
#endif
#include <i386/isa/intr_machdep.h>
#include <bus/isa/isavar.h>
#include <sys/interrupt.h>
#ifdef APIC_IO
#include <machine/clock.h>
#endif
#include <machine/cpu.h>

/* XXX should be in suitable include files */
#define	ICU_IMR_OFFSET		1		/* IO_ICU{1,2} + 1 */
#define	ICU_SLAVEID			2

#ifdef APIC_IO
/*
 * This is to accommodate "mixed-mode" programming for 
 * motherboards that don't connect the 8254 to the IO APIC.
 */
#define	AUTO_EOI_1	1
#endif

#define	NR_INTRNAMES	(1 + ICU_LEN + 2 * ICU_LEN)

static inthand2_t isa_strayintr;
#if defined(FAST_HI) && defined(APIC_IO)
void do_wrongintr(int intr);
#endif
static void	init_i8259(void);

void	*intr_unit[ICU_LEN*2];
u_long	*intr_countp[ICU_LEN*2];
inthand2_t *intr_handler[ICU_LEN*2] = {
	isa_strayintr, isa_strayintr, isa_strayintr, isa_strayintr,
	isa_strayintr, isa_strayintr, isa_strayintr, isa_strayintr,
	isa_strayintr, isa_strayintr, isa_strayintr, isa_strayintr,
	isa_strayintr, isa_strayintr, isa_strayintr, isa_strayintr,
	isa_strayintr, isa_strayintr, isa_strayintr, isa_strayintr,
	isa_strayintr, isa_strayintr, isa_strayintr, isa_strayintr,
	isa_strayintr, isa_strayintr, isa_strayintr, isa_strayintr,
	isa_strayintr, isa_strayintr, isa_strayintr, isa_strayintr,
};

static struct md_intr_info {
    int		irq;
    int		mihandler_installed;
} intr_info[ICU_LEN*2];

static inthand_t *fastintr[ICU_LEN] = {
	&IDTVEC(fastintr0), &IDTVEC(fastintr1),
	&IDTVEC(fastintr2), &IDTVEC(fastintr3),
	&IDTVEC(fastintr4), &IDTVEC(fastintr5),
	&IDTVEC(fastintr6), &IDTVEC(fastintr7),
	&IDTVEC(fastintr8), &IDTVEC(fastintr9),
	&IDTVEC(fastintr10), &IDTVEC(fastintr11),
	&IDTVEC(fastintr12), &IDTVEC(fastintr13),
	&IDTVEC(fastintr14), &IDTVEC(fastintr15),
#if defined(APIC_IO)
	&IDTVEC(fastintr16), &IDTVEC(fastintr17),
	&IDTVEC(fastintr18), &IDTVEC(fastintr19),
	&IDTVEC(fastintr20), &IDTVEC(fastintr21),
	&IDTVEC(fastintr22), &IDTVEC(fastintr23),
#endif /* APIC_IO */
};

unpendhand_t *fastunpend[ICU_LEN] = {
	IDTVEC(fastunpend0), IDTVEC(fastunpend1),
	IDTVEC(fastunpend2), IDTVEC(fastunpend3),
	IDTVEC(fastunpend4), IDTVEC(fastunpend5),
	IDTVEC(fastunpend6), IDTVEC(fastunpend7),
	IDTVEC(fastunpend8), IDTVEC(fastunpend9),
	IDTVEC(fastunpend10), IDTVEC(fastunpend11),
	IDTVEC(fastunpend12), IDTVEC(fastunpend13),
	IDTVEC(fastunpend14), IDTVEC(fastunpend15),
#if defined(APIC_IO)
	IDTVEC(fastunpend16), IDTVEC(fastunpend17),
	IDTVEC(fastunpend18), IDTVEC(fastunpend19),
	IDTVEC(fastunpend20), IDTVEC(fastunpend21),
	IDTVEC(fastunpend22), IDTVEC(fastunpend23),
#endif
};

static inthand_t *slowintr[ICU_LEN] = {
	&IDTVEC(intr0), &IDTVEC(intr1), &IDTVEC(intr2), &IDTVEC(intr3),
	&IDTVEC(intr4), &IDTVEC(intr5), &IDTVEC(intr6), &IDTVEC(intr7),
	&IDTVEC(intr8), &IDTVEC(intr9), &IDTVEC(intr10), &IDTVEC(intr11),
	&IDTVEC(intr12), &IDTVEC(intr13), &IDTVEC(intr14), &IDTVEC(intr15),
#if defined(APIC_IO)
	&IDTVEC(intr16), &IDTVEC(intr17), &IDTVEC(intr18), &IDTVEC(intr19),
	&IDTVEC(intr20), &IDTVEC(intr21), &IDTVEC(intr22), &IDTVEC(intr23),
#endif /* APIC_IO */
};

#if defined(APIC_IO)

static inthand_t *wrongintr[ICU_LEN] = {
	&IDTVEC(wrongintr0), &IDTVEC(wrongintr1), &IDTVEC(wrongintr2),
	&IDTVEC(wrongintr3), &IDTVEC(wrongintr4), &IDTVEC(wrongintr5),
	&IDTVEC(wrongintr6), &IDTVEC(wrongintr7), &IDTVEC(wrongintr8),
	&IDTVEC(wrongintr9), &IDTVEC(wrongintr10), &IDTVEC(wrongintr11),
	&IDTVEC(wrongintr12), &IDTVEC(wrongintr13), &IDTVEC(wrongintr14),
	&IDTVEC(wrongintr15),
	&IDTVEC(wrongintr16), &IDTVEC(wrongintr17), &IDTVEC(wrongintr18),
	&IDTVEC(wrongintr19), &IDTVEC(wrongintr20), &IDTVEC(wrongintr21),
	&IDTVEC(wrongintr22), &IDTVEC(wrongintr23)
};

#endif /* APIC_IO */

#define NMI_PARITY (1 << 7)
#define NMI_IOCHAN (1 << 6)
#define ENMI_WATCHDOG (1 << 7)
#define ENMI_BUSTIMER (1 << 6)
#define ENMI_IOSTATUS (1 << 5)

/*
 * Handle a NMI, possibly a machine check.
 * return true to panic system, false to ignore.
 */
int
isa_nmi(cd)
	int cd;
{
	int retval = 0;
	int isa_port = inb(0x61);
	int eisa_port = inb(0x461);

	log(LOG_CRIT, "NMI ISA %x, EISA %x\n", isa_port, eisa_port);
	
	if (isa_port & NMI_PARITY) {
		log(LOG_CRIT, "RAM parity error, likely hardware failure.");
		retval = 1;
	}

	if (isa_port & NMI_IOCHAN) {
		log(LOG_CRIT, "I/O channel check, likely hardware failure.");
		retval = 1;
	}

	/*
	 * On a real EISA machine, this will never happen.  However it can
	 * happen on ISA machines which implement XT style floating point
	 * error handling (very rare).  Save them from a meaningless panic.
	 */
	if (eisa_port == 0xff)
		return(retval);

	if (eisa_port & ENMI_WATCHDOG) {
		log(LOG_CRIT, "EISA watchdog timer expired, likely hardware failure.");
		retval = 1;
	}

	if (eisa_port & ENMI_BUSTIMER) {
		log(LOG_CRIT, "EISA bus timeout, likely hardware failure.");
		retval = 1;
	}

	if (eisa_port & ENMI_IOSTATUS) {
		log(LOG_CRIT, "EISA I/O port status error.");
		retval = 1;
	}
	return(retval);
}

/*
 *  ICU reinitialize when ICU configuration has lost.
 */
void
icu_reinit()
{
       int i;

       init_i8259();
       for(i=0;i<ICU_LEN;i++)
               if(intr_handler[i] != isa_strayintr)
                       INTREN(1<<i);
}

/*
 * Fill in default interrupt table (in case of spurious interrupt
 * during configuration of kernel, setup interrupt control unit
 */
void
isa_defaultirq()
{
	int i;

	/* icu vectors */
	for (i = 0; i < ICU_LEN; i++)
		icu_unset(i, isa_strayintr);
	init_i8259();
}

static void
init_i8259(void)
{

	/* initialize 8259's */
	outb(IO_ICU1, 0x11);		/* reset; program device, four bytes */
	outb(IO_ICU1+ICU_IMR_OFFSET, NRSVIDT);	/* starting at this vector index */
	outb(IO_ICU1+ICU_IMR_OFFSET, IRQ_SLAVE);		/* slave on line 7 */
#ifdef AUTO_EOI_1
	outb(IO_ICU1+ICU_IMR_OFFSET, 2 | 1);		/* auto EOI, 8086 mode */
#else
	outb(IO_ICU1+ICU_IMR_OFFSET, 1);		/* 8086 mode */
#endif
	outb(IO_ICU1+ICU_IMR_OFFSET, 0xff);		/* leave interrupts masked */
	outb(IO_ICU1, 0x0a);		/* default to IRR on read */
	outb(IO_ICU1, 0xc0 | (3 - 1));	/* pri order 3-7, 0-2 (com2 first) */
	outb(IO_ICU2, 0x11);		/* reset; program device, four bytes */
	outb(IO_ICU2+ICU_IMR_OFFSET, NRSVIDT+8); /* staring at this vector index */
	outb(IO_ICU2+ICU_IMR_OFFSET, ICU_SLAVEID);         /* my slave id is 7 */
#ifdef AUTO_EOI_2
	outb(IO_ICU2+ICU_IMR_OFFSET, 2 | 1);		/* auto EOI, 8086 mode */
#else
	outb(IO_ICU2+ICU_IMR_OFFSET,1);		/* 8086 mode */
#endif
	outb(IO_ICU2+ICU_IMR_OFFSET, 0xff);          /* leave interrupts masked */
	outb(IO_ICU2, 0x0a);		/* default to IRR on read */
}

/*
 * Caught a stray interrupt, notify
 */
static void
isa_strayintr(void *vcookiep)
{
	int intr = (void **)vcookiep - &intr_unit[0];

	/* DON'T BOTHER FOR NOW! */
	/* for some reason, we get bursts of intr #7, even if not enabled! */
	/*
	 * Well the reason you got bursts of intr #7 is because someone
	 * raised an interrupt line and dropped it before the 8259 could
	 * prioritize it.  This is documented in the intel data book.  This
	 * means you have BAD hardware!  I have changed this so that only
	 * the first 5 get logged, then it quits logging them, and puts
	 * out a special message. rgrimes 3/25/1993
	 */
	/*
	 * XXX TODO print a different message for #7 if it is for a
	 * glitch.  Glitches can be distinguished from real #7's by
	 * testing that the in-service bit is _not_ set.  The test
	 * must be done before sending an EOI so it can't be done if
	 * we are using AUTO_EOI_1.
	 */
	if (intrcnt[1 + intr] <= 5)
		log(LOG_ERR, "stray irq %d\n", intr);
	if (intrcnt[1 + intr] == 5)
		log(LOG_CRIT,
		    "too many stray irq %d's; not logging any more\n", intr);
}

#if defined(FAST_HI) && defined(APIC_IO)

/*
 * This occurs if we've mis-programmed the APIC and its vector is still
 * pointing to the slow vector even when we thought we reprogrammed it
 * to the high vector.  This can occur when interrupts are improperly
 * routed by the APIC.  The unit data is opaque so we have to try to
 * find it in the unit array.
 */
void
do_wrongintr(int intr)
{
	if (intrcnt[1 + intr] <= 5) {
		log(LOG_ERR, "stray irq ~%d on cpu %d (APIC misprogrammed)\n",
		    intr, mycpu->gd_cpuid);
	} else if (intrcnt[1 + intr] == 6) {
		log(LOG_CRIT,
		    "too many stray irq ~%d's; not logging any more\n", intr);
	}
}

#endif

#if NISA > 0
/*
 * Return a bitmap of the current interrupt requests.  This is 8259-specific
 * and is only suitable for use at probe time.
 */
intrmask_t
isa_irq_pending(void)
{
	u_char irr1;
	u_char irr2;

	irr1 = inb(IO_ICU1);
	irr2 = inb(IO_ICU2);
	return ((irr2 << 8) | irr1);
}
#endif

static void
update_intrname(int intr, char *name)
{
	char buf[32];
	char *cp;
	int name_index, off, strayintr;

	/*
	 * Initialise strings for bitbucket and stray interrupt counters.
	 * These have statically allocated indices 0 and 1 through ICU_LEN.
	 */
	if (intrnames[0] == '\0') {
		off = sprintf(intrnames, "???") + 1;
		for (strayintr = 0; strayintr < ICU_LEN; strayintr++)
			off += sprintf(intrnames + off, "stray irq%d",
			    strayintr) + 1;
	}

	if (name == NULL)
		name = "???";
	if (snprintf(buf, sizeof(buf), "%s irq%d", name, intr) >= sizeof(buf))
		goto use_bitbucket;

	/*
	 * Search for `buf' in `intrnames'.  In the usual case when it is
	 * not found, append it to the end if there is enough space (the \0
	 * terminator for the previous string, if any, becomes a separator).
	 */
	for (cp = intrnames, name_index = 0;
	    cp != eintrnames && name_index < NR_INTRNAMES;
	    cp += strlen(cp) + 1, name_index++) {
		if (*cp == '\0') {
			if (strlen(buf) >= eintrnames - cp)
				break;
			strcpy(cp, buf);
			goto found;
		}
		if (strcmp(cp, buf) == 0)
			goto found;
	}

use_bitbucket:
	printf("update_intrname: counting %s irq%d as %s\n", name, intr,
	    intrnames);
	name_index = 0;
found:
	intr_countp[intr] = &intrcnt[name_index];
}

/*
 * NOTE!  intr_handler[] is only used for FAST interrupts, the *vector.s
 * code ignores it for normal interrupts.
 */
int
icu_setup(int intr, inthand2_t *handler, void *arg, int flags)
{
#if defined(FAST_HI) && defined(APIC_IO)
	int		select;		/* the select register is 8 bits */
	int		vector;
	u_int32_t	value;		/* the window register is 32 bits */
#endif /* FAST_HI */
	u_long	ef;

#if defined(APIC_IO)
	if ((u_int)intr >= ICU_LEN)	/* no 8259 SLAVE to ignore */
#else
	if ((u_int)intr >= ICU_LEN || intr == ICU_SLAVEID)
#endif /* APIC_IO */
		return (EINVAL);
	if (intr_handler[intr] != isa_strayintr)
		return (EBUSY);

	ef = read_eflags();
	cpu_disable_intr();	/* YYY */
	intr_handler[intr] = handler;
	intr_unit[intr] = arg;
#if 0
	/* YYY  fast ints supported and mp protected but ... */
	flags &= ~INTR_FAST;
#endif
#if defined(FAST_HI) && defined(APIC_IO)
	if (flags & INTR_FAST) {
		/*
		 * Install a spurious interrupt in the low space in case
		 * the IO apic is not properly reprogrammed.
		 */
		vector = TPR_SLOW_INTS + intr;
		setidt(vector, wrongintr[intr],
		       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));
		vector = TPR_FAST_INTS + intr;
		setidt(vector, fastintr[intr],
		       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));
	} else {
		vector = TPR_SLOW_INTS + intr;
#ifdef APIC_INTR_REORDER
#ifdef APIC_INTR_HIGHPRI_CLOCK
		/* XXX: Hack (kludge?) for more accurate clock. */
		if (intr == apic_8254_intr || intr == 8) {
			vector = TPR_FAST_INTS + intr;
		}
#endif
#endif
		setidt(vector, slowintr[intr],
		       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));
	}
#ifdef APIC_INTR_REORDER
	set_lapic_isrloc(intr, vector);
#endif
	/*
	 * Reprogram the vector in the IO APIC.
	 *
	 * XXX EOI/mask a pending (stray) interrupt on the old vector?
	 */
	if (int_to_apicintpin[intr].ioapic >= 0) {
		select = int_to_apicintpin[intr].redirindex;
		value = io_apic_read(int_to_apicintpin[intr].ioapic, 
				     select) & ~IOART_INTVEC;
		io_apic_write(int_to_apicintpin[intr].ioapic, 
			      select, value | vector);
	}
#else
	setidt(ICU_OFFSET + intr,
	       flags & INTR_FAST ? fastintr[intr] : slowintr[intr],
	       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));
#endif /* FAST_HI && APIC_IO */
	INTREN(1 << intr);
	write_eflags(ef);
	return (0);
}

int
icu_unset(intr, handler)
	int	intr;
	inthand2_t *handler;
{
	u_long	ef;

	if ((u_int)intr >= ICU_LEN || handler != intr_handler[intr]) {
		printf("icu_unset: invalid handler %d %p/%p\n", intr, handler, 
		    (((u_int)intr >= ICU_LEN) ? (void *)-1 : intr_handler[intr]));
		return (EINVAL);
	}

	INTRDIS(1 << intr);
	ef = read_eflags();
	cpu_disable_intr();	/* YYY */
	intr_countp[intr] = &intrcnt[1 + intr];
	intr_handler[intr] = isa_strayintr;
	intr_unit[intr] = &intr_unit[intr];
#ifdef FAST_HI_XXX
	/* XXX how do I re-create dvp here? */
	setidt(flags & INTR_FAST ? TPR_FAST_INTS + intr : TPR_SLOW_INTS + intr,
	    slowintr[intr], SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));
#else /* FAST_HI */
#ifdef APIC_INTR_REORDER
	set_lapic_isrloc(intr, ICU_OFFSET + intr);
#endif
	setidt(ICU_OFFSET + intr, slowintr[intr], SDT_SYS386IGT, SEL_KPL,
	    GSEL(GCODE_SEL, SEL_KPL));
#endif /* FAST_HI */
	write_eflags(ef);
	return (0);
}


/* The following notice applies beyond this point in the file */

/*
 * Copyright (c) 1997, Stefan Esser <se@freebsd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/i386/isa/intr_machdep.c,v 1.29.2.5 2001/10/14 06:54:27 luigi Exp $
 *
 */

typedef struct intrec {
	inthand2_t      *handler;
	void            *argument;
	struct intrec   *next;
	char            *name;
	int             intr;
	int             flags;
	lwkt_serialize_t serializer;
	volatile int	in_handler;
} intrec;

static intrec *intreclist_head[ICU_LEN];

/*
 * The interrupt multiplexer calls each of the handlers in turn.  A handler
 * is called only if we can successfully obtain the interlock, meaning
 * (1) we aren't recursed and (2) the handler has not been disabled via
 * inthand_disabled().
 *
 * XXX the IPL is currently raised as necessary for the handler.  However,
 * IPLs are not MP safe so the IPL code will be removed when the device
 * drivers, BIO, and VM no longer depend on it.
 */
static void
intr_mux(void *arg)
{
	intrec **pp;
	intrec *p;

	for (pp = arg; (p = *pp) != NULL; pp = &p->next) {
		if (p->serializer) {
			/*
			 * New handler dispatch method.  Only the serializer
			 * is used to interlock access.  Note that this
			 * API includes a handler disablement feature.
			 */
			lwkt_serialize_handler_call(p->serializer,
						    p->handler, p->argument);
		} else {
			/*
			 * Old handlers may expect multiple interrupt
			 * sources to be masked.  We must use a critical
			 * section.
			 */
			crit_enter();
			p->handler(p->argument);
			crit_exit();
		}
	}
}

/*
 * Add an interrupt handler to the linked list hung off of intreclist_head[irq]
 * and install a shared interrupt multiplex handler.  Install an interrupt
 * thread for each interrupt (though FAST interrupts will not use it).
 * The preemption procedure checks the CPL.  lwkt_preempt() will check
 * relative thread priorities for us as long as we properly pass through
 * critpri.
 *
 * The interrupt thread has already been put on the run queue, so if we cannot
 * preempt we should force a reschedule.
 *
 * This preemption check routine is currently empty, but will be used in the
 * future to pre-check interrupts for preemptability to avoid the
 * inefficiencies of having to instantly block.  We used to do a CPL check
 * here (otherwise the interrupt thread could preempt even when it wasn't
 * supposed to), but with CPLs gone we no longer have to do this.
 */
static void
cpu_intr_preempt(struct thread *td, int critpri)
{
	lwkt_preempt(td, critpri);
}

static int
add_intrdesc(intrec *idesc)
{
	int irq = idesc->intr;
	intrec *head;
	intrec **headp;

	/*
	 * There are two ways to enter intr_mux().  (1) via the scheduled
	 * interrupt thread or (2) directly.   The thread mechanism is the
	 * normal mechanism used by SLOW interrupts, while the direct method
	 * is used by FAST interrupts.
	 *
	 * We need to create an interrupt thread if none exists.
	 */
	if (intr_info[irq].mihandler_installed == 0) {
		struct thread *td;

		intr_info[irq].mihandler_installed = 1;
		intr_info[irq].irq = irq;
		td = register_int(irq, intr_mux, &intreclist_head[irq], idesc->name);
		td->td_info.intdata = &intr_info[irq];
		td->td_preemptable = cpu_intr_preempt;
		printf("installed MI handler for int %d\n", irq);
	}

	headp = &intreclist_head[irq];
	head = *headp;

	/*
	 * Check exclusion
	 */
	if (head) {
		if ((idesc->flags & INTR_EXCL) || (head->flags & INTR_EXCL)) {
			printf("\tdevice combination doesn't support "
			       "shared irq%d\n", irq);
			return (-1);
		}
		if ((idesc->flags & INTR_FAST) || (head->flags & INTR_FAST)) {
			printf("\tdevice combination doesn't support "
			       "multiple FAST interrupts on IRQ%d\n", irq);
		}
	}

	/*
	 * Always install intr_mux as the hard handler so it can deal with
	 * individual enablement on handlers.
	 */
	if (head == NULL) {
		if (icu_setup(irq, idesc->handler, idesc->argument, idesc->flags) != 0)
			return (-1);
		update_intrname(irq, idesc->name);
	} else if (head->next == NULL) {
		icu_unset(irq, head->handler);
		if (icu_setup(irq, intr_mux, &intreclist_head[irq], 0) != 0)
			return (-1);
		if (bootverbose && head->next == NULL)
			printf("\tusing shared irq%d.\n", irq);
		update_intrname(irq, "mux");
	}

	/*
	 * Append to the end of the chain.
	 */
	while (*headp != NULL)
		headp = &(*headp)->next;
	*headp = idesc;

	return (0);
}

/*
 * Create and activate an interrupt handler descriptor data structure.
 *
 * The dev_instance pointer is required for resource management, and will
 * only be passed through to resource_claim().
 *
 * There will be functions that derive a driver and unit name from a
 * dev_instance variable, and those functions will be used to maintain the
 * interrupt counter label array referenced by systat and vmstat to report
 * device interrupt rates (->update_intrlabels).
 *
 * Add the interrupt handler descriptor data structure created by an
 * earlier call of create_intr() to the linked list for its irq.
 *
 * WARNING: This is an internal function and not to be used by device
 * drivers.  It is subject to change without notice.
 */

intrec *
inthand_add(const char *name, int irq, inthand2_t handler, void *arg,
	     int flags, lwkt_serialize_t serializer)
{
	intrec *idesc;
	int errcode = -1;

	if ((unsigned)irq >= ICU_LEN) {
		printf("create_intr: requested irq%d too high, limit is %d\n",
		       irq, ICU_LEN -1);
		return (NULL);
	}

	idesc = malloc(sizeof *idesc, M_DEVBUF, M_WAITOK | M_ZERO);
	if (idesc == NULL)
		return NULL;

	if (name == NULL)
		name = "???";
	idesc->name = malloc(strlen(name) + 1, M_DEVBUF, M_WAITOK);
	if (idesc->name == NULL) {
		free(idesc, M_DEVBUF);
		return NULL;
	}
	strcpy(idesc->name, name);

	idesc->handler  = handler;
	idesc->argument = arg;
	idesc->intr     = irq;
	idesc->flags    = flags;
	idesc->serializer = serializer;

	crit_enter();
	errcode = add_intrdesc(idesc);
	crit_exit();

	if (errcode != 0) {
		if (bootverbose)
			printf("\tintr_connect(irq%d) failed, result=%d\n", 
			       irq, errcode);
		free(idesc->name, M_DEVBUF);
		free(idesc, M_DEVBUF);
		idesc = NULL;
	}

	return (idesc);
}

/*
 * Deactivate and remove the interrupt handler descriptor data connected
 * created by an earlier call of intr_connect() from the linked list.
 *
 * Return the memory held by the interrupt handler descriptor data structure
 * to the system. Make sure, the handler is not actively used anymore, before.
 */
int
inthand_remove(intrec *idesc)
{
	intrec **hook, *head;
	int irq;

	if (idesc == NULL)
		return (-1);

	irq = idesc->intr;
	crit_enter();

	/*
	 * Find and remove the interrupt descriptor.
	 */
	hook = &intreclist_head[irq];
	while (*hook != idesc) {
		if (*hook == NULL) {
			crit_exit();
			return(-1);
		}
		hook = &(*hook)->next;
	}
	*hook = idesc->next;

	/*
	 * If the list is now empty, revert the hard vector to the spurious
	 * interrupt.
	 */
	head = intreclist_head[irq];
	if (head == NULL) {
		/*
		 * No more interrupts on this irq
		 */
		icu_unset(irq, idesc->handler);
		update_intrname(irq, NULL);
	} else if (head->next) {
		/*
		 * This irq is still shared (has at least two handlers)
		 * (the name should already be set to "mux").
		 */
	} else {
		/*
		 * This irq is no longer shared
		 */
		icu_unset(irq, intr_mux);
		icu_setup(irq, head->handler, head->argument, head->flags);
		update_intrname(irq, head->name);
	}
	crit_exit();
	free(idesc, M_DEVBUF);

	return (0);
}

/*
 * ithread_done()
 *
 *	This function is called by an interrupt thread when it has completed
 *	processing a loop.  We re-enable interrupts and interlock with
 *	ipending.
 *
 *	See kern/kern_intr.c for more information.
 */
void
ithread_done(int irq)
{
    struct mdglobaldata *gd = mdcpu;
    int mask = 1 << irq;
    thread_t td;

    td = gd->mi.gd_curthread;

    KKASSERT(td->td_pri >= TDPRI_CRIT);
    lwkt_deschedule_self(td);
    INTREN(mask);
    if (gd->gd_ipending & mask) {
	atomic_clear_int_nonlocked(&gd->gd_ipending, mask);
	INTRDIS(mask);
	lwkt_schedule_self(td);
    } else {
	lwkt_switch();
    }
}

#ifdef SMP
/*
 * forward_fast_remote()
 *
 *	This function is called from the receiving end of an IPIQ when a
 *	remote cpu wishes to forward a fast interrupt to us.  All we have to
 *	do is set the interrupt pending and let the IPI's doreti deal with it.
 */
void
forward_fastint_remote(void *arg)
{
    int irq = (int)arg;
    struct mdglobaldata *gd = mdcpu;

    atomic_set_int_nonlocked(&gd->gd_fpending, 1 << irq);
    atomic_set_int_nonlocked(&gd->mi.gd_reqflags, RQF_INTPEND);
}

#endif
