# New ports collection makefile for:	spook
# Date created:		1 Sep 2008
# Whom:			Bruce M Simpson <bms@FreeBSD.org>
#
# $FreeBSD$
#

PORTNAME=	spook
PORTVERSION=	20050207
PORTREVISION=	3
CATEGORIES=	multimedia
MASTER_SITES=	http://www.litech.org/spook/dist/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Embedded RTP/RTSP/HTTP video streamer

# TODO: FireWire IIDC support (needs libraw1394, libdc1394).
# TODO: Test with Luigi-ified V4L input drivers e.g. pwc, etc.

OPTIONS= \
	JPEG	"With JPEG encoding support" on \
	MPEG4	"With MPEG4 encoding support" off \
	V4L	"With V4L input support" on

USE_BZIP2=	yes
USE_GMAKE=	yes

GNU_CONFIGURE=	yes
USE_AUTOTOOLS=	autoconf aclocal automake
AUTOMAKE_ARGS=	--add-missing

NOMAN=		defined

SUB_FILES=	pkg-message

LDFLAGS+=	-L${LOCALBASE}/lib
CFLAGS+=	-I${LOCALBASE}/include

.include <bsd.port.pre.mk>

.if !defined(WITHOUT_JPEG)
LIB_DEPENDS+=		jpeg.11:${PORTSDIR}/graphics/jpeg
CONFIGURE_ARGS+=	--enable-encoder-jpeg
.endif

.if defined(WITH_MPEG4)
LIB_DEPENDS+=		xvidcore.4:${PORTSDIR}/multimedia/xvid
CONFIGURE_ARGS+=	--enable-encoder-mpeg4
.endif

.if !defined(WITHOUT_V4L)
BUILD_DEPENDS+=		${LOCALBASE}/include/linux/videodev.h:${PORTSDIR}/multimedia/v4l_compat
CONFIGURE_ARGS+=	--enable-input-v4l
.endif

PLIST_FILES=	bin/spook bin/spookctl etc/spook.conf.dist

.if !defined(NOPORTDOCS)
PORTDOCS=	README
.endif

do-install:
.if !defined(NOPORTDOCS)
	@${MKDIR} ${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/README ${DOCSDIR}
.endif
	${INSTALL_PROGRAM} ${WRKSRC}/spook ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/spookctl ${PREFIX}/bin
	${INSTALL_DATA} ${WRKSRC}/spook.conf.dist ${PREFIX}/etc

.include <bsd.port.post.mk>
