--- cpp.orig/test/Ice/custom/AllTests.cpp	2011-06-15 21:43:59.000000000 +0200
+++ cpp/test/Ice/custom/AllTests.cpp	2012-03-04 20:14:53.000000000 +0100
@@ -1384,7 +1384,8 @@
                        const ::Test::ClassStructSeq& seq,
                        const InParamPtr& cookie)
     {
-        pair< ::Test::ClassStructPtr, ::Test::ClassStructSeq> in = getIn(in, cookie);
+        pair< ::Test::ClassStructPtr, ::Test::ClassStructSeq> in;
+        in = getIn(in, cookie);
         test(ret == in.first);
         test(cs1 == in.first);
         test(seq == in.second);
@@ -1432,7 +1433,8 @@
 
     void throwExcept1(const Ice::AsyncResultPtr& result)
     {
-        wstring in = getIn(in, InParamPtr::dynamicCast(result->getCookie()));
+        wstring in;
+        in = getIn(in, InParamPtr::dynamicCast(result->getCookie()));
         try
         {
             Test1::WstringClassPrx t = Test1::WstringClassPrx::uncheckedCast(result->getProxy());
@@ -1451,7 +1453,8 @@
 
     void throwExcept2(const Ice::AsyncResultPtr& result)
     {
-        wstring in = getIn(in, InParamPtr::dynamicCast(result->getCookie()));
+        wstring in;
+        in = getIn(in, InParamPtr::dynamicCast(result->getCookie()));
         try
         {
             Test2::WstringClassPrx t = Test2::WstringClassPrx::uncheckedCast(result->getProxy());
