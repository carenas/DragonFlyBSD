/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	@(#)stdarg.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/i386/include/stdarg.h,v 1.10 1999/08/28 00:44:26 peter Exp $
 * $DragonFly: src/sys/i386/include/Attic/stdarg.h,v 1.4 2003/11/09 02:22:35 dillon Exp $
 */

#ifndef _MACHINE_STDARG_H_
#define	_MACHINE_STDARG_H_

/*
 * GNUC mess
 */
#if defined(__GNUC__) && (__GNUC__ == 2 && __GNUC_MINOR__ > 95 || __GNUC__ >= 3)
typedef __builtin_va_list	__va_list;	/* internally known to gcc */
#else
typedef	char *			__va_list;
#endif /* post GCC 2.95 */
#if defined __GNUC__ && !defined(__GNUC_VA_LIST) && !defined(__NO_GNUC_VA_LIST)
#define __GNUC_VA_LIST
typedef __va_list		__gnuc_va_list;	/* compatibility w/GNU headers*/
#endif

/*
 * Standard va types and macros
 */
#define	__va_size(type) \
	(((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#ifdef __GNUC__
#define __va_start(ap, last) \
	((ap) = (__va_list)__builtin_next_arg(last))
#else
#define	__va_start(ap, last) \
	((ap) = (__va_list)&(last) + __va_size(last))
#endif

#define	__va_arg(ap, type) \
	(*(type *)((ap) += __va_size(type), (ap) - __va_size(type)))

#define	__va_end(ap)

#endif

