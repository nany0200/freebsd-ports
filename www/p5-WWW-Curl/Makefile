# New ports collection makefile for:	p5-WWW-Curl
# Date created:				24 July 2003
# Whom:					Chris Larsen <darth@vader.dk>
#
# $FreeBSD$
#

PORTNAME=	WWW-Curl
PORTVERSION=	4.15
CATEGORIES=	www ftp perl5
MASTER_SITES=	CPAN \
		http://curl.haxx.se/libcurl/perl/
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Perl binding interface for curl

LICENSE=	MIT

LIB_DEPENDS=	curl.6:${PORTSDIR}/ftp/curl:install

PERL_CONFIGURE=	yes

MAN3=		WWW::Curl.3

post-patch:
		${FIND} ${WRKSRC} -type f -name \*.orig -delete

.include <bsd.port.mk>
