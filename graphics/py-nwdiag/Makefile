# New ports collection makefile for:	py-nwdiag
# Date created:		2011-08-07
# Whom:			TAKATSU Tomonari <tota@FreeBSD.org>
#
# $FreeBSD$
#

PORTNAME=	nwdiag
PORTVERSION=	0.7.0
CATEGORIES=	graphics python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	tota@FreeBSD.org
COMMENT=	A simple network-diagram image generator

LICENSE=	AL2
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PKGNAMEPREFIX}imaging>=1.1.5:${PORTSDIR}/graphics/py-imaging \
		${PKGNAMEPREFIX}funcparserlib>=0.3.4:${PORTSDIR}/devel/py-funcparserlib \
		${PKGNAMEPREFIX}blockdiag>=1.1.0:${PORTSDIR}/graphics/py-blockdiag

USE_PYTHON=	2.4-2.7
USE_PYDISTUTILS=	easy_install

MAN1=	${PORTNAME}.1 rackdiag.1

DOCSDIR=	${PREFIX}/share/doc/${PKGNAMEPREFIX}${PORTNAME}
EXAMPLESDIR=	${PREFIX}/share/examples/${PKGNAMEPREFIX}${PORTNAME}

PORTDOCS=	README.txt
PORTEXAMPLES=	*

post-install:
.if !defined(NOPORTDOCS)
	@${MKDIR} ${DOCSDIR}
	@${INSTALL_DATA} ${INSTALL_WRKSRC}/src/${PORTDOCS} ${DOCSDIR}
.endif
.if !defined(NOPORTEXAMPLES)
	@${MKDIR} ${EXAMPLESDIR}
	@${INSTALL_DATA} \
		${INSTALL_WRKSRC}/examples/${PORTNAME}/${PORTEXAMPLES} \
		${EXAMPLESDIR}
.endif
.for f in ${MAN1}
	@${INSTALL_MAN} ${WRKSRC}/${f} ${MAN1PREFIX}/man/man1/
.endfor

x-generate-plist:
	${ECHO} bin/${PORTNAME} > pkg-plist.new
	${ECHO} bin/rackdiag >> pkg-plist.new
	${FIND} ${PYTHON_SITELIBDIR}/${PYEASYINSTALL_EGG} -type f | ${SORT} | \
	${SED} -e 's,${PYTHON_SITELIBDIR},%%PYTHON_SITELIBDIR%%,' \
		-e 's,${PYEASYINSTALL_EGG},%%PYEASYINSTALL_EGG%%,' \
		>> pkg-plist.new
	${FIND} ${PYTHON_SITELIBDIR}/${PYEASYINSTALL_EGG} -type d -depth | ${SORT} -r | \
	${SED} -e 's,${PYTHON_SITELIBDIR},@dirrm %%PYTHON_SITELIBDIR%%,' \
		-e 's,${PYEASYINSTALL_EGG},%%PYEASYINSTALL_EGG%%,' \
		>> pkg-plist.new

.include <bsd.port.mk>
