# New ports collection makefile for:	filedupe
# Date created:			Apr 10, 2001
# Whom:				Mark Pulford <mark@kyne.com.au>
#
# $FreeBSD$
#

PORTNAME=	filedupe
PORTVERSION=	1.1
PORTREVISION=	2
CATEGORIES=	sysutils
MASTER_SITES=	http://sammy.net/~sammy/hacks/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	A utility for quickly finding duplicate files

LIB_DEPENDS=	gdbm.4:${PORTSDIR}/databases/gdbm

PLIST_FILES=	bin/filedupe

post-patch:
	${REINPLACE_CMD} -e 's|filename\[80\]|filename[1024]|g; \
		s|your_database|/var/db/filedupe.db|' ${WRKSRC}/filedupe.c

do-install:
	$(INSTALL_PROGRAM) ${WRKSRC}/filedupe ${PREFIX}/bin

.include <bsd.port.mk>
