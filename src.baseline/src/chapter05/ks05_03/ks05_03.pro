TEMPLATE	= app
LANGUAGE	= C++
CONFIG		+= qt
QT         += widgets

TARGET     	= ks05_03

FORMS 		+= dialog.ui

HEADERS		+= ks.pro \
			   dialog.h 
	
	
SOURCES    += \
			    main.cpp \
				dialog.cpp
