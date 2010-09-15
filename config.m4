dnl $Id: config.m4,v 1.4 2008/06/30 21:18:25 phadej Exp $
dnl config.m4 for extension intarray

PHP_ARG_ENABLE(intarray, whether to enable intarray support,
[  --enable-intarray           Enable intarray support])

if test "$PHP_INTARRAY" != "no"; then
  PHP_INSTALL_HEADERS([ext/intarray], [intarray.h])

  PHP_NEW_EXTENSION(intarray, intarray.c, $ext_shared)
fi
