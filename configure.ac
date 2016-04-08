dnl
dnl configure.in for Ingar's Sudoku Solver
dnl
dnl see also http://qtnode.net/wiki/Qt_with_autotools
dnl

AC_INIT([Sudoku Solver], [0.1.0], [ingar@osirion.org], [sudokusolver])

AC_LANG_CPLUSPLUS
AC_PROG_CC
AC_PROG_CXX
AC_CONFIG_HEADERS(src/config.h)

AM_INIT_AUTOMAKE

dnl
dnl Qt installation prefix
dnl
AC_MSG_CHECKING(Qt installation prefix)
QTDIR=xxx
AC_ARG_WITH([qt-prefix],
             AC_HELP_STRING([--with-qt-prefix=], [to specify the path to the Qt installation prefix.]),
             [QTPATHS="$withval"],
             [QTPATHS="/usr /usr/qt"])

for x in $QTPATHS; do
    if test -d $x ; then
       QTDIR="$x"
    fi
done
if test $QTDIR = xxx ; then
   AC_MSG_ERROR(Could not locate Qt)
fi
AC_MSG_RESULT($QTDIR)

dnl
dnl Qt includes directory
dnl
AC_MSG_CHECKING(Qt includes directory)

AC_ARG_WITH([qt-includes],
             AC_HELP_STRING([--with-qt-includes=], [to specify the path to directory containing the Qt includes.]),
             [QTINCLUDEDIR="$withval"],
             [QTINCLUDEDIR="$QTDIR/include"])
AC_MSG_RESULT($QTINCLUDEDIR)

dnl
dnl libraries directory
dnl             
AC_MSG_CHECKING(Qt libraries directory)
AC_ARG_WITH([qt-libraries],
             AC_HELP_STRING([--with-qt-libraries=], [to specify the path to directory containing the Qt libraries.]),
             [QTLIBDIR="$withval"],
             [QTLIBDIR="$QTDIR/lib"])
AC_MSG_RESULT($QTLIBDIR)

AC_MSG_CHECKING([host type])
host=`uname -a`
case "$host" in
	MINGW32*)
		AC_MSG_RESULT(win32)
		QTLIBS="-L$QTLIBDIR -lgdi32 -luser32 -lmingw32 -lqtmain -lQt5Widgets -lQt5Gui -lQt5Core -mthreads -Wl,-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -Wl,-s -Wl,-s -Wl,-subsystem,windows"
		QTINC="-I$QTINCLUDEDIR -I$QTINCLUDEDIR/QtCore -I$QTINCLUDEDIR/QtGui -I$QTINCLUDEDIR/QtWidgets -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -DQT_NEEDS_QMAIN -frtti -fexceptions"
		QTBIN="$QTDIR/bin"
		EXEICON="icon.o"
		;;
	*)
		AC_MSG_RESULT(generic unix)
		AC_PATH_XTRA
		QTINC="-I$QTINCLUDEDIR -I$QTINCLUDEDIR/QtGui -I$QTINCLUDEDIR/QtCore -I$QTINCLUDEDIR/QtWidgets -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED"
		QTLIBS="-Wl,-rpath,QTLIBDIR -L$QTLIBDIR -lQt5Widgets -lQt5Gui -lQt5Core -lpthread"
		QTBIN="$QTDIR/bin"
		EXEICON=""
		;;
esac

AC_SUBST(EXEICON)

LIBS="$LIBS $QTLIBS"
INCLUDES="$INCLUDES $QTINC"
PATH="$PATH:$QTBIN"
CXXFLAGS="$CXXFLAGS $QTINC"

AC_MSG_CHECKING(if the compiler accepts -fPIC)
SAVED_CXXFLAGS="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -fPIC"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [return 0;])],
    [AC_MSG_RESULT(yes)
     CXXFLAGS="$SAVED_CXXFLAGS -fPIC"],
    [AC_MSG_RESULT(no)
     CXXFLAGS="$SAVED_CXXFLAGS"])

dnl Now we check whether we can actually build a Qt app.
cat > myqt.h << EOF
#include <QObject>
class Test : public QObject
{
Q_OBJECT
public:
  Test() {}
  ~Test() {}
public slots:
  void receive() {}
signals:
  void send();
};
EOF

cat > myqt.cpp << EOF
#include "myqt.h"
#include <QApplication>
int main( int argc, char **argv )
{
  QApplication app( argc, argv );
  Test t;
  QObject::connect( &t, SIGNAL(send()), &t, SLOT(receive()) );
}
EOF

AC_MSG_CHECKING(does moc work)
bnv_try_1="moc myqt.h -o moc_myqt.cpp"
AC_TRY_EVAL(bnv_try_1)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(moc doesn't work)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I compile moc_myqt.cpp)
bnv_try_2="$CXX -c $CXXFLAGS -o moc_myqt.o moc_myqt.cpp"
AC_TRY_EVAL(bnv_try_2)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't compile moc_myqt.cpp)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I compile myqt.cpp)
bnv_try_3="$CXX $QTINC -c $CXXFLAGS -o myqt.o myqt.cpp"
AC_TRY_EVAL(bnv_try_3)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't compile myqt.cpp)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I link against QT)
nv_try_4="$CXX $LIBS -o myqt myqt.o moc_myqt.o"
AC_TRY_EVAL(bnv_try_4)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't link)
fi
AC_MSG_RESULT(yes)

AC_MSG_CHECKING(for mkoctfile)
AC_TRY_EVAL(mkoctfile)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(mkoctfile is not in the path)
fi
AC_MSG_RESULT(yes)
rm -f moc_myqt.cpp myqt.h myqt.cpp myqt.o myqt moc_myqt.o

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT

AC_MSG_RESULT([

$PACKAGE_STRING

Configuration summary:

platform .................. $host
installation prefix ....... $prefix

includes .................. $INCLUDES
libraries ................. $LIBS
preprocessor flags ........ $CXXFLAGS
compiler flags ............ $CXXFLAGS

])
