include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TRANSLATIONS = ks03_02.ts

TARGET     	= ks03_02
TEMPDIR		= $$TRAIN_OBJ_PATH/chapter03/ks03_02

DESTDIR     = $$TRAIN_BIN_PATH

OBJECTS_DIR = $$TEMPDIR
MOC_DIR	= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

				
FORMS		+= dialog.ui

HEADERS		+= $$(TRAINDEVHOME)/src/gui_base.pri \
				ks03_02.pro \
				dialog.h
	
	
SOURCES    +=  main.cpp \
				dialog.cpp
				
				
debug_and_release {
	CONFIG(debug, debug|release) {	
	
		TARGET = ks03_02_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks03_02
	}
} else {
	debug {
	
		TARGET	= ks03_02_d
	}
	release {
		
		TARGET 	= ks03_02
	}
}