
$FreeBSD$

--- src/glyph.h	2002/08/26 17:43:17	1.1
+++ src/glyph.h	2002/08/26 17:44:14
@@ -20,7 +20,7 @@
 #define __GFE_GLYPH_H__
 
 #include <gtk/gtk.h>
-#include <values.h>
+#include <limits.h>
 
 /* macro for type casting */
 #define GFE_GLYPH(glyph) ((GfeGlyph*)(glyph))
@@ -29,7 +29,7 @@
 #define GFE_GLYPH_NO_ENCODING (-1)
 
 /* constant used to define undefined status of variables */
-#define GFE_UNDEFINED         (MAXINT)
+#define GFE_UNDEFINED         (INT_MAX)
 
 /* macro(s) to access member(s) of GfeGlyph structure */
 #define GFE_GLYPH_TYPE(glyph)     (((glyph)->flags) & 0xFF)
