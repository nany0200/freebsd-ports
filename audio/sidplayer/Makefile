# New ports collection makefile for:   sidplayer
# Date created:		27 May 2005
# Whom:			Emanuel Haupt <ehaupt@critical.ch>
#
# $FreeBSD$
#

PORTNAME=	sidplayer
PORTVERSION=	4.4
PORTREVISION=	4
CATEGORIES=	audio
MASTER_SITES=	http://sidplayer.cebix.net/downloads/ \
		CRITICAL
DISTNAME=	SIDPlayer-${PORTVERSION}

MAINTAINER=	ehaupt@FreeBSD.org
COMMENT=	A C64 SID tune player

LICENSE=	GPLv2

USE_SDL=	yes
GNU_CONFIGURE=	yes
MAKE_JOBS_SAFE=	yes

SDLINCLUDEDIR=	SDL

post-patch:
	@${REINPLACE_CMD} -e 's|SDL/SDL_endian\.h|${SDLINCLUDEDIR}/SDL_endian\.h|' \
		${WRKSRC}/src/main_sdl.cpp

do-install:
	${INSTALL} ${WRKSRC}/src/${PORTNAME} ${PREFIX}/bin/${PORTNAME}
.if !defined(NOPORTDOCS)
	${MKDIR} ${DOCSDIR}
	${CP} ${WRKSRC}/PSID\ Demo/* ${DOCSDIR}/
.endif

post-install:
	@${ECHO_MSG} "=============================================================="
	@${ECHO_MSG} "A huge SID tune archive can be found at http://hvsc.c64.org/"
.if !defined(NOPORTDOCS)
	@${ECHO_MSG} "You can find a few examples in ${DOCSDIR}"
.endif
	@${ECHO_MSG} "=============================================================="

.include <bsd.port.mk>
