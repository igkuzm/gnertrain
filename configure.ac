AC_INIT([GNerTrain], [1.0])
AC_CONFIG_FILES([Makefile])

AC_CANONICAL_HOST
AC_CANONICAL_BUILD

#dnl needed for CF_WITH_LIBTOOL
AC_CHECK_TOOL(AR, ar, ar)


# Detect the target system
case "${host_os}" in
    linux*)
        TARGETOS=Linux
        ;;
    cygwin*|mingw*)
        TARGETOS=Windows
        ;;
    darwin*)
        TARGETOS=Darwin
        ;;
    *)
        AC_MSG_ERROR(["OS $host_os is not supported"])
        ;;
esac

AC_SUBST([CC])

AC_SUBST([TARGETOS])

if test $host_os != $build_os
then
	CROSS_COMPILING=1
fi

AC_SUBST([CROSS_COMPILING])

# Checks for programs.
AC_PROG_CC

#char ARCHS
AS_VAR_IF(ARCHS, [], AS_IF([test "$host_cpu" = "powerpc"], ARCHS=ppc, ARCHS=[$host_cpu]))
AS_VAR_IF(ARCHS, [], AS_IF([test "$host_cpu" = "aarch64"], ARCHS=arm64, ARCHS=[$host_cpu]))
AC_SUBST([ARCHS])

AC_SUBST([CFLAGS])
AC_SUBST([LDFLAGS])

AC_SUBST([PKG_CONFIG_PATH])

AC_CHECK_PROG(PKG_CONFIG_EXISTS,[pkg-config],[pkg-config],[no])
if test "$PKG_CONFIG_EXISTS" = "no"
then
		# Notify user that pkg-tools are required
	AC_MSG_NOTICE([===================================================================================])
	AC_MSG_NOTICE([IMPORTANT: Make sure you have pkg-config installed - it's needed to build GTK GUI])
	AC_MSG_NOTICE([IMPORTANT: or use PKG_CONFIG_PATH=/path/to/pkg/config])		
	AC_MSG_NOTICE([===================================================================================])
	AC_MSG_ERROR([Please install required program 'pkg-config' and run script again.])
fi	
if	pkg-config --exists gtk+-2.0
then
	GTKCFLAGS=`pkg-config --cflags gtk+-2.0`
	GTKLIBS=`pkg-config --libs gtk+-2.0`
else
	AC_CHECK_LIB(gtk-2.0, main, [],[AC_MSG_ERROR([Could not find GTK+2 library])],[])
fi
AC_SUBST([GTKCFLAGS])		
AC_SUBST([GTKLIBS])		


AC_OUTPUT


########################################################################
GTKLIBSPATH=`echo $GTKLIBS|cut -d" " -f1`

echo ""
echo "        GNerdTrain $GNerdTrain_VERSION"
echo "        ======================"
echo ""
echo "        CC:				$CC"
echo "        HOST:				$host_os"
echo "        BUILD:				$build_os"
echo "        ARCHS:				$ARCHS"
echo "        TARGETOS:			$TARGETOS"
echo "        prefix:				$prefix"
echo ""
echo "        GTKLIBS:			$GTKLIBSPATH"
