# New ports collection makefile for:	xmms-nebulus
# Date created:				3 Oct 2002
# Whom:					David Yeske <dyeske@gmail.com>
#
# $FreeBSD$
#

PORTNAME=	xmms-nebulus
PORTVERSION=	0.8.0
PORTREVISION=	5
CATEGORIES=	graphics
MASTER_SITES=	http://nebulus.tuxfamily.org/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	A XMMS visualization plugin that uses SDL and OpenGL

BUILD_DEPENDS=	xmms-config:${PORTSDIR}/multimedia/xmms
RUN_DEPENDS=	xmms:${PORTSDIR}/multimedia/xmms

PLIST_FILES=	lib/xmms/Visualization/libnebulus.so
USE_SDL=	sdl
USE_GL=		yes
USE_GNOME=	gtk12
USE_BZIP2=	yes
GNU_CONFIGURE=	yes

CPPFLAGS+=	-I${LOCALBASE}/include

post-patch:
	@${REINPLACE_CMD} -e \
		's|-Wall||' \
		${WRKSRC}/src/Makefile.in

.include <bsd.port.mk>
