# New ports collection makefile for:	RSIBreak
# Date created:			15 Mar 2006
# Whom:				Alex Dupre <ale@FreeBSD.org>
#
# $FreeBSD$
#

PORTNAME=	rsibreak
PORTVERSION=	0.8.0
PORTREVISION=	7
CATEGORIES=	x11 kde
MASTER_SITES=	http://www.rsibreak.org/files/

MAINTAINER=	ale@FreeBSD.org
COMMENT=	A KDE RSI prevention tool

PORTSCOUT=	limit:^0\.8\.

USE_BZIP2=	yes
USE_KDELIBS_VER=3
USE_AUTOTOOLS=	libtool
USE_GETTEXT=	yes
INSTALLS_ICONS=	yes
USE_XORG=	xscrnsaver

post-patch:
	@${REINPLACE_CMD} 's/install-data-local: install-apidox/install-data-local:/' \
		${WRKSRC}/rsibreak/Makefile.in ${WRKSRC}/rsibreak/src/Makefile.in

.include <bsd.port.mk>
