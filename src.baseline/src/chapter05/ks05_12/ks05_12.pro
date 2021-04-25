include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_12/exe

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks05_12

RESOURCES 	+= ks05_12.qrc

FORMS 		+= dialog.ui \
				step1.ui \
				step2.ui \
				step3.ui
				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks05_12.pro \
			   dialog.h	\
			   step1.h \
			   step2.h \
			   step3.h
				   
	
SOURCES    +=  main.cpp  \
				dialog.cpp \
				step1.cpp \
				step2.cpp \
				step3.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {				   
		TARGET = ks05_12_d
	}
	CONFIG(release, debug|release) {			   
		TARGET	= ks05_12
	}
} else {
	debug {		
		TARGET	= ks05_12_d
	}
	release {
		TARGET 	= ks05_12
	}
}