# New ports collection makefile for:    etoile-foundation
# Date created:         22 Dec 2006
# Whom:                 dirk.meyer@dinoex.sub.org
#
# $FreeBSD$
#

PORTNAME=	foundation
PORTVERSION=	0.4.1
CATEGORIES=	devel gnustep
MASTER_SITES=	http://download.gna.org/etoile/
PKGNAMEPREFIX=	etoile-
DISTNAME=	etoile-${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Etoile Project EtoileFoundation framework

LICENSE=	BSD
LICENSE_FILE=	${WRKSRC}/Frameworks/EtoileFoundation/COPYING

IGNORE=		does not build with gcc runtime
DEPRECATED=	API no longer supported
EXPIRATION_DATE=	2012-07-20

USE_BZIP2=	yes
USE_GNUSTEP=	yes
USE_GNUSTEP_BACK=	yes
USE_GNUSTEP_BUILD=	yes
USE_GNUSTEP_INSTALL=	yes
USE_GNUSTEP_LDCONFIG=	${GNUSTEP_LOCAL_LIBRARIES}

DEFAULT_LIBVERSION=	0.2
WRKSRC=	${WRKDIR}/Etoile-${PORTVERSION}
USE_GNUSTEP_MAKE_DIRS+=	Frameworks/EtoileFoundation
DEFAULT_LIBVERSION2=	0.1
PLIST_SUB+=	LIBVERSION2=${DEFAULT_LIBVERSION2}
PLIST_SUB+=	MAJORLIBVERSION2=${DEFAULT_LIBVERSION2:C/([0-9]).*/\1/1}

.include <bsd.port.pre.mk>

do-configure:
.if (${ARCH} != i386)
	${REINPLACE_CMD} -e 's|ADDITIONAL_OBJCFLAGS += -march=i586||' \
		${WRKSRC}/Frameworks/EtoileFoundation/GNUmakefile
.endif
	${REINPLACE_CMD} -e 's|-Werror||' ${WRKSRC}/etoile.make

.include <bsd.port.post.mk>
