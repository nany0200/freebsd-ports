
$FreeBSD$

--- /dev/null
+++ gdb/ppcfbsd-tdep.h
@@ -0,0 +1,30 @@
+/* Common target dependent code for GDB on PowerPC systems running FreeBSD.
+   Copyright 2002 Free Software Foundation, Inc.
+
+   This file is part of GDB.
+
+   This program is free software; you can redistribute it and/or modify
+   it under the terms of the GNU General Public License as published by
+   the Free Software Foundation; either version 2 of the License, or
+   (at your option) any later version.
+
+   This program is distributed in the hope that it will be useful,
+   but WITHOUT ANY WARRANTY; without even the implied warranty of
+   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+   GNU General Public License for more details.
+
+   You should have received a copy of the GNU General Public License
+   along with this program; if not, write to the Free Software
+   Foundation, Inc., 59 Temple Place - Suite 330,
+   Boston, MA 02111-1307, USA.  */
+
+#ifndef PPCFBSD_TDEP_H
+#define PPCFBSD_TDEP_H
+
+void ppcfbsd_supply_reg (char *, int);
+void ppcfbsd_fill_reg (char *, int);
+
+void ppcfbsd_supply_fpreg (char *, int);
+void ppcfbsd_fill_fpreg (char *, int);
+
+#endif /* PPCFBSD_TDEP_H */
