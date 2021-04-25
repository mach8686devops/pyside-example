#!/bin/sh
/usr/local/Python3.8.1/bin/pyuic5 dialog.ui -o ui_dialog.py
/usr/local/Python3.8.1/bin/pyuic5 customwidget.ui -o ui_customwidget.py
/usr/local/Python3.8.1/bin/pyrcc5 ks17_01.qrc -o ks17_01_rc.py
