# ex:ts=8
# Ports collection makefile for:	white_dune
# Date created:			Apr 12, 2002
# Whom:				ijliao
#
# $FreeBSD$
#

PORTNAME=	white_dune
PORTVERSION=	${DISTVERSION:S/pl/./}
DISTVERSION=	0.30pl5
PORTREVISION=	3
PORTEPOCH=	1
CATEGORIES=	graphics
MASTER_SITES=	http://vrml.cip.ica.uni-stuttgart.de/dune/ CENKES

MAINTAINER=	devel@stasyan.com
COMMENT=	Graphical VRML97 Editor and animation tool

LIB_DEPENDS=	jpeg.11:${PORTSDIR}/graphics/jpeg \
		png15:${PORTSDIR}/graphics/png

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

USE_XORG=	xft
USE_MOTIF=	yes
USE_GL=		gl glu glut
USE_SDL=	sdl
GNU_CONFIGURE=	yes
CONFIGURE_ENV=	YACC="/usr/bin/byacc"
CONFIGURE_ARGS=	--with-optimization \
		--without-devil \
		--with-helpurl="${DOCSDIR}/index.html" \
		--with-vrml97am1url="${DOCSDIR}/vrml97Amendment1" \
		--with-x3ddrafturl="${DOCSDIR}/x3dDraft" \
		--with-scriptednodesurl="${DOCSDIR}/scriptedNodes"
CPPFLAGS+=	`${SDL_CONFIG} --cflags` -DUSBHID_UCR_DATA -DUSBHID_NEW -D__FREEBSD__
LDFLAGS+=	`${SDL_CONFIG} --libs`
ALL_TARGET=	dune

MAN1=		dune.1 illegal2vrml.1

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/bin/dune ${PREFIX}/bin/
	@cd ${WRKSRC}/bin/&&${INSTALL_SCRIPT} dune4kids illegal2vrml ${PREFIX}/bin/
	@cd ${WRKSRC}/man/&&${INSTALL_MAN} ${MAN1} ${MAN1PREFIX}/man/man1/
.ifndef NOPORTDOCS
	@cd ${WRKSRC}/docs/&&${COPYTREE_SHARE} . ${DOCSDIR}/
.endif

.include <bsd.port.mk>
