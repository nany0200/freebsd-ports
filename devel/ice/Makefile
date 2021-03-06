# New ports collection makefile for:	ice
# Date created:		2004-02-02
# Whom:			Stefan Ehmann <shoesoft@gmx.net>
#
# $FreeBSD$
#

PORTNAME=	Ice
PORTVERSION=	3.4.2
PORTREVISION=	2
CATEGORIES=	devel
MASTER_SITES=	http://download.zeroc.com/Ice/3.4/

MAINTAINER=	freebsd@grem.de
COMMENT=	A modern alternative to object middleware such as CORBA/COM/DCOM/COM+

LIB_DEPENDS=	expat.6:${PORTSDIR}/textproc/expat2 \
		mcpp.3:${PORTSDIR}/devel/mcpp

OPTIONS=	TESTS "Build and run tests (requires lang/python)" on \
		DEMOS "Build demos" on

.include <bsd.port.options.mk>

.if defined(WITH_TESTS)
USE_PYTHON_BUILD=	yes
.endif

USE_GMAKE=	yes
USE_ICONV=	yes
USE_BDB=	42+
INVALID_BDB_VER=	2 3 40 41
USE_LDCONFIG=	yes
BUILD_WRKSRC=	${WRKSRC}/cpp
INSTALL_WRKSRC=	${WRKSRC}/cpp

CFLAGS+=	-ftemplate-depth-128 -fPIC -DPIC -Wall -D_REENTRANT ${PTHREAD_CFLAGS} -I${LOCALBASE}/include
.if defined(DEBUG)
CFLAGS+=	-g
.else
CFLAGS+=	-DNDEBUG
.endif

.include <bsd.port.pre.mk>
.if ${ARCH} == "ia64"
BROKEN=		does not compile on ia64
.endif

.if ${ARCH} == "sparc64"
BROKEN=		fails to link
.endif

.if ((${ARCH} != i386) && (${ARCH} != powerpc))
MAKE_ENV=	LP64=yes
.endif

.if !defined(WITH_TESTS)
MAKE_ENV+=	NOTESTS=yes
.endif

.if !defined(WITH_DEMOS)
MAKE_ENV+=	NODEMOS=yes
.endif

.if defined(NOPORTDOCS)
MAKE_ENV+=	NOPORTDOCS=yes
.endif

post-patch:
	${SED} 's|%%PTHREAD_LIBS%%|${PTHREAD_LIBS}|g; \
		s|%%PREFIX%%|${PREFIX}|g; \
		s|%%DATADIR%%|${DATADIR}|g; \
		s|%%DOCSDIR%%|${DOCSDIR}|g; \
		s|%%INSTALL_PROGRAM%%|${INSTALL_PROGRAM}|g; \
		s|%%INSTALL_DATA%%|${INSTALL_DATA}|g' \
		${FILESDIR}/Make.rules.FreeBSD > ${WRKSRC}/cpp/config/Make.rules.FreeBSD
	${REINPLACE_CMD} 's|%%BDB_LIB_CXX_NAME%%|${BDB_LIB_CXX_NAME}|g; \
		s|%%BDB_LIB_DIR%%|${BDB_LIB_DIR}|g; \
		s|%%BDB_INCLUDE_DIR%%|${BDB_INCLUDE_DIR}|g; \
		/install_docdir/d' \
		${WRKSRC}/cpp/config/Make.rules
	${REINPLACE_CMD} '/install_configdir/d' \
		${WRKSRC}/cpp/config/Make.rules
	${REINPLACE_CMD} 's|INSTALL_PROGRAM|INSTALL_DATA|g' \
		${WRKSRC}/cpp/src/ca/Makefile
	${REINPLACE_CMD} '/LICENSE/s/prefix/install_slicedir/' \
		${WRKSRC}/config/Make.common.rules

.if defined(WITH_TESTS)
TEST_CMD=	@cd ${BUILD_WRKSRC} && ${PYTHON_CMD} ./allTests.py
post-build:
	${TEST_CMD}
regression-test test: build
	${TEST_CMD}
.endif

.include <bsd.port.post.mk>
