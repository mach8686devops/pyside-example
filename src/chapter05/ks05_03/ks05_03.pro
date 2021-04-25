include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_03/exe

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks05_03

FORMS 		+= prevwindow.ui \
				ctrlwindow.ui
				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks05_03.pro \
			   ctrlwindow.h \
			   prevwindow.h 	
				   
	
SOURCES    +=  main.cpp  \
				ctrlwindow.cpp \
				prevwindow.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {				   
		TARGET = ks05_03_d
	}
	CONFIG(release, debug|release) {			   
		TARGET	= ks05_03
	}
} else {
	debug {		
		TARGET	= ks05_03_d
	}
	release {
		TARGET 	= ks05_03
	}
}