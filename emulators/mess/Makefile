# New ports collection makefile for:	sdlmess
# Date created:				2007-01-10
# Whom:					alepulver
#
# $FreeBSD$
#

PORTNAME=	mess
PORTVERSION=	0.146${PATCHSUFFIX}
CATEGORIES=	emulators
#MASTER_SITES=	http://www.mess.org/_media/downloads:/
MASTER_SITES=	http://ompldr.org/vZHV6ag/ \
		http://distfiles.exherbo.org/distfiles/ \
		http://www.umich.edu/~archive/apollo/
DISTNAME=	${PORTNAME}${PORTVERSION:S/.//:C/p[0-9]*$//}s
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} \
		${UPDATE_PATCHES:C/$/.zip/}
DIST_SUBDIR=	mame

MAINTAINER=	ports@FreeBSD.org
COMMENT=	The popular MESS (Multiple Emulator Super System)

LIB_DEPENDS=	FLAC:${PORTSDIR}/audio/flac \
		jpeg:${PORTSDIR}/graphics/jpeg \
		expat:${PORTSDIR}/textproc/expat2 \
		fontconfig:${PORTSDIR}/x11-fonts/fontconfig
RUN_DEPENDS=	liberation-fonts-ttf>=0:${PORTSDIR}/x11-fonts/liberation-fonts-ttf

OPTIONS_DEFINE=	BUILTIN_DEBUGGER DEBUG DOCS EXAMPLES
BUILTIN_DEBUGGER_DESC=	Enable builtin debugger support

NO_WRKSUBDIR=	yes

USE_ZIP=	yes
USE_XORG=	xext xi xinerama xrender
USE_GL=		gl
USE_SDL=	sdl ttf
USE_GCC=	4.6+
USE_GMAKE=	yes
MAKE_ENV=	NOWERROR=1 OPTIMIZE=0 USE_NETWORK=1 \
		OPT_FLAGS="${CXXFLAGS}" GCC_LDFLAGS="${LDFLAGS}"
MAKEFILE=	makefile
MAKE_JOBS_SAFE=	yes

SUB_FILES=	pkg-message

PATCHLEVEL=	# none

.if defined(PATCHLEVEL) && ${PATCHLEVEL}
PATCHSUFFIX=	p${PATCHLEVEL}
UPDATE_PATCHES!=	/usr/bin/jot -s " " \
		-w ${PORTNAME}${PORTVERSION:S/.//:C/\.p[0-9]*$//}u%d_diff \
		${PATCHLEVEL} 1 ${PATCHLEVEL}
.endif

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MBUILTIN_DEBUGGER}
USE_GNOME=	gtk20 gconf2
MAKE_ENV+=	GTK_INCPATH="$$(pkg-config --cflags-only-I gtk+-2.0 gconf-2.0)" \
		GTK_CCOMFLAGS="$$(pkg-config --cflags-only-other gtk+-2.0 gconf-2.0)" \
		GTK_LIBS="$$(pkg-config --libs gtk+-2.0 gconf-2.0)"
.else
MAKE_ENV+=	NO_DEBUGGER=1 \
		GTK_INCPATH="" \
		GTK_CCOMFLAGS="" \
		GTK_LIBS=""
.endif

.if ${PORT_OPTIONS:MDEBUG}
MAKE_ENV+=	DEBUG=1
.endif

.include <bsd.port.pre.mk>

.if ${ARCH} == "ia64" || ${ARCH} == "powerpc" || ${ARCH} == "sparc64"
BROKEN=		Does not install on ia64, powerpc, or sparc64
.endif

post-extract:
# Use post-extract target to get in before dos2unix-isation
.if defined(UPDATE_PATCHES)
. for patch in ${UPDATE_PATCHES:S/_/./}
	@${ECHO_MSG} -n "===> Applying upstream development patch ${patch}... "
	@${PATCH} ${PATCH_ARGS} < ${WRKSRC}/${patch}
	@${ECHO_MSG} "[DONE]"
. endfor
.endif

post-patch:
	@${REINPLACE_CMD} -e \
		's|^BUILD_EXPAT|# BUILD_EXPAT| ; \
		 s|^BUILD_ZLIB|# BUILD_ZLIB| ; \
		 s|^BUILD_FLAC|# BUILD_FLAC| ; \
		 s|^BUILD_JPEGLIB|# BUILD_JPEGLIB| ; \
		 s| = @gcc| := $$(CC)| ; \
		 s| = @g++| := $$(CXX)| ; \
		 s|^FULLNAME =.*|FULLNAME = $$(NAME)| ; \
		 /--warn-common/s|= -Wl,|= $$(GCC_LDFLAGS) -Wl,| ; \
		 /LDFLAGS/s|-s||' ${WRKSRC}/makefile
	@${REINPLACE_CMD} -e \
		'/-system/s|/usr/local/|${LOCALBASE}/| ; \
		 /--cflags-only-I gtk+-2.0/s|=.*|= $$(GTK_INCPATH)| ; \
		 /--cflags-only-other gtk+-2.0/s|=.*|= $$(GTK_CCOMFLAGS)| ; \
		 /--libs gtk+-2.0/s|=.*|= $$(GTK_LIBS)| ; \
		 /X11R6/s|^|#|' ${WRKSRC}/src/osd/sdl/sdl.mak

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${PREFIX}/bin
	@${MKDIR} ${PREFIX}/libexec/${PORTNAME}
.for FILE in castool chdman imgtool jedutil ldresample ldverify romcmp \
	testkeys unidasm
	${INSTALL_PROGRAM} ${WRKSRC}/${FILE} ${PREFIX}/libexec/${PORTNAME}
.endfor
	@${MKDIR} ${DATADIR}
	@(cd ${WRKSRC} && ${COPYTREE_SHARE} artwork ${DATADIR})
	@(cd ${WRKSRC} && ${COPYTREE_SHARE} hash ${DATADIR})
	@(cd ${WRKSRC}/src/osd/sdl && ${COPYTREE_SHARE} keymaps ${DATADIR})
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/*.txt ${DOCSDIR}
	@(cd ${WRKSRC} && ${COPYTREE_SHARE} docs ${DOCSDIR})
.endif
.if ${PORT_OPTIONS:MEXAMPLES}
	@${MKDIR} ${EXAMPLESDIR}
	${INSTALL_DATA} ${FILESDIR}/mess.ini ${EXAMPLESDIR}
.endif
	@${CAT} ${PKGMESSAGE}

.include <bsd.port.post.mk>
