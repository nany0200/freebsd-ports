# New ports collection makefile for:	secretmaryochronicles
# Date created:		31 Jan 2008
# Whom:			Dmitry Marakasov <amdmi3@amdmi3.ru>
#
# $FreeBSD$
#

PORTNAME=	secretmaryochronicles
PORTVERSION=	1.10.git20120512
PORTREVISION=	3
CATEGORIES=	games
MASTER_SITES=	http://mirror.amdmi3.ru/distfiles/
#		SF/smclone/Secret%20Maryo%20Chronicles/${PORTVERSION}
DISTNAME=	smc-${PORTVERSION}

MAINTAINER=	amdmi3@FreeBSD.org
COMMENT=	Secret Maryo Chronicles two-dimensional platform game

LIB_DEPENDS=	CEGUIBase-0.7.7.0:${PORTSDIR}/graphics/cegui \
		boost_filesystem.4:${PORTSDIR}/devel/boost-libs \
		png15:${PORTSDIR}/graphics/png

USE_BZIP2=	yes
USE_AUTOTOOLS=	aclocal:env autoheader:env autoconf:env automake:env
GNU_CONFIGURE=	yes
USE_GMAKE=	yes
USE_SDL=	sdl image mixer ttf
USE_GL=		gl glu
USE_GETTEXT=	yes
MAKE_JOBS_SAFE=	yes

CPPFLAGS+=	-I${LOCALBASE}/include
CXXFLAGS+=	-DBOOST_FILESYSTEM_VERSION=3
LDFLAGS+=	-L${LOCALBASE}/lib

DATADIR=	${PREFIX}/share/smc

WRKSRC=		${WRKDIR}/smc

post-patch:
	@${REINPLACE_CMD} -e 's|/usr/local|${LOCALBASE}|' ${WRKSRC}/autogen.sh

run-autotools:
	cd ${WRKSRC} && ${SH} ./autogen.sh
	@${REINPLACE_CMD} -e '/^LIBS =/ s|$$|$$(INTLLIBS)|' \
		${WRKSRC}/src/Makefile.in

.if !defined(NOPORTDOCS)
PORTDOCS=	controls.html style.css

post-install:
	${MKDIR} ${DOCSDIR}
.for f in ${PORTDOCS}
	${INSTALL_DATA} ${WRKSRC}/docs/${f} ${DOCSDIR}
.endfor
.endif

.include <bsd.port.mk>
