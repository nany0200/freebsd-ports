--- cpp.orig/src/IceUtil/Cond.cpp	2011-06-15 21:43:59.000000000 +0200
+++ cpp/src/IceUtil/Cond.cpp	2012-03-04 20:14:53.000000000 +0100
@@ -330,8 +330,11 @@
 
 IceUtil::Cond::~Cond()
 {
+#ifndef NDEBUG
     int rc = 0;
-    rc = pthread_cond_destroy(&_cond);
+    rc = 
+#endif
+    pthread_cond_destroy(&_cond);
     assert(rc == 0);
 }
 
