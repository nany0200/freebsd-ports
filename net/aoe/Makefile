# Ports collection makefile for:	aoe (ATA Over Ethernet) driver
# Date created:				22 May 2006
# Whom:					Stacey D. Son <sds@son.org>
#
# $FreeBSD$
#

PORTNAME=	aoe
PORTVERSION=	1.2.0
CATEGORIES=	net
MASTER_SITES=	http://www.son.org/download/
DISTNAME=	${PORTNAME}-freebsd-${PORTVERSION}

MAINTAINER=	fjoe@FreeBSD.org
COMMENT=	FreeBSD driver for ATA over Ethernet (AoE)

NO_PACKAGE=	Should be in sync with the kernel to work correctly

WRKSRC=		${WRKDIR}/dev/aoe
MAN4=		aoe.4
USE_RC_SUBR=	aoe

pre-everything::
	@if [ ! -f /usr/src/sys/Makefile ]; then \
		${ECHO_MSG} ">> The AoE port needs FreeBSD kernel source code to compile."; \
		${ECHO_MSG} ">> Please install FreeBSD kernel source code in /usr/src/sys."; \
		${FALSE}; \
	fi

do-install:
	${MKDIR} ${PREFIX}/lib/aoe
	${INSTALL_KLD} ${WRKSRC}/aoe.ko ${PREFIX}/lib/aoe
	${INSTALL_MAN} ${WRKDIR}/aoe.4 ${PREFIX}/man/man4
	${CAT} ${PKGMESSAGE}

.include <bsd.port.mk>
