# New ports collection makefile for:	p5-WWW-2ch
# Date created:		2006-02-28
# Whom:			TAKAHASHI Kaoru <kaoru@kaisei.org>
#
# $FreeBSD$
#

PORTNAME=	WWW-2ch
PORTVERSION=	0.07
PORTREVISION=	1
CATEGORIES=	japanese www perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	kaoru@kaisei.org
COMMENT=	Perl module for scraping of 2ch.net BBS

RUN_DEPENDS=	${SITE_PERL}/LWP/UserAgent.pm:${PORTSDIR}/www/p5-libwww \
		${SITE_PERL}/Class/Accessor/Fast.pm:${PORTSDIR}/devel/p5-Class-Accessor
TEST_DEPENDS=	p5-UNIVERSAL-require>=0:${PORTSDIR}/devel/p5-UNIVERSAL-require

PERL_CONFIGURE=	yes

MAN3=		WWW::2ch.3	\
	WWW::2ch::Plugin::Base.3	\
	WWW::2ch::Res.3		\
	WWW::2ch::Subject.3	\
	WWW::2ch::Dat.3		\
	WWW::2ch::Plugin::Jbbs.3

.include <bsd.port.mk>
