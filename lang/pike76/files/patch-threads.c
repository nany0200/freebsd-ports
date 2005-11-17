--- src/threads.c.old	Wed Nov 16 10:58:57 2005
+++ src/threads.c	Wed Nov 16 10:59:00 2005
@@ -2,12 +2,12 @@
 || This file is part of Pike. For copyright information see COPYRIGHT.
 || Pike is distributed under GPL, LGPL and MPL. See the file COPYING
 || for more information.
-|| $Id$
+|| $Id$
 */
 
 #ifndef CONFIGURE_TEST
 #include "global.h"
-RCSID("$Id$");
+RCSID("$Id$");
 
 PMOD_EXPORT int num_threads = 1;
 PMOD_EXPORT int threads_disabled = 0;
@@ -1460,9 +1460,10 @@
     THIS_KEY->mutex_obj = NULL;
     if (mut->num_waiting)
       co_signal(&mut->condition);
-    else if (!mutex_obj->prog)
+    else if (mutex_obj && !mutex_obj->prog)
       co_destroy (&mut->condition);
-    free_object(mutex_obj);
+    if (mutex_obj)
+      free_object(mutex_obj);
   }
 }
 
