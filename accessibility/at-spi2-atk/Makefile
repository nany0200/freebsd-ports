# New ports collection makefile for:   at-spi
# Date Created:			12 April 2002
# Whom:				Maxim Sobolev <sobomax@FreeBSD.org>
#
# $FreeBSD$
#   $MCom: ports/accessibility/at-spi2-atk/Makefile,v 1.16 2010/11/16 11:53:13 kwm Exp $
#

PORTNAME=	at-spi2-atk
PORTVERSION=	0.4.1
PORTREVISION=	1
CATEGORIES=	accessibility x11-toolkits
MASTER_SITES=	GNOME
DIST_SUBDIR=	gnome2

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Assisted Technology Provider module for GTK+

LIB_DEPENDS=	dbus-glib-1.2:${PORTSDIR}/devel/dbus-glib
RUN_DEPENDS=	${LOCALBASE}/libexec/at-spi2-registryd:${PORTSDIR}/accessibility/at-spi2-core

LICENSE=        LGPL21
LICENSE_FILE=   ${WRKSRC}/COPYING
USE_BZIP2=	yes
USE_GETTEXT=	yes
USE_GMAKE=	yes
USE_GNOME=	gnomehack gnomehier intlhack gconf2 libxml2
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--enable-static
CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
GCONF_SCHEMAS=	at-spi2.schemas

.include <bsd.port.mk>
