#!/bin/sh
/usr/local/Python3.8.1/bin/pyuic5 user.ui -o ui_user.py
/usr/local/Python3.8.1/bin/pyuic5 addsprint.ui -o ui_addsprint.py
/usr/local/Python3.8.1/bin/pyuic5 backlog.ui -o ui_backlog.py
/usr/local/Python3.8.1/bin/pyuic5 burndown.ui -o ui_burndown.py
/usr/local/Python3.8.1/bin/pyuic5 projects.ui -o ui_projects.py
/usr/local/Python3.8.1/bin/pyuic5 projectinfo.ui -o ui_projectinfo.py
/usr/local/Python3.8.1/bin/pyuic5 mainwidget.ui -o ui_mainwidget.py
/usr/local/Python3.8.1/bin/pyuic5 logindialog.ui -o ui_logindialog.py
/usr/local/Python3.8.1/bin/pyuic5 task.ui -o ui_task.py
/usr/local/Python3.8.1/bin/pyuic5 sprint.ui -o ui_sprint.py
/usr/local/Python3.8.1/bin/pyrcc5 ks24_03.qrc -o ks24_03_rc.py

/usr/local/Python3.8.1/bin/pylupdate5 ui_user.py ui_addsprint.py ui_backlog.py ui_burndown.py ui_projects.py ui_projectinfo.py ui_mainwidget.py  ui_logindialog.py ui_task.py ui_sprint.py cuser.py caddsprint.py cburndown.py cbacklog.py  cprojects.py cprojectinfo.py cmainwidget.py clogindialog.py ctask.py csprint.py config.py custombar.py customlabel.py customwidget.py  -ts ks24_03.ts
