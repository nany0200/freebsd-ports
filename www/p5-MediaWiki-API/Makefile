# New ports collection makefile for:	p5-MediaWiki-API
# Date created:		23.09.2008
# Whom:			Martin Wilke <miwi@FreeBSD.org>
#
# $FreeBSD$
#

PORTNAME=	MediaWiki-API
PORTVERSION=	0.39
CATEGORIES=	www perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	miwi@FreeBSD.org
COMMENT=	OOP MediaWiki engine client

BUILD_DEPENDS=	p5-libwww>=0:${PORTSDIR}/www/p5-libwww \
		p5-JSON-XS>=0:${PORTSDIR}/converters/p5-JSON-XS
RUN_DEPENDS:=	${BUILD_DEPENDS}
TEST_DEPENDS=	p5-JSON-Any>=0:${PORTSDIR}/converters/p5-JSON-Any

PERL_CONFIGURE=	yes

MAN3=		MediaWiki::API.3

.include <bsd.port.mk>
