# New ports collection makefile for:	CNS11643-font
# Date created:		2009/01/03
# Whom:			chinsan
#
# $FreeBSD$
#

PORTNAME=	CNS11643-font
PORTVERSION=	98.1
CATEGORIES=	chinese x11-fonts
MASTER_SITES=	http://www.cns11643.gov.tw/AIDB/file.do?path=download/%E5%AD%97%E5%9E%8B%E4%B8%8B%E8%BC%89%601q%60%E5%85%A8%E5%AD%97%E5%BA%AB%E6%AD%A3%E6%A5%B7%E9%AB%94/name/:kai \
		http://www.cns11643.gov.tw/AIDB/file.do?path=download/%E5%AD%97%E5%9E%8B%E4%B8%8B%E8%BC%89%601q%60%E5%85%A8%E5%AD%97%E5%BA%AB%E6%AD%A3%E5%AE%8B%E9%AB%94/name/:sung
DISTFILES=	TW-Kai-98_1.ttf:kai TW-Sung-98_1.ttf:sung
EXTRACT_ONLY=

MAINTAINER=	lhd@cs.nctu.edu.tw
COMMENT=	A combine of Kai and Sung with CNS11643 TrueType Fonts

DIST_SUBDIR=	${PORTNAME}
NO_WRKSUBDIR=	yes
NO_BUILD=	yes
RESTRICTED=	No redistribution or commercial use is allowed.

TTF=		TW-Kai-98_1.ttf TW-Sung-98_1.ttf

do-install:
	@${MKDIR} ${FONTSDIR}
	${INSTALL_DATA} ${DISTDIR}/${PORTNAME}/TW-Kai-98_1.ttf ${FONTSDIR}
	${INSTALL_DATA} ${DISTDIR}/${PORTNAME}/TW-Sung-98_1.ttf ${FONTSDIR}

.include <bsd.port.pre.mk>
.include "${PORTSDIR}/chinese/ttfm/Makefile.ttf"
.include <bsd.port.post.mk>
