# New ports collection makefile for:	bsdbktr_tvtune
# Date created:		Sun Jan  4 17:49:00 EST 2004
# Whom:			Mina Naguib <webmaster@topfx.com>
#
# $FreeBSD$
#

PORTNAME=	bsdbktr_tvtune
PORTVERSION=	0.02
CATEGORIES=	multimedia
MASTER_SITES=	http://mina.naguib.ca/dist/

MAINTAINER=	mina.website@naguib.ca
COMMENT=	A console Brooktree (bktr) TV tuner

ONLY_FOR_ARCHS=	alpha i386
PLIST_FILES=	bin/bsdbktr_tvtune
WRKSRC=	${WRKDIR}/${PORTNAME}
ALL_TARGET=	bsdbktr_tvtune

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/bsdbktr_tvtune ${PREFIX}/bin/

.include <bsd.port.mk>
