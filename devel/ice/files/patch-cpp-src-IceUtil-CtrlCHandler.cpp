--- cpp.orig/src/IceUtil/CtrlCHandler.cpp	2011-06-15 21:43:59.000000000 +0200
+++ cpp/src/IceUtil/CtrlCHandler.cpp	2012-03-04 20:14:53.000000000 +0100
@@ -219,29 +219,41 @@
         sigaddset(&ctrlCLikeSignals, SIGHUP);
         sigaddset(&ctrlCLikeSignals, SIGINT);
         sigaddset(&ctrlCLikeSignals, SIGTERM);
-        int rc = pthread_sigmask(SIG_BLOCK, &ctrlCLikeSignals, 0);
+#ifndef NDEBUG
+        int rc = 
+#endif        
+        pthread_sigmask(SIG_BLOCK, &ctrlCLikeSignals, 0);
         assert(rc == 0);
 
         // Joinable thread
-        rc = pthread_create(&_tid, 0, sigwaitThread, 0);
+#ifndef NDEBUG
+        rc = 
+#endif
+        pthread_create(&_tid, 0, sigwaitThread, 0);
         assert(rc == 0);
     }
 }
 
 CtrlCHandler::~CtrlCHandler()
 {
-    int rc = pthread_cancel(_tid);
+#ifndef NDEBUG
+    int rc = 
+#endif
+    pthread_cancel(_tid);
     assert(rc == 0);
 #if defined(__APPLE__)
     //
     // WORKAROUND: sigwait isn't a cancellation point on MacOS X, see
     // comment in sigwaitThread
     //
-    rc = pthread_kill(_tid, SIGTERM);
+    pthread_kill(_tid, SIGTERM);
     //assert(rc == 0); For some reaosns, this assert is sometime triggered
 #endif
     void* status = 0;
-    rc = pthread_join(_tid, &status);
+#ifndef NDEBUG
+    rc = 
+#endif
+    pthread_join(_tid, &status);
     assert(rc == 0);
 #if !defined(__APPLE__)
     assert(status == PTHREAD_CANCELED);
