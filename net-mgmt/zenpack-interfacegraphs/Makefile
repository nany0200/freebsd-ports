# New ports collection makefile for: InterfaceGraphs
# Date created:    26 May 2011
# Whom:      Zenoss <zenoss@experts-exchange.com>
#
# $FreeBSD$
#

PORTNAME=	InterfaceGraphs
PORTVERSION=	1.0
CATEGORIES=	net-mgmt
MASTER_SITES=   https://github.com/zenoss/${ZPACKPREFIX}${PORTNAME}/tarball/master/
DISTNAME=       zenoss-${ZPACKPREFIX}${PORTNAME}-${TAG}

MAINTAINER=	zenoss@experts-exchange.com
COMMENT=	Provides a link that graphs all network interfaces for a device

PLIST_FILES=	zenoss/ZenPack/${ZPACK}
PLIST_DIRS=	zenoss/ZenPack

ZPACKGROUP=	community
ZPACKPREFIX=	ZenPacks.community.
WRKSRC=  ${WRKDIR}/zenoss-${ZPACKPREFIX}${PORTNAME}-${TAG}
TAG= 7ed2d7d

.include <bsd.port.pre.mk>
.include "${PORTSDIR}/Mk/bsd.zenoss.mk"
.include <bsd.port.post.mk>
