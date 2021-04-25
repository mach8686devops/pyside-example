echo "Qt入门与提高-GUI产品开发 环境变量设置"

set QTDIR=C:\Qt\5.11.1
set QMAKESPEC=win32-msvc
set TRAINDEVHOME=E:\xingdianketang\project\qt5_pyqt5_v1
set TRAINBUILDBIT=64
set TRAINBUILDTYPE=all
set path=%TRAINDEVHOME%\lib;%TRAINDEVHOME%\bin;%QTDIR%\bin;%QTDIR%\lib;%path%
echo %QTDIR%
echo %QMAKESPEC%
echo %TRAINDEVHOME%