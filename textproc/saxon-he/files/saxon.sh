#!/bin/sh
#
# $FreeBSD$

IAM=`basename "$0"`

if [ "${IAM}" = "saxon-xquery" ]
then
	LAUNCHER_CLASS="net.sf.saxon.Query"
else
	LAUNCHER_CLASS="net.sf.saxon.Transform"
fi

SAXON_CLASSPATH=""
for jarfile in %%SAXON_JARS%%
do
	SAXON_CLASSPATH="${SAXON_CLASSPATH}:${jarfile}"
done

JAVA_VERSION="1.4+" "%%LOCALBASE%%/bin/java" -classpath "${SAXON_CLASSPATH}" "${LAUNCHER_CLASS}" "$@"
