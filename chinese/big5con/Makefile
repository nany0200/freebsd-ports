# New ports collection makefile for:	big5con
# Date created:		07 Jan 1997
# Whom:			Hung-Chi Chu <hcchu@r350.ee.ntu.edu.tw>
#
# $FreeBSD$
#

PORTNAME=	big5con
PORTVERSION=	0.92i
CATEGORIES=	chinese
MASTER_SITES=	SF

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Big5 Chinese console

ONLY_FOR_ARCHS=	i386

.include <bsd.port.pre.mk>

.if ${OSVERSION} > 900007
BROKEN=		fails to build with new utmpx
.endif

post-patch:
	@${REINPLACE_CMD} -e 's,/dev/vga,/dev/ttyv0,g' ${WRKSRC}/src/*c
	@${REINPLACE_CMD} -e 's,GetShmem(),GetShmem(char),g' ${WRKSRC}/src/fnld.c
	@${REINPLACE_CMD} -e 's,#endif.*,#endif,g' ${WRKSRC}/include/ksymdef.h
	@${REINPLACE_CMD} -e 's,TOPDIR,PREFIX,g' ${WRKSRC}/big5con.mk

post-install:
	@${CAT} ${PKGMESSAGE}

.include <bsd.port.post.mk>
