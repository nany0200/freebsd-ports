# Ports collection makefile for:	ocamlgsl
# Date created:				2011/04/10
# Whom:					Klaus T. Aehlig <aehlig@linta.de>
#
# $FreeBSD$
#

PORTNAME=	ocamlgsl
PORTVERSION=	0.6.0
CATEGORIES=	math
MASTER_SITES=	http://oandrieu.nerim.net/ocaml/gsl/

MAINTAINER=	aehlig@linta.de
COMMENT=	An interface to GSL for the Objective Caml langage

LIB_DEPENDS=	gsl:${PORTSDIR}/math/gsl
BUILD_DEPENDS=	gawk:${PORTSDIR}/lang/gawk \
		${OCAMLC_DEPEND}
RUN_DEPENDS=	ocamlfind:${PORTSDIR}/devel/ocaml-findlib

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

INSTALL_TARGET=	install-findlib

USE_GMAKE=	YES
USE_GCC=	4.2+
USE_OCAML=	YES
MAKE_ENV+=	OCAMLDIR=${OCAML_LIBDIR}
NO_OCAML_BUILDDEPENDS=	yes
USE_OCAML_LDCONFIG=	yes

.include <bsd.port.mk>
