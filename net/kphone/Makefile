# New ports collection Makefile for:		kphone
# Date created:					2004-07-05
# Whom:						arved
#
# $FreeBSD$

PORTNAME=	kphone
PORTVERSION=	4.2
PORTREVISION=	6
CATEGORIES=	net
MASTER_SITES=	http://www.wirlab.net/kphone/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	A voice over internet phone

WRKSRC=		${WRKDIR}/${PORTNAME}

USE_QT_VER=	3
USE_OPENSSL=	yes
USE_GMAKE=	yes
GNU_CONFIGURE=	yes
CFLAGS+=	${PTHREAD_CFLAGS}

post-patch:
	@${REINPLACE_CMD} -e "s|-O3||g ; \
		 s|-Wall|${CFLAGS}|g;s|-L/usr/X11R6/lib64|${PTHREAD_LIBS}|g; \
		 s|-lssl|-lssl -lcrypto|g" ${WRKSRC}/configure
	@${FIND} ${WRKSRC} -name "Makefile.in" | ${XARGS} ${REINPLACE_CMD} -e \
		's,make -C,$$(MAKE) -C,g ; \
		 s,/apps/,/,g ; \
		 s,-lresolv,${PTHREAD_LIBS},g'

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/kphone/kphone ${PREFIX}/bin
	${MKDIR} ${DATADIR}/icons
	${INSTALL_DATA} ${WRKSRC}/icons/*.png ${DATADIR}/icons
	${MKDIR} ${DATADIR}/translations
	${INSTALL_DATA} ${WRKSRC}/po/*.qm ${DATADIR}/translations

.include <bsd.port.mk>
