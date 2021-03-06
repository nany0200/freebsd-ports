# New ports collection makefile for:	Oracal Linux JRE 7.x
# Date created:				1 May 2012
# Whom:					Jung-uk Kim <jkim@FreeBSD.org>
#
# $FreeBSD$
#

PORTNAME=	jre
PORTVERSION=	${JRE_VERSION}.${JRE_UPDATE_VERSION}
CATEGORIES=	java
MASTER_SITES=	#
PKGNAMEPREFIX=	linux-sun-
DISTNAME=	jre-7u${JRE_UPDATE_VERSION}-linux-i586

MAINTAINER=	java@FreeBSD.org
COMMENT=	Oracle Java 7 Runtime Environment for Linux

RUN_DEPENDS=	javavm:${PORTSDIR}/java/javavmwrapper

NO_CDROM=	License does not allow distribution with fee
RESTRICTED=	Redistribution of repackaged binaries not permitted
LATEST_LINK=	linux-sun-jre17

WRKSRC=		${WRKDIR}/jre${DL_JRE_VERSION}
PLIST_SUB+=	T=${APP_HOME:S/^${PREFIX}\///} PORTVERSION=${PORTVERSION}
PKGINSTALL=	${WRKDIR}/pkg-install

NO_BUILD=	yes
USE_LINUX=	yes
USE_LINUX_APPS=	xorglibs
ONLY_FOR_ARCHS=	i386 amd64

JRE_VERSION=		7
JRE_INTERNAL_VERSION=	1.7.0
JRE_UPDATE_VERSION=	4
DL_JRE_VERSION=		${JRE_INTERNAL_VERSION}_0${JRE_UPDATE_VERSION}
DOWNLOAD_URL=		http://www.oracle.com/technetwork/java/javase/downloads/index.html

APP_HOME=	${PREFIX}/${PKGNAMEPREFIX}${PORTNAME}${JRE_INTERNAL_VERSION}
SCRIPT_FILES=	bin/jcontrol
BIN_DIRS=	bin

.include <bsd.port.pre.mk>

.if !exists(${DISTDIR}/${DISTNAME}${EXTRACT_SUFX}) && !defined(PACKAGE_BUILDING)
IGNORE?=You must manually fetch the J2SE RE download for the Linux platform (${DISTNAME}${EXTRACT_SUFX}) from ${DOWNLOAD_URL}, place it in ${DISTDIR} and then run make again
.endif

pre-everything::
	@${CAT} ${PKGMESSAGE}

post-patch:
.for script in ${SCRIPT_FILES}
	@${REINPLACE_CMD} -i.orig -e 's:^#!/bin/bash:#!/bin/sh:' ${WRKSRC}/${script}
.endfor
	@${FIND} ${WRKSRC} -name '*.orig' -delete

do-install:
	@${MKDIR} ${APP_HOME}
	@cd ${WRKSRC} && ${COPYTREE_SHARE} . ${APP_HOME}
.for dir in ${BIN_DIRS}
	@${CHOWN} -R ${BINOWN}:${BINGRP} "${APP_HOME}/${dir}"
	@${FIND} ${APP_HOME}/${dir} -type f -exec "${CHMOD}" ${BINMODE} "{}" \;
.endfor

post-install:
	${LOCALBASE}/bin/registervm "${APP_HOME}/bin/java # Linux-Sun-JRE${PORTVERSION}"
	@${SED} -e "s:%%JRE_HOME%%:${APP_HOME}:g" \
	  < ${FILESDIR}/pkg-install.in > ${PKGINSTALL}
	@${SETENV} PKG_PREFIX=${PREFIX} ${SH} ${PKGINSTALL} ${PKGNAME} POST-INSTALL

.include <bsd.port.post.mk>
