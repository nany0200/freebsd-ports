# New ports collection makefile for:	py-msrplib
# Date created:		16 July 2011
# Whom:			Eugene Grosbein <ports@grosbein.net>
#
# $FreeBSD$
#

PORTNAME=	msrplib
PORTVERSION=	0.14.1
CATEGORIES=	net python
MASTER_SITES=	http://download.ag-projects.com/SipClient/ \
		http://www.grosbein.net/python/
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTNAME=	python-${PORTNAME}-${PORTVERSION}

MAINTAINER=	ports@grosbein.net
COMMENT=	Python MSRP client library

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}gnutls>=1.1.6:${PORTSDIR}/security/py-gnutls \
		${PYTHON_PKGNAMEPREFIX}twistedCore>=8.1.0:${PORTSDIR}/devel/py-twistedCore \
		${PYTHON_PKGNAMEPREFIX}twistedNames>=8.1.0:${PORTSDIR}/dns/py-twistedNames \
		${PYTHON_PKGNAMEPREFIX}eventlet>=0.9.15:${PORTSDIR}/net/py-eventlet \
		${PYTHON_PKGNAMEPREFIX}application>=1.1.0:${PORTSDIR}/devel/py-application \

RUN_DEPENDS:=	${BUILD_DEPENDS}

USE_PYTHON=	yes
USE_PYDISTUTILS=yes
PYDISTUTILS_PKGNAME=python_${PORTNAME}

.include <bsd.port.mk>
