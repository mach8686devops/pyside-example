include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt
QT			+= widgets sql printsupport

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter23/ks23_03

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH

TRANSLATIONS = ../../translations/ks23_03.ts

FORMS 		+= mainwidget.ui \
                projects.ui \
                sprint.ui \
                user.ui \
                projectinfo.ui \
				logindialog.ui \
				backlog.ui \
				task.ui \
				addsprint.ui \
				burndown.ui
				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks23_03.pro \
                mainwidget.h \
                projects.h \
                sprint.h \
                user.h \
                projectinfo.h \
				logindialog.h \
				custombar.h \
				customlabel.h \
				customwidget.h \
				backlog.h \
				task.h \
				config.h \
				addsprint.h \
				qcustomplot.h \
				burndown.h
	
SOURCES    +=  main.cpp \
                mainwidget.cpp \
                projects.cpp \
                sprint.cpp \
                user.cpp \
                projectinfo.cpp \
				logindialog.cpp \
				custombar.cpp \
				customlabel.cpp \
				customwidget.cpp \
				backlog.cpp \
				task.cpp \
				config.cpp \
				addsprint.cpp \
				qcustomplot.cpp \
				burndown.cpp

RESOURCES	+= ks23_03.qrc

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		LIBS += -lbasedll_d
		TARGET = ks23_03_d
	}
	CONFIG(release, debug|release) {   
		LIBS += -lbasedll
		TARGET	= ks23_03
	}
} else {
	debug {		
		LIBS += -lbasedll_d
		TARGET	= ks23_03_d
	}
	release {
		LIBS += -lbasedll
		TARGET 	= ks23_03
	}
}
