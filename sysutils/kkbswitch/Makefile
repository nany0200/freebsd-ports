# New ports collection makefile for:	kkbswitch
# Date created:				01 Oct 2003
# Whom:					Rashid N. Achilov <shelton@granch.ru>
#
# $FreeBSD$
#

PORTNAME=		kkbswitch
PORTVERSION=		1.4.3
PORTREVISION=	9
CATEGORIES=		sysutils kde
MASTER_SITES=		SF

MAINTAINER=		citycat4@ngs.ru
COMMENT=		Keyboard layout switcher and indicator for KDE 3.x

EXTRA_PATCHES=		${.CURDIR}/../../x11/kde3/files/extrapatch-old_configure

USE_KDELIBS_VER=	3
USE_GMAKE=		yes
USE_AUTOTOOLS=		libtool

CONFIGURE_ARGS += 	--with-qt-dir=${QT_PREFIX} \
			--with-extra-includes=${LOCALBASE}/include \
			--with-extra-libs=${LOCALBASE}/lib

DOCSDIR=		share/doc/HTML/en/${PORTNAME}

MAN1=			kkbswitch.1

OPTIONS=		RU_UA_LAYOUT	"With additional RU_UA keyboard layout" off

PLIST_SUB=		PREFIX=${PREFIX} \
			LOCALBASE=${LOCALBASE} \
			DOCSDIR=${DOCSDIR}

.include <bsd.port.pre.mk>

.if defined(WITH_RU_UA_LAYOUT)
CONFIGURE_ARGS+=	--enable-ru-ua-layout
PLIST_SUB+=		LAYOUT=""
.else
PLIST_SUB+=		LAYOUT="@comment "
.endif

.include <bsd.port.post.mk>
