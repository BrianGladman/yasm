/* $IdPath$
 * Includes standard headers and defines prototypes for replacement functions
 * if needed.  This is the *only* header file which should include other
 * header files!
 *
 *  Copyright (C) 2001  Peter Johnson
 *
 *  This file is part of YASM.
 *
 *  YASM is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  YASM is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef YASM_UTIL_H
#define YASM_UTIL_H

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>

#ifdef STDC_HEADERS
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
#endif

#if defined(lint)
/*@dependent@*/ const char *gettext(const char *s);
#define _(String)	gettext(String)
#else
# ifdef HAVE_LOCALE_H
#  include <locale.h>
# endif

# ifdef ENABLE_NLS
#  include <libintl.h>
#  define _(String)	gettext(String)
# else
#  define gettext(Msgid)    (Msgid)
#  define dgettext(Domainname, Msgid)	(Msgid)
#  define dcgettext(Domainname, Msgid, Category)    (Msgid)
#  define textdomain(Domainname)		while (0) /* nothing */
#  define bindtextdomain(Domainname, Dirname)	while (0) /* nothing */
#  define _(String)	(String)
# endif
#endif

#ifdef gettext_noop
# define N_(String)	gettext_noop(String)
#else
# define N_(String)	(String)
#endif

#if !defined(HAVE_MERGESORT) || defined(lint)
int mergesort(void *base, size_t nmemb, size_t size,
	      int (*compar)(const void *, const void *));
#endif

#if !defined(HAVE_STRSEP) || defined(HAVE_GNU_C_LIBRARY) || defined(lint)
/*@null@*/ char *strsep(char **stringp, const char *delim);
#endif

#ifndef HAVE_STRCASECMP
# ifdef HAVE_STRICMP
#  define strcasecmp(x, y)	stricmp(x, y)
#  define strncasecmp(x, y)	strnicmp(x, y)
# elif HAVE_STRCMPI
#  define strcasecmp(x, y)	strcmpi(x, y)
#  define strncasecmp(x, y)	strncmpi(x, y)
# else
#  define USE_OUR_OWN_STRCASECMP
# endif
#endif

#if defined(USE_OUR_OWN_STRCASECMP) || defined(HAVE_GNU_C_LIBRARY) || defined(lint)
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
#endif

#if !defined(HAVE_TOASCII) || defined(HAVE_GNU_C_LIBRARY) || defined(lint)
# define toascii(c) ((c) & 0x7F)
#endif

#if defined(HAVE_SYS_QUEUE_H) && !defined(HAVE_BOGUS_SYS_QUEUE_H)
# include <sys/queue.h>
#else
# include "compat-queue.h"
#endif

#ifdef HAVE_SYS_CDEFS_H
# include <sys/cdefs.h>
#endif

#ifdef __RCSID
# define RCSID(s)	__RCSID(s)
#else
# ifdef __GNUC__
#  ifdef __ELF__
#   define RCSID(s)	__asm__(".ident\t\"" s "\"")
#  else
#   define RCSID(s)	static const char rcsid[] = s
#  endif
# else
#  define RCSID(s)	static const char rcsid[] = s
# endif
#endif

#ifdef DMALLOC
# include <dmalloc.h>
#else
/* strdup() implementation with error checking (using xmalloc). */
/*@only@*/ char *xstrdup(const char *str);

/* Error-checking memory allocation routines in xmalloc.c. */
/*@only@*/ /*@out@*/ void *xmalloc(size_t size);
/*@only@*/ /*@out@*/ void *xcalloc(size_t nelem, size_t elsize);
/*@out@*/ void *xrealloc(/*@returned@*/ /*@null@*/ void *oldmem, size_t size);
void xfree(/*@only@*/ /*@out@*/ /*@null@*/ void *p);
#endif

#include "coretype.h"

#include "valparam.h"

#endif
