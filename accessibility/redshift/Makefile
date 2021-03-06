# New ports collection makefile for:   redshift
# Date created:        Wed Nov 24 12:35:17 CST 2010
# Whom:                Mark Felder <feld@feld.me>
#
# $FreeBSD$
#

PORTNAME=	redshift
PORTVERSION=	1.7
PORTREVISION=	1
CATEGORIES=	accessibility
MASTER_SITES=	http://launchpad.net/redshift/trunk/${PORTVERSION}/+download/

MAINTAINER=	feld@feld.me
COMMENT=	Adjusts the color temperature of your screen

FETCH_ARGS=	"-pRr"
USE_GMAKE=	yes
USE_BZIP2=	yes
GNU_CONFIGURE=	yes
INSTALLS_ICONS=	yes
MAN1=		redshift.1
MANCOMPRESSED=	no

CONFIGURE_ARGS+=	--disable-wingdi

OPTIONS_DEFINE=	GUI NLS RANDR VIDMODE
OPTIONS_DEFAULT=	RANDR

GUI_DESC=	Tray icon and location via Gnome clock
RANDR_DESC=	Support RANDR for changing colors
VIDMODE_DESC=	Support VIDMODE for changing colors (NVIDIA)

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MNLS)
USE_GETTEXT=	yes
CONFIGURE_ARGS+=--with-libiconv-prefix=${LOCALBASE} \
                --with-libintl-prefix=${LOCALBASE}
PLIST_SUB=	NLS=""
.else
CONFIGURE_ARGS+=--disable-nls
PLIST_SUB=	NLS="@comment "
.endif

.if ${PORT_OPTIONS:MRANDR}
CONFIGURE_ARGS+=--enable-randr
USE_XORG=	xrandr
.else
CONFIGURE_ARGS+=--disable-randr
.endif

.if ${PORT_OPTIONS:MVIDMODE}
CONFIGURE_ARGS+=--enable-vidmode
.else
CONFIGURE_ARGS+=--disable-vidmode
.endif

.if ${PORT_OPTIONS:MGUI}
CONFIGURE_ARGS+=--enable-gui --enable-gnome-clock
RUN_DEPENDS+=	py-gtk2:${PORTSDIR}/x11-toolkits/py-gtk2 \
		py-xdg:${PORTSDIR}/devel/py-xdg
PLIST_SUB+=	GUI=""
.else
CONFIGURE_ARGS+=--disable-gui --disable-gnome-clock
PLIST_SUB+=	GUI="@comment "
.endif

.include <bsd.port.mk>
