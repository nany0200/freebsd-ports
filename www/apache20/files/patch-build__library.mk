--- ./build/library.mk.orig	2006-07-12 03:40:55.000000000 -0400
+++ ./build/library.mk	2010-05-06 16:06:03.733831899 -0400
@@ -19,4 +19,4 @@
 LTLIBRARY_OBJECTS = $(LTLIBRARY_SOURCES:.c=.lo) $(LTLIBRARY_OBJECTS_X)
 
 $(LTLIBRARY_NAME): $(LTLIBRARY_OBJECTS) $(LTLIBRARY_DEPENDENCIES)
-	$(LINK) $(LTLIBRARY_LDFLAGS) $(LTLIBRARY_OBJECTS) $(LTLIBRARY_LIBADD)
+	$(LINK) -static $(LTLIBRARY_LDFLAGS) $(LTLIBRARY_OBJECTS) $(LTLIBRARY_LIBADD)
