define(`confEBINDIR',`%%PREFIX%%/libexec')
define(`confMANROOT',`%%PREFIX%%/man/cat')
define(`confMANROOTMAN',`%%PREFIX%%/man/man')
define(`confMBINDIR',`%%PREFIX%%/sbin')
define(`confSBINDIR',`%%PREFIX%%/sbin')
define(`confUBINDIR',`%%PREFIX%%/bin')
APPENDDEF(`conf_sendmail_ENVDEF', `-DTCPWRAPPERS')
APPENDDEF(`conf_sendmail_LIBS', `-lwrap')"
APPENDDEF(`conf_sendmail_ENVDEF', `-DNETINET6')
APPENDDEF(`conf_libmilter_ENVDEF', `-DNETINET6')
APPENDDEF(`conf_mail_local_ENVDEF', `-DQUEUE_ONLY')
APPENDDEF(`conf_smrsh_ENVDEF', `-DCMDDIR="\"%%PREFIX%%/libexec/sm.bin\""')
APPENDDEF(`conf_smrsh_ENVDEF', `-DPATH="\"/bin:/usr/bin\""')
