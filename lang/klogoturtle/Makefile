# New ports collection makefile for:    klogoturtle
# Date created:                 2003-07-23
# Whom:                         Tilman Linneweh <arved@FreeBSD.org>
#
# $FreeBSD$

PORTNAME=	klogoturtle
PORTVERSION=	0.6
PORTREVISION=	10
CATEGORIES=	lang kde
MASTER_SITES=	http://klogoturtle.sourceforge.net/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	LOGO Interpreter for the KDE Desktop

USE_KDELIBS_VER=3
USE_AUTOTOOLS=	libtool
LDFLAGS+=	${PTHREAD_LIBS}

post-patch:
	@${REINPLACE_CMD} -e 's/-O2//g; s/-lpthread/${PTHREAD_LIBS}/g' \
		${WRKSRC}/configure

.include <bsd.port.mk>
