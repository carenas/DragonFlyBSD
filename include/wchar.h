/*-
 * Copyright (c)1999 Citrus Project,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/include/wchar.h,v 1.3.2.2 2002/08/08 02:42:29 imp Exp $
 * $DragonFly: src/include/wchar.h,v 1.3 2003/11/09 02:22:28 dillon Exp $
 */

/*-
 * Copyright (c) 1999, 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Julian Coleman.
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
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *	$NetBSD: wchar.h,v 1.8 2000/12/22 05:31:42 itojun Exp $
 */

#ifndef _WCHAR_H_
#define _WCHAR_H_

#include <sys/cdefs.h>
#ifndef _SYS_STDINT_H_
#include <sys/stdint.h>	/* __wchar_t and friends */
#endif

#ifndef NULL
#define NULL	0
#endif

#ifndef __cplusplus
#ifndef _WCHAR_T_DECLARED_
#define _WCHAR_T_DECLARED_
typedef __wchar_t	wchar_t;
#endif
#endif

#ifndef _MBSTATE_T_DECLARED_
#define _MBSTATE_T_DECLARED_
typedef	__mbstate_t	mbstate_t;
#endif

#ifndef _WINT_T_DECLARED_
#define _WINT_T_DECLARED_
typedef	__wint_t	wint_t;
#endif

#ifndef _SIZE_T_DECLARED_
#define _SIZE_T_DECLARED_
typedef __size_t        size_t;		/* open group */
#endif

#ifndef WEOF
#define	WEOF 	((wint_t)-1)
#endif

__BEGIN_DECLS

wchar_t	*wcscat __P((wchar_t * __restrict, const wchar_t * __restrict));
wchar_t	*wcschr __P((const wchar_t *, wchar_t));
int	wcscmp __P((const wchar_t *, const wchar_t *));
wchar_t	*wcscpy __P((wchar_t * __restrict, const wchar_t * __restrict));
size_t	wcscspn __P((const wchar_t *, const wchar_t *));
size_t	wcslen __P((const wchar_t *));
wchar_t	*wcsncat __P((wchar_t * __restrict, const wchar_t * __restrict,
	    size_t));
int	wcsncmp __P((const wchar_t *, const wchar_t *, size_t));
wchar_t	*wcsncpy __P((wchar_t * __restrict , const wchar_t * __restrict,
	    size_t));
wchar_t	*wcspbrk __P((const wchar_t *, const wchar_t *));
wchar_t	*wcsrchr __P((const wchar_t *, wchar_t));
#if 0
/* XXX: not implemented */
size_t	wcsrtombs __P((char * __restrict, const wchar_t ** __restrict, size_t,
	    mbstate_t * __restrict));
#endif
size_t	wcsspn __P((const wchar_t *, const wchar_t *));
wchar_t	*wcsstr __P((const wchar_t *, const wchar_t *));
wchar_t	*wmemchr __P((const wchar_t *, wchar_t, size_t));
int	wmemcmp __P((const wchar_t *, const wchar_t *, size_t));
wchar_t	*wmemcpy __P((wchar_t * __restrict, const wchar_t * __restrict,
	    size_t));
wchar_t	*wmemmove __P((wchar_t *, const wchar_t *, size_t));
wchar_t	*wmemset __P((wchar_t *, wchar_t, size_t));

size_t	wcslcat __P((wchar_t *, const wchar_t *, size_t));
size_t	wcslcpy __P((wchar_t *, const wchar_t *, size_t));
#if 0
/* XXX: not implemented */
int	wcswidth __P((const wchar_t *, size_t));
int	wcwidth __P((wchar_t));
#endif
__END_DECLS

#endif /* !_WCHAR_H_ */
