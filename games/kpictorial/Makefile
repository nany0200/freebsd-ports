# New ports collection makefile for:	kpictorial
# Date created:				2003-10-13
# Whom:					arved
#
# $FreeBSD$

PORTNAME=	kpictorial
PORTVERSION=	0.9.1
PORTREVISION=	10
CATEGORIES=	games kde
MASTER_SITES=	SF/${PORTNAME}/${PORTNAME}/${PORTNAME}-${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Little logical game for KDE

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

USE_KDELIBS_VER=	3
USE_AUTOTOOLS=		libtool
USE_GMAKE=		yes

post-patch:
	${REINPLACE_CMD} -e "s,-lpthread,${PTHREAD_LIBS}," ${WRKSRC}/configure

.include <bsd.port.mk>
