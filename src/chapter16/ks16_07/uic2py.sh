#!/bin/sh
/usr/local/Python3.8.1/bin/pyuic5 dialog.ui -o ui_dialog.py
/usr/local/Python3.8.1/bin/pyuic5 step1.ui -o ui_step1.py
/usr/local/Python3.8.1/bin/pyuic5 step2.ui -o ui_step2.py
/usr/local/Python3.8.1/bin/pyuic5 step3.ui -o ui_step3.py
/usr/local/Python3.8.1/bin/pyrcc5 ks16_07.qrc -o ks16_07_rc.py
