include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets concurrent

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter13/ks13_04

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/base/basedll

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks13_04.pro
	
SOURCES    +=  main.cpp
				
#FORMS		+= dialog.ui

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		LIBS   += -lbasedll_d   
		TARGET = ks13_04_d
	}
	CONFIG(release, debug|release) {			   
		LIBS   += -lbasedll				   
		TARGET	= ks13_04
	}
} else {
	debug {
		LIBS   += -lbasedll_d		
		TARGET	= ks13_04_d
	}
	release {			   
		LIBS   += -lbasedll		
		TARGET 	= ks13_04
	}
}