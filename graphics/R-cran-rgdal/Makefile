# New ports collection makefile for:	R-cran-rgdal
# Date created:		2012-01-04
# Whom:			TAKATSU Tomonari <tota@FreeBSD.org>
#
# $FreeBSD$
#

PORTNAME=	rgdal
DISTVERSION=	0.7-12
PORTREVISION=	1
CATEGORIES=	graphics
DISTNAME=	${PORTNAME}_${DISTVERSION}

MAINTAINER=	tota@FreeBSD.org
COMMENT=	Bindings for the Geospatial Data Abstraction Library

LICENSE=	GPLv2 GPLv3
LICENSE_COMB=	dual

LIB_DEPENDS=	gdal:${PORTSDIR}/graphics/gdal \
		proj:${PORTSDIR}/graphics/proj
RUN_DEPENDS=	R-cran-sp>=0.9.99:${PORTSDIR}/math/R-cran-sp

USE_R_MOD=	yes
R_MOD_AUTOPLIST=	yes

R_POSTCMD_INSTALL_OPTIONS+=	--configure-args="--with-proj-lib=${LOCALBASE}"

.include <bsd.port.mk>
