# New ports collection makefile for:	p5-CSS-Squish
# Date created:				18 Jun 2006
# Whom:					Aaron Dalton <aaron@FreeBSD.org>
#
# $FreeBSD$
#

PORTNAME=	CSS-Squish
PORTVERSION=	0.10
CATEGORIES=	textproc www perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	Compact many CSS files into one big file

RUN_DEPENDS=	p5-URI>=0:${PORTSDIR}/net/p5-URI
BUILD_DEPENDS:=	${RUN_DEPENDS}
BUILD_DEPENDS+=	p5-Test-LongString>=0:${PORTSDIR}/devel/p5-Test-LongString

MAKE_JOBS_SAFE=	yes

MAN3=	CSS::Squish.3

PERL_CONFIGURE=	yes

.include <bsd.port.mk>
