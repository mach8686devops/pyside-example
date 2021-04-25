include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt
QT			+= widgets sql printsupport

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter23/ks23_02

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH

#TRANSLATIONS = ../../translations/ks23_02.ts

FORMS 		+= dialog.ui
				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks23_02.pro \
				qcustomplot.h \
				dialog.h
	
SOURCES    +=  main.cpp \
                dialog.cpp \
				qcustomplot.cpp

#RESOURCES	+= ks23_02.qrc

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		TARGET = ks23_02_d
	}
	CONFIG(release, debug|release) {   
		TARGET	= ks23_02
	}
} else {
	debug {		
		TARGET	= ks23_02_d
	}
	release {
		TARGET 	= ks23_02
	}
}
