# New ports collection makefile for: 	pmacct
# Date created:				Thu May  8 16:03:11 CEST 2003
# Whom:					Kirill Ponomarew <ponomarew@oberon.net>
#
# $FreeBSD$
#

PORTNAME=	pmacct
DISTVERSION=	0.14.0
CATEGORIES=	net-mgmt
MASTER_SITES=	http://www.pmacct.net/ \
		http://mirrors.rit.edu/zi/

MAINTAINER=	zi@FreeBSD.org
COMMENT=	Accounting and aggregation tool for IPv4 and IPv6 traffic

LICENSE=	GPLv2

USE_RC_SUBR=	pmacctd
SUB_FILES=	pkg-message
GNU_CONFIGURE=	yes
CPPFLAGS+=	"-I${LOCALBASE}/include"
LDFLAGS+=	"-L${LOCALBASE}/lib"

OPTIONS=	MYSQL "Enable MySQL support" off \
		PGSQL "Enable PostgreSQL support" off \
		SQLITE "Enable SQLite support" off \
		THREADS "Enable multi-threading" off \
		MMAP  "Enable mmap(2) support" on \
		LAYER2 "Enable Layer-2 support: MAC Adresses and VLANs" on \
		IPV6  "Enable IPv6 support" on \
		SHARED "Enable shared objects" on \
		DEBUG "Enable debugging" off

.include <bsd.port.pre.mk>

.if ${ARCH} == "amd64" || ${ARCH} == "sparc64"
CONFIGURE_ARGS+=--enable-64bit
.endif

.if defined(WITH_MYSQL)
USE_MYSQL=	yes
CONFIGURE_ARGS+=--enable-mysql
PLIST_SUB+=	WITH_MYSQL=""
.else
CONFIGURE_ARGS+=--disable-mysql
PLIST_SUB+=	WITH_MYSQL="@comment "
.endif

.if defined(WITH_PGSQL)
USE_PGSQL=	yes
CONFIGURE_ARGS+=--enable-pgsql
PLIST_SUB+=	WITH_PGSQL=""
.else
CONFIGURE_ARGS+=--disable-pgsql
PLIST_SUB+=	WITH_PGSQL="@comment "
.endif

.if defined(WITH_SQLITE)
USE_SQLITE=	yes
CONFIGURE_ARGS+=--enable-sqlite3 \
		--with-sqlite3-includes=${LOCALBASE}/include
.else
CONFIGURE_ARGS+=--disable-sqlite3
.endif

.if defined(WITHOUT_MMAP)
CONFIGURE_ARGS+=--disable-mmap
.else
CONFIGURE_ARGS+=--enable-mmap
.endif

.if defined(WITHOUT_LAYER2)
CONFIGURE_ARGS+=--disable-l2
.else
CONFIGURE_ARGS+=--enable-l2
.endif

.if defined(WITHOUT_IPV6)
CONFIGURE_ARGS+=--disable-ipv6
.else
CONFIGURE_ARGS+=--enable-ipv6
.endif

.if defined(WITH_THREADS)
CONFIGURE_ARGS+=--enable-threads
.else
CONFIGURE_ARGS+=--disable-threads
.endif

.if defined(WITHOUT_SHARED)
CONFIGURE_ARGS+=--disable-so
.endif

.if defined(WITH_DEBUG)
CONFIGURE_ARGS+=--enable-debug
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|-O2||g' ${WRKSRC}/configure

post-install:
.if !defined(NOPORTEXAMPLES)
	@${MKDIR} ${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/examples/* ${EXAMPLESDIR}
.endif
.if !defined(NOPORTDOCS)
	${MKDIR} ${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/docs/* ${DOCSDIR}
.for i in ChangeLog EXAMPLES FAQS README TOOLS CONFIG-KEYS KNOWN-BUGS
	${INSTALL_DATA} ${WRKSRC}/${i} ${DOCSDIR}
.endfor
.endif
	@${MKDIR} ${DATADIR}
	${INSTALL_DATA} ${WRKSRC}/sql/* ${DATADIR}
	@${CAT} ${PKGMESSAGE}

.include <bsd.port.post.mk>
