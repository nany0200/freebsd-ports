# New ports collection makefile for:	Devel::KYTProf
# Date created:		20 Oct 2011
# Whom:			Jun Kuriyama <kuriyama@FreeBSD.org>
#
# $FreeBSD$
#

PORTNAME=	Devel-KYTProf
PORTVERSION=	0.01
PORTREVISION=	1
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	kuriyama@FreeBSD.org
COMMENT=	Perl extension for simple profiler

BUILD_DEPENDS=	p5-Class-Data-Inheritable>0:${PORTSDIR}/devel/p5-Class-Data-Inheritable \
		p5-UNIVERSAL-require>0:${PORTSDIR}/devel/p5-UNIVERSAL-require
RUN_DEPENDS:=	${BUILD_DEPENDS}

PERL_CONFIGURE=	yes

MAN3=	Devel::KYTProf.3 \
	Devel::README.3

.include <bsd.port.mk>
