# New ports collection makefile for:   qpsmtpd
# Date created:        1 January 2007
# Whom:                Zane C. Bowers
#
# $FreeBSD$
#

PORTNAME=	qpsmtpd
PORTVERSION=	0.84
PORTREVISION=	5
CATEGORIES=	mail perl5
MASTER_SITES=	http://smtpd.develooper.com/files/
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	A flexible SMTP daemon written in Perl and featuring a plugin API

BUILD_DEPENDS=	spamd:${PORTSDIR}/mail/p5-Mail-SpamAssassin \
		p5-Data-Dumper>=0:${PORTSDIR}/devel/p5-Data-Dumper \
		p5-File-Temp>=0:${PORTSDIR}/devel/p5-File-Temp \
		p5-Mail-Tools>=0:${PORTSDIR}/mail/p5-Mail-Tools \
		p5-MIME-Base64>=0:${PORTSDIR}/converters/p5-MIME-Base64 \
		p5-Net-DNS>=0.39:${PORTSDIR}/dns/p5-Net-DNS \
		p5-Net-IP>=0:${PORTSDIR}/net-mgmt/p5-Net-IP \
		p5-Time-HiRes>0:${PORTSDIR}/devel/p5-Time-HiRes
RUN_DEPENDS:=	${BUILD_DEPENDS}

OPTIONS	=	MODPERL "Enable Apache Support via mod_perl"	On

.ifdef WITH_MODPERL
RUN_DEPENDS+=	${SITE_PERL}/${PERL_ARCH}/mod_perl2.pm:${PORTSDIR}/www/mod_perl2
.endif

MAKE_JOBS_SAFE=	yes

WRKSRC=		${WRKDIR}/${DISTNAME}
PERL_CONFIGURE=	yes

MAN1=	qpsmtpd-async.1
MAN3=		Qpsmtpd::Command.3 \
		Qpsmtpd::Constants.3 \
		Qpsmtpd::DSN.3 \
		Qpsmtpd::ConfigServer.3 \
		Qpsmtpd::Transaction.3 \
		Qpsmtpd::Address.3 \
		Qpsmtpd.3 \
		Qpsmtpd::Connection.3 \
		Qpsmtpd::Postfix.3 \
		Apache::Qpsmtpd.3

USE_RC_SUBR=	qpsmtpd

SUB_LIST+=	PERL=${PERL}
SUB_FILES+=	pkg-message

pre-configure:
	@${RM} ${WRKSRC}/plugins/milter

post-install:
	@${MKDIR} ${DATADIR}/
	@${MKDIR} ${DATADIR}/plugins
	@(cd ${WRKSRC}/plugins/ && ${COPYTREE_SHARE} \* ${DATADIR}/plugins/)
.if !defined(NOPORTDOCS)
	@${MKDIR} ${DOCSDIR}/
	@${INSTALL_DATA} ${WRKSRC}/README* ${DOCSDIR}/
.endif
.if !defined(NOPORTEXAMPLES)
	@${MKDIR} ${EXAMPLESDIR}/
	@(cd ${WRKSRC}/config.sample/ && ${COPYTREE_SHARE} \* ${EXAMPLESDIR}/)
.endif

.include <bsd.port.mk>
