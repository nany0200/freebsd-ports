# New ports collection makefile for:	CGI::Application::Plugin::ValidateRM
# Date created:				08 Nov 2005
# Whom:					Espen Tagestad <espen@tagestad.no>
#
# $FreeBSD$

PORTNAME=	CGI-Application-Plugin-ValidateRM
PORTVERSION=	2.4
CATEGORIES=	www perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	lippe@FreeBSD.org
COMMENT=	Help validate forms with the CGI::Application framework

BUILD_DEPENDS=	${SITE_PERL}/HTML/FillInForm.pm:${PORTSDIR}/www/p5-HTML-FillInForm \
		${SITE_PERL}/Data/FormValidator.pm:${PORTSDIR}/textproc/p5-Data-FormValidator \
		${SITE_PERL}/CGI/Carp.pm:${PORTSDIR}/www/p5-CGI-modules \
		${SITE_PERL}/CGI/Application.pm:${PORTSDIR}/www/p5-CGI-Application
RUN_DEPENDS:=	${BUILD_DEPENDS}

PERL_MODBUILD=	yes

WRKSRC=		${WRKDIR}/${PORTNAME}-${PORTVERSION}

MAN3=		CGI::Application::Plugin::ValidateRM.3

.include <bsd.port.mk>
