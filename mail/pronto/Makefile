# New ports collection makefile for:	pronto
# Date created:		15 March 2001
# Whom:			killer	<killer@prosalg.no>
#
# $FreeBSD$

PORTNAME=	pronto
PORTVERSION=	2.4.0
PORTREVISION=	2
CATEGORIES=	mail perl5
MASTER_SITES=	http://muhri.net/pronto/

MAINTAINER=	araujo@FreeBSD.org
COMMENT=	A Mail Client for Gnome/Gtk written in Perl

BUILD_DEPENDS=\
		${SITE_PERL}/${PERL_ARCH}/Gtk.pm:${PORTSDIR}/x11-toolkits/p5-Gtk \
		${SITE_PERL}/${PERL_ARCH}/DBI.pm:${PORTSDIR}/databases/p5-DBI \
		${SITE_PERL}/DBD/CSV.pm:${PORTSDIR}/databases/p5-DBD-CSV \
		${SITE_PERL}/Date/Manip.pm:${PORTSDIR}/devel/p5-Date-Manip \
		${SITE_PERL}/SQL/Statement.pm:${PORTSDIR}/databases/p5-SQL-Statement \
		${SITE_PERL}/MIME/Tools.pm:${PORTSDIR}/mail/p5-MIME-Tools \
		${SITE_PERL}/MIME/Types.pm:${PORTSDIR}/mail/p5-MIME-Types \
		${SITE_PERL}/URI.pm:${PORTSDIR}/net/p5-URI \
		${SITE_PERL}/${PERL_ARCH}/HTML/Parser.pm:${PORTSDIR}/www/p5-HTML-Parser \
		${SITE_PERL}/Lingua/Ispell.pm:${PORTSDIR}/textproc/p5-Lingua-Ispell

.if defined(WITH_MYSQL)
BUILD_DEPENDS+=	${SITE_PERL}/${PERL_ARCH}/Mysql.pm:${PORTSDIR}/databases/p5-Mysql
.endif

RUN_DEPENDS:=	${BUILD_DEPENDS}

USE_PERL5=	yes

post-patch:
	@${FIND} ${WRKSRC} -type f | ${XARGS} ${REINPLACE_CMD} -e \
	's,/usr/local,${PREFIX},g' ${WRKSRC}/Makefile
	@${FIND} ${WRKSRC} -name "*".bak | ${XARGS} ${RM} -f

.include <bsd.port.mk>
