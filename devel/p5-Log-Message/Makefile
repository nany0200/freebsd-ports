# New ports collection makefile for:	p5-Log-Message
# Date created:				31 May 2006
# Whom:					Aaron Dalton <aaron@FreeBSD.org>
#
# $FreeBSD$
#

PORTNAME=	Log-Message
PORTVERSION=	0.04
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
MASTER_SITE_SUBDIR=	CPAN:BINGOS
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	Powerful and flexible message logging mechanism

BUILD_DEPENDS=	p5-Params-Check>=0:${PORTSDIR}/devel/p5-Params-Check \
		p5-Module-Load>=0:${PORTSDIR}/devel/p5-Module-Load \
		p5-Locale-Maketext-Simple>=0:${PORTSDIR}/devel/p5-Locale-Maketext-Simple
RUN_DEPENDS:=	${BUILD_DEPENDS}

MAN3=	Log::Message.3 \
	Log::Message::Config.3 \
	Log::Message::Handlers.3 \
	Log::Message::Item.3

PERL_CONFIGURE=	yes

.include <bsd.port.mk>
