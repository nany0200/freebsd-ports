--- base/src/propimpl.cpp.orig	Thu Feb  6 02:52:47 2003
+++ base/src/propimpl.cpp	Mon Aug 18 17:35:16 2003
@@ -21,7 +21,10 @@
 	$Id$
 ____________________________________________________________________________*/
 
+#include <inttypes.h>
+#if HAVE_STDINT_H
 #include <stdint.h>
+#endif
 #include <map>
 #include <vector>
 #include <string>
