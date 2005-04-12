
$FreeBSD$

--- cfs_des.c.orig
+++ cfs_des.c
@@ -22,13 +22,15 @@
  *	block_cipher(key, block, decrypting)
  */
 
+#include <inttypes.h>
+
 #ifdef SOLARIS2X
 #define bcopy(s, d, l)		memcpy(d, s, l)
 #define bcmp(s, d, l)		(memcmp(s, d, l)? 1 : 0)
 #endif
 
-static long	ip_low();
-static long	ip_high();
+static int32_t	ip_low();
+static int32_t	ip_high();
 static void	fp();
 void	des_key_setup();
 
@@ -36,7 +38,7 @@
  *	Tables for Combined S and P Boxes
  */
 
-static long  s0p[] = {
+static int32_t  s0p[] = {
 0x00410100,0x00010000,0x40400000,0x40410100,0x00400000,0x40010100,0x40010000,0x40400000,
 0x40010100,0x00410100,0x00410000,0x40000100,0x40400100,0x00400000,0x00000000,0x40010000,
 0x00010000,0x40000000,0x00400100,0x00010100,0x40410100,0x00410000,0x40000100,0x00400100,
@@ -47,7 +49,7 @@
 0x00010000,0x00400000,0x40400100,0x00410100,0x40000000,0x40410000,0x00000100,0x40010100,
 };
 
-static long  s1p[] = {
+static int32_t  s1p[] = {
 0x08021002,0x00000000,0x00021000,0x08020000,0x08000002,0x00001002,0x08001000,0x00021000,
 0x00001000,0x08020002,0x00000002,0x08001000,0x00020002,0x08021000,0x08020000,0x00000002,
 0x00020000,0x08001002,0x08020002,0x00001000,0x00021002,0x08000000,0x00000000,0x00020002,
@@ -58,7 +60,7 @@
 0x08020002,0x00020000,0x00001002,0x08001000,0x08001002,0x00000002,0x08020000,0x00021000,
 };
 
-static long  s2p[] = {
+static int32_t  s2p[] = {
 0x20800000,0x00808020,0x00000020,0x20800020,0x20008000,0x00800000,0x20800020,0x00008020,
 0x00800020,0x00008000,0x00808000,0x20000000,0x20808020,0x20000020,0x20000000,0x20808000,
 0x00000000,0x20008000,0x00808020,0x00000020,0x20000020,0x20808020,0x00008000,0x20800000,
@@ -69,7 +71,7 @@
 0x00800020,0x00000000,0x20808000,0x20000020,0x20800000,0x20008020,0x00000020,0x00808000,
 };
 
-static long  s3p[] = {
+static int32_t  s3p[] = {
 0x00080201,0x02000200,0x00000001,0x02080201,0x00000000,0x02080000,0x02000201,0x00080001,
 0x02080200,0x02000001,0x02000000,0x00000201,0x02000001,0x00080201,0x00080000,0x02000000,
 0x02080001,0x00080200,0x00000200,0x00000001,0x00080200,0x02000201,0x02080000,0x00000200,
@@ -80,7 +82,7 @@
 0x00080001,0x00080200,0x02080000,0x02000201,0x00000201,0x02000000,0x02000001,0x02080200,
 };
 
-static long  s4p[] = {
+static int32_t  s4p[] = {
 0x01000000,0x00002000,0x00000080,0x01002084,0x01002004,0x01000080,0x00002084,0x01002000,
 0x00002000,0x00000004,0x01000004,0x00002080,0x01000084,0x01002004,0x01002080,0x00000000,
 0x00002080,0x01000000,0x00002004,0x00000084,0x01000080,0x00002084,0x00000000,0x01000004,
@@ -91,7 +93,7 @@
 0x00002080,0x01002004,0x01000080,0x00000084,0x00000004,0x00002084,0x01002000,0x01000004,
 };
 
-static long  s5p[] = {
+static int32_t  s5p[] = {
 0x10000008,0x00040008,0x00000000,0x10040400,0x00040008,0x00000400,0x10000408,0x00040000,
 0x00000408,0x10040408,0x00040400,0x10000000,0x10000400,0x10000008,0x10040000,0x00040408,
 0x00040000,0x10000408,0x10040008,0x00000000,0x00000400,0x00000008,0x10040400,0x10040008,
@@ -102,7 +104,7 @@
 0x00000400,0x10000008,0x10000408,0x10040400,0x10040000,0x00000408,0x00000008,0x10040008,
 };
 
-static long  s6p[] = {
+static int32_t  s6p[] = {
 0x00000800,0x00000040,0x00200040,0x80200000,0x80200840,0x80000800,0x00000840,0x00000000,
 0x00200000,0x80200040,0x80000040,0x00200800,0x80000000,0x00200840,0x00200800,0x80000040,
 0x80200040,0x00000800,0x80000800,0x80200840,0x00000000,0x00200040,0x80200000,0x00000840,
@@ -113,7 +115,7 @@
 0x00200840,0x80000000,0x80000800,0x80200840,0x80200000,0x00200840,0x00200800,0x80000800,
 };
 
-static long  s7p[] = {
+static int32_t  s7p[] = {
 0x04100010,0x04104000,0x00004010,0x00000000,0x04004000,0x00100010,0x04100000,0x04104010,
 0x00000010,0x04000000,0x00104000,0x00004010,0x00104010,0x04004010,0x04000010,0x04100000,
 0x00004000,0x00104010,0x00100010,0x04004000,0x04104010,0x04000010,0x00000000,0x00104000,
@@ -134,8 +136,8 @@
 int decrypting;
 {
 	register char *key;
-	register long temp;
-	register long left, right;
+	register int32_t temp;
+	register int32_t left, right;
 	register i;
 	register key_offset;
 	int j,k;
@@ -199,8 +201,8 @@
 int decrypting;
 {
 	register char *key;
-	register long temp;
-	register long left, right;
+	register int32_t temp;
+	register int32_t left, right;
 	register i;
 	register key_offset;
 
@@ -240,78 +242,78 @@
 /*
  *	Final Permutation
  */
-static long	fph0[16] = {
+static int32_t	fph0[16] = {
 0x00000000,0x40000000,0x00400000,0x40400000,0x00004000,0x40004000,0x00404000,0x40404000,
 0x00000040,0x40000040,0x00400040,0x40400040,0x00004040,0x40004040,0x00404040,0x40404040,
 };
-static long	fpl1[16] = {
+static int32_t	fpl1[16] = {
 0x00000000,0x40000000,0x00400000,0x40400000,0x00004000,0x40004000,0x00404000,0x40404000,
 0x00000040,0x40000040,0x00400040,0x40400040,0x00004040,0x40004040,0x00404040,0x40404040,
 };
-static long	fph2[16] = {
+static int32_t	fph2[16] = {
 0x00000000,0x10000000,0x00100000,0x10100000,0x00001000,0x10001000,0x00101000,0x10101000,
 0x00000010,0x10000010,0x00100010,0x10100010,0x00001010,0x10001010,0x00101010,0x10101010,
 };
-static long	fpl3[16] = {
+static int32_t	fpl3[16] = {
 0x00000000,0x10000000,0x00100000,0x10100000,0x00001000,0x10001000,0x00101000,0x10101000,
 0x00000010,0x10000010,0x00100010,0x10100010,0x00001010,0x10001010,0x00101010,0x10101010,
 };
-static long	fph4[16] = {
+static int32_t	fph4[16] = {
 0x00000000,0x04000000,0x00040000,0x04040000,0x00000400,0x04000400,0x00040400,0x04040400,
 0x00000004,0x04000004,0x00040004,0x04040004,0x00000404,0x04000404,0x00040404,0x04040404,
 };
-static long	fpl5[16] = {
+static int32_t	fpl5[16] = {
 0x00000000,0x04000000,0x00040000,0x04040000,0x00000400,0x04000400,0x00040400,0x04040400,
 0x00000004,0x04000004,0x00040004,0x04040004,0x00000404,0x04000404,0x00040404,0x04040404,
 };
-static long	fph6[16] = {
+static int32_t	fph6[16] = {
 0x00000000,0x01000000,0x00010000,0x01010000,0x00000100,0x01000100,0x00010100,0x01010100,
 0x00000001,0x01000001,0x00010001,0x01010001,0x00000101,0x01000101,0x00010101,0x01010101,
 };
-static long	fpl7[16] = {
+static int32_t	fpl7[16] = {
 0x00000000,0x01000000,0x00010000,0x01010000,0x00000100,0x01000100,0x00010100,0x01010100,
 0x00000001,0x01000001,0x00010001,0x01010001,0x00000101,0x01000101,0x00010101,0x01010101,
 };
-static long	fph8[16] = {
+static int32_t	fph8[16] = {
 0x00000000,0x80000000,0x00800000,0x80800000,0x00008000,0x80008000,0x00808000,0x80808000,
 0x00000080,0x80000080,0x00800080,0x80800080,0x00008080,0x80008080,0x00808080,0x80808080,
 };
-static long	fpl9[16] = {
+static int32_t	fpl9[16] = {
 0x00000000,0x80000000,0x00800000,0x80800000,0x00008000,0x80008000,0x00808000,0x80808000,
 0x00000080,0x80000080,0x00800080,0x80800080,0x00008080,0x80008080,0x00808080,0x80808080,
 };
-static long	fpha[16] = {
+static int32_t	fpha[16] = {
 0x00000000,0x20000000,0x00200000,0x20200000,0x00002000,0x20002000,0x00202000,0x20202000,
 0x00000020,0x20000020,0x00200020,0x20200020,0x00002020,0x20002020,0x00202020,0x20202020,
 };
-static long	fplb[16] = {
+static int32_t	fplb[16] = {
 0x00000000,0x20000000,0x00200000,0x20200000,0x00002000,0x20002000,0x00202000,0x20202000,
 0x00000020,0x20000020,0x00200020,0x20200020,0x00002020,0x20002020,0x00202020,0x20202020,
 };
-static long	fphc[16] = {
+static int32_t	fphc[16] = {
 0x00000000,0x08000000,0x00080000,0x08080000,0x00000800,0x08000800,0x00080800,0x08080800,
 0x00000008,0x08000008,0x00080008,0x08080008,0x00000808,0x08000808,0x00080808,0x08080808,
 };
-static long	fpld[16] = {
+static int32_t	fpld[16] = {
 0x00000000,0x08000000,0x00080000,0x08080000,0x00000800,0x08000800,0x00080800,0x08080800,
 0x00000008,0x08000008,0x00080008,0x08080008,0x00000808,0x08000808,0x00080808,0x08080808,
 };
-static long	fphe[16] = {
+static int32_t	fphe[16] = {
 0x00000000,0x02000000,0x00020000,0x02020000,0x00000200,0x02000200,0x00020200,0x02020200,
 0x00000002,0x02000002,0x00020002,0x02020002,0x00000202,0x02000202,0x00020202,0x02020202,
 };
-static long	fplf[16] = {
+static int32_t	fplf[16] = {
 0x00000000,0x02000000,0x00020000,0x02020000,0x00000200,0x02000200,0x00020200,0x02020200,
 0x00000002,0x02000002,0x00020002,0x02020002,0x00000202,0x02000202,0x00020202,0x02020202,
 };
 
 static void
 fp(left, right, text)
-long left, right;
+int32_t left, right;
 char text[8];
 {
-	register unsigned long low, high;
-	register unsigned long temp;
+	register uint32_t low, high;
+	register uint32_t temp;
 
 	temp = left;
 	high = fph0[temp & 0xf];
@@ -358,140 +360,140 @@
 /*
  *	Initial Permutation
  */
-static long	ipl0[16] = {
+static int32_t	ipl0[16] = {
 0x00000000,
 0x00008000,0x00000000,0x00008000,0x00000080,0x00008080,0x00000080,0x00008080,0x00000000,
 0x00008000,0x00000000,0x00008000,0x00000080,0x00008080,0x00000080,0x00008080,};
-static long	iph0[16] = {
+static int32_t	iph0[16] = {
 0x00000000,
 0x00000000,0x00008000,0x00008000,0x00000000,0x00000000,0x00008000,0x00008000,0x00000080,
 0x00000080,0x00008080,0x00008080,0x00000080,0x00000080,0x00008080,0x00008080,};
-static long	ipl1[16] = {
+static int32_t	ipl1[16] = {
 0x00000000,
 0x80000000,0x00000000,0x80000000,0x00800000,0x80800000,0x00800000,0x80800000,0x00000000,
 0x80000000,0x00000000,0x80000000,0x00800000,0x80800000,0x00800000,0x80800000,};
-static long	iph1[16] = {
+static int32_t	iph1[16] = {
 0x00000000,
 0x00000000,0x80000000,0x80000000,0x00000000,0x00000000,0x80000000,0x80000000,0x00800000,
 0x00800000,0x80800000,0x80800000,0x00800000,0x00800000,0x80800000,0x80800000,};
-static long	ipl2[16] = {
+static int32_t	ipl2[16] = {
 0x00000000,
 0x00004000,0x00000000,0x00004000,0x00000040,0x00004040,0x00000040,0x00004040,0x00000000,
 0x00004000,0x00000000,0x00004000,0x00000040,0x00004040,0x00000040,0x00004040,};
-static long	iph2[16] = {
+static int32_t	iph2[16] = {
 0x00000000,
 0x00000000,0x00004000,0x00004000,0x00000000,0x00000000,0x00004000,0x00004000,0x00000040,
 0x00000040,0x00004040,0x00004040,0x00000040,0x00000040,0x00004040,0x00004040,};
-static long	ipl3[16] = {
+static int32_t	ipl3[16] = {
 0x00000000,
 0x40000000,0x00000000,0x40000000,0x00400000,0x40400000,0x00400000,0x40400000,0x00000000,
 0x40000000,0x00000000,0x40000000,0x00400000,0x40400000,0x00400000,0x40400000,};
-static long	iph3[16] = {
+static int32_t	iph3[16] = {
 0x00000000,
 0x00000000,0x40000000,0x40000000,0x00000000,0x00000000,0x40000000,0x40000000,0x00400000,
 0x00400000,0x40400000,0x40400000,0x00400000,0x00400000,0x40400000,0x40400000,};
-static long	ipl4[16] = {
+static int32_t	ipl4[16] = {
 0x00000000,
 0x00002000,0x00000000,0x00002000,0x00000020,0x00002020,0x00000020,0x00002020,0x00000000,
 0x00002000,0x00000000,0x00002000,0x00000020,0x00002020,0x00000020,0x00002020,};
-static long	iph4[16] = {
+static int32_t	iph4[16] = {
 0x00000000,
 0x00000000,0x00002000,0x00002000,0x00000000,0x00000000,0x00002000,0x00002000,0x00000020,
 0x00000020,0x00002020,0x00002020,0x00000020,0x00000020,0x00002020,0x00002020,};
-static long	ipl5[16] = {
+static int32_t	ipl5[16] = {
 0x00000000,
 0x20000000,0x00000000,0x20000000,0x00200000,0x20200000,0x00200000,0x20200000,0x00000000,
 0x20000000,0x00000000,0x20000000,0x00200000,0x20200000,0x00200000,0x20200000,};
-static long	iph5[16] = {
+static int32_t	iph5[16] = {
 0x00000000,
 0x00000000,0x20000000,0x20000000,0x00000000,0x00000000,0x20000000,0x20000000,0x00200000,
 0x00200000,0x20200000,0x20200000,0x00200000,0x00200000,0x20200000,0x20200000,};
-static long	ipl6[16] = {
+static int32_t	ipl6[16] = {
 0x00000000,
 0x00001000,0x00000000,0x00001000,0x00000010,0x00001010,0x00000010,0x00001010,0x00000000,
 0x00001000,0x00000000,0x00001000,0x00000010,0x00001010,0x00000010,0x00001010,};
-static long	iph6[16] = {
+static int32_t	iph6[16] = {
 0x00000000,
 0x00000000,0x00001000,0x00001000,0x00000000,0x00000000,0x00001000,0x00001000,0x00000010,
 0x00000010,0x00001010,0x00001010,0x00000010,0x00000010,0x00001010,0x00001010,};
-static long	ipl7[16] = {
+static int32_t	ipl7[16] = {
 0x00000000,
 0x10000000,0x00000000,0x10000000,0x00100000,0x10100000,0x00100000,0x10100000,0x00000000,
 0x10000000,0x00000000,0x10000000,0x00100000,0x10100000,0x00100000,0x10100000,};
-static long	iph7[16] = {
+static int32_t	iph7[16] = {
 0x00000000,
 0x00000000,0x10000000,0x10000000,0x00000000,0x00000000,0x10000000,0x10000000,0x00100000,
 0x00100000,0x10100000,0x10100000,0x00100000,0x00100000,0x10100000,0x10100000,};
-static long	ipl8[16] = {
+static int32_t	ipl8[16] = {
 0x00000000,
 0x00000800,0x00000000,0x00000800,0x00000008,0x00000808,0x00000008,0x00000808,0x00000000,
 0x00000800,0x00000000,0x00000800,0x00000008,0x00000808,0x00000008,0x00000808,};
-static long	iph8[16] = {
+static int32_t	iph8[16] = {
 0x00000000,
 0x00000000,0x00000800,0x00000800,0x00000000,0x00000000,0x00000800,0x00000800,0x00000008,
 0x00000008,0x00000808,0x00000808,0x00000008,0x00000008,0x00000808,0x00000808,};
-static long	ipl9[16] = {
+static int32_t	ipl9[16] = {
 0x00000000,
 0x08000000,0x00000000,0x08000000,0x00080000,0x08080000,0x00080000,0x08080000,0x00000000,
 0x08000000,0x00000000,0x08000000,0x00080000,0x08080000,0x00080000,0x08080000,};
-static long	iph9[16] = {
+static int32_t	iph9[16] = {
 0x00000000,
 0x00000000,0x08000000,0x08000000,0x00000000,0x00000000,0x08000000,0x08000000,0x00080000,
 0x00080000,0x08080000,0x08080000,0x00080000,0x00080000,0x08080000,0x08080000,};
-static long	ipla[16] = {
+static int32_t	ipla[16] = {
 0x00000000,
 0x00000400,0x00000000,0x00000400,0x00000004,0x00000404,0x00000004,0x00000404,0x00000000,
 0x00000400,0x00000000,0x00000400,0x00000004,0x00000404,0x00000004,0x00000404,};
-static long	ipha[16] = {
+static int32_t	ipha[16] = {
 0x00000000,
 0x00000000,0x00000400,0x00000400,0x00000000,0x00000000,0x00000400,0x00000400,0x00000004,
 0x00000004,0x00000404,0x00000404,0x00000004,0x00000004,0x00000404,0x00000404,};
-static long	iplb[16] = {
+static int32_t	iplb[16] = {
 0x00000000,
 0x04000000,0x00000000,0x04000000,0x00040000,0x04040000,0x00040000,0x04040000,0x00000000,
 0x04000000,0x00000000,0x04000000,0x00040000,0x04040000,0x00040000,0x04040000,};
-static long	iphb[16] = {
+static int32_t	iphb[16] = {
 0x00000000,
 0x00000000,0x04000000,0x04000000,0x00000000,0x00000000,0x04000000,0x04000000,0x00040000,
 0x00040000,0x04040000,0x04040000,0x00040000,0x00040000,0x04040000,0x04040000,};
-static long	iplc[16] = {
+static int32_t	iplc[16] = {
 0x00000000,
 0x00000200,0x00000000,0x00000200,0x00000002,0x00000202,0x00000002,0x00000202,0x00000000,
 0x00000200,0x00000000,0x00000200,0x00000002,0x00000202,0x00000002,0x00000202,};
-static long	iphc[16] = {
+static int32_t	iphc[16] = {
 0x00000000,
 0x00000000,0x00000200,0x00000200,0x00000000,0x00000000,0x00000200,0x00000200,0x00000002,
 0x00000002,0x00000202,0x00000202,0x00000002,0x00000002,0x00000202,0x00000202,};
-static long	ipld[16] = {
+static int32_t	ipld[16] = {
 0x00000000,
 0x02000000,0x00000000,0x02000000,0x00020000,0x02020000,0x00020000,0x02020000,0x00000000,
 0x02000000,0x00000000,0x02000000,0x00020000,0x02020000,0x00020000,0x02020000,};
-static long	iphd[16] = {
+static int32_t	iphd[16] = {
 0x00000000,
 0x00000000,0x02000000,0x02000000,0x00000000,0x00000000,0x02000000,0x02000000,0x00020000,
 0x00020000,0x02020000,0x02020000,0x00020000,0x00020000,0x02020000,0x02020000,};
-static long	iple[16] = {
+static int32_t	iple[16] = {
 0x00000000,
 0x00000100,0x00000000,0x00000100,0x00000001,0x00000101,0x00000001,0x00000101,0x00000000,
 0x00000100,0x00000000,0x00000100,0x00000001,0x00000101,0x00000001,0x00000101,};
-static long	iphe[16] = {
+static int32_t	iphe[16] = {
 0x00000000,
 0x00000000,0x00000100,0x00000100,0x00000000,0x00000000,0x00000100,0x00000100,0x00000001,
 0x00000001,0x00000101,0x00000101,0x00000001,0x00000001,0x00000101,0x00000101,};
-static long	iplf[16] = {
+static int32_t	iplf[16] = {
 0x00000000,
 0x01000000,0x00000000,0x01000000,0x00010000,0x01010000,0x00010000,0x01010000,0x00000000,
 0x01000000,0x00000000,0x01000000,0x00010000,0x01010000,0x00010000,0x01010000,};
-static long	iphf[16] = {
+static int32_t	iphf[16] = {
 0x00000000,
 0x00000000,0x01000000,0x01000000,0x00000000,0x00000000,0x01000000,0x01000000,0x00010000,
 0x00010000,0x01010000,0x01010000,0x00010000,0x00010000,0x01010000,0x01010000,};
 
-static long
+static int32_t
 ip_low(block)
 register char block[8];
 {
-	register long l;
+	register int32_t l;
 
 	l  = ipl1[block[0] & 0xf];
 	l |= ipl0[(block[0] >> 4) & 0xf];
@@ -512,11 +514,11 @@
 	return l;
 }
 
-static long
+static int32_t
 ip_high(block)
 register char block[8];
 {
-	register long l;
+	register int32_t l;
 
 	l  = iph1[block[0] & 0xf];
 	l |= iph0[(block[0] >> 4) & 0xf];
@@ -962,7 +964,7 @@
   int size;
 {
     int i;
-    struct {long fo; char key[9];} s;
+    struct {int32_t fo; char key[9];} s;
 
     bcopy("encrypt!",s.key,8);
 
