#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([modules/echo/mod_echo.c])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE
AM_PROG_UPC([upcc upc])
# Checks for programs.
LT_INIT
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_YACC
AC_PROG_CC
AC_PROG_CPP
AC_PROG_LEX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h libintl.h limits.h malloc.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h strings.h sys/file.h sys/param.h sys/socket.h sys/time.h syslog.h unistd.h utime.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UID_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_CHOWN
AC_FUNC_FORK
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit endgrent getcwd gethostbyname gettimeofday inet_ntoa memchr memmove memset select socket sqrt strcasecmp strchr strcspn strdup strerror strncasecmp strpbrk strrchr strspn strstr strtol])
AC_CONFIG_FILES([Makefile
                 modules/Makefile
                 modules/aaa/Makefile
                 modules/arch/unix/Makefile
                 modules/arch/win32/Makefile
                 modules/cache/Makefile
                 modules/cluster/Makefile
                 modules/core/Makefile
                 modules/database/Makefile
                 modules/dav/fs/Makefile
                 modules/dav/lock/Makefile
                 modules/dav/main/Makefile
                 modules/debugging/Makefile
                 modules/echo/Makefile
                 modules/examples/Makefile
                 modules/experimental/Makefile
                 modules/filters/Makefile
                 modules/generators/Makefile
                 modules/http/Makefile
                 modules/http2/Makefile
                 modules/ldap/Makefile
                 modules/loggers/Makefile
                 modules/lua/Makefile
                 modules/mappers/Makefile
                 modules/md/Makefile
                 modules/metadata/Makefile
                 modules/proxy/Makefile
                 modules/proxy/balancers/Makefile
                 modules/session/Makefile
                 modules/slotmem/Makefile
                 modules/ssl/Makefile
                 modules/test/Makefile
                 os/Makefile
                 os/os2/Makefile
                 os/unix/Makefile
                 os/win32/Makefile
                 server/Makefile
                 server/mpm/Makefile
                 server/mpm/event/Makefile
                 server/mpm/mpmt_os2/Makefile
                 server/mpm/prefork/Makefile
                 server/mpm/winnt/Makefile
                 server/mpm/worker/Makefile
                 srclib/Makefile
                 support/Makefile
                 test/Makefile])
AC_CONFIG_SUBDIRS([srclib/apr])
AC_OUTPUT
