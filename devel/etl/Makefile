# New ports collection makefile for:	ETL
# Date created:				25 Jun 2006
# Whom:					Yinghong Liu <relaxbsd@gmail.com>
#
# $FreeBSD$
#

PORTNAME=	etl
PORTVERSION=	0.04.15
CATEGORIES=	devel lang
MASTER_SITES=	SF/synfig/ETL/${PORTVERSION}
DISTNAME=	ETL-${PORTVERSION}

MAINTAINER=	dhn@FreeBSD.org
COMMENT=	Voria Extended Class and Template Library

USE_GNOME=	gnomehack pkgconfig
USE_GMAKE=	yes
GNU_CONFIGURE=	yes

post-install:
.if !defined(NOPORTDOCS)
	@${MKDIR} ${DOCSDIR}
.for doc in AUTHORS ChangeLog INSTALL NEWS README
	${INSTALL_DATA} ${WRKSRC}/${doc} ${DOCSDIR}
.endfor
.endif

.include <bsd.port.mk>
