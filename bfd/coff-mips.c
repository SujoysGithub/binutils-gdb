/* MIPS Extended-Coff handler for Binary File Diddling.
   Written by Per Bothner.  */

/* Copyright (C) 1990, 1991 Free Software Foundation, Inc.

This file is part of BFD, the Binary File Diddler.

BFD is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 1, or (at your option)
any later version.

BFD is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with BFD; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* This does not compile on anything but a MIPS yet (and I haven't been
   able to test it there either since the latest merge!).  So it stays
   out by default.  */

#define MIPS 1
#include <stdio.h>
#include <string.h>

#include "bfd.h"
#include "libbfd.h"
#include "sysdep.h"

#include "intel-coff.h"
#include "libcoff.h"		/* to allow easier abstraction-breaking */

#define BADMAG(x) ECOFFBADMAG(x)

#include "coff-code.h"
bfd_target ecoff_little_vec =
    {"ecoff-littlemips",      /* name */
	bfd_target_coff_flavour_enum,
	false,			/* data byte order is little */
	false,			/* header byte order is little */

	(HAS_RELOC | EXEC_P |	/* object flags */
	 HAS_LINENO | HAS_DEBUG |
	 HAS_SYMS | HAS_LOCALS | DYNAMIC | WP_TEXT),

	(SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD | SEC_RELOC), /* sect flags */
	'/',			/* ar_pad_char */
	15,			/* ar_max_namelen */
	_do_getllong, _do_putllong, _do_getlshort, _do_putlshort, /* data */
	_do_getllong, _do_putllong, _do_getlshort, _do_putlshort, /* hdrs */

	{_bfd_dummy_target, coff_object_p, /* bfd_check_format */
	  bfd_generic_archive_p, _bfd_dummy_target},
	{bfd_false, coff_mkobject, bfd_false, /* bfd_set_format */
	  bfd_false},
	{bfd_false, coff_write_object_contents, bfd_false, bfd_false},
	JUMP_TABLE (coff)
};

bfd_target ecoff_big_vec =
    {"ecoff-bigmips",      /* name */
	bfd_target_coff_flavour_enum,
	true,			/* data byte order is big */
	true,			/* header byte order is big */

	(HAS_RELOC | EXEC_P |	/* object flags */
	 HAS_LINENO | HAS_DEBUG |
	 HAS_SYMS | HAS_LOCALS | DYNAMIC | WP_TEXT),

	(SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD | SEC_RELOC), /* sect flags */
	' ',			/* ar_pad_char */
	16,			/* ar_max_namelen */
	_do_getblong, _do_putblong, _do_getbshort, _do_putbshort, /* data */
	_do_getblong, _do_putblong, _do_getbshort, _do_putbshort, /* hdrs */

	{_bfd_dummy_target, coff_object_p, /* bfd_check_format */
	  bfd_generic_archive_p, _bfd_dummy_target},
	{bfd_false, coff_mkobject, bfd_false, /* bfd_set_format */
	  bfd_false},
	{bfd_false, coff_write_object_contents, /* bfd_write_contents */
	  bfd_false, bfd_false},
	JUMP_TABLE(coff)
};
