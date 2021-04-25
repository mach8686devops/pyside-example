del /S *.ilk
del /S *.pdb
del /S *.sdf
del /S *.ncb
del /S *.bak
del /S *.sln
del /S *.suo
del /S *.vcproj*
del /S *.vcxproj*
del /S *.pyproj*
del /S *.filters
del /S *.idb
del /S *makefile*
del /S *.ipch
del /S *.db
del /S *.suo
del /S *.qmake.stash
del /S *.user
del /S *.pyc
del /S *_rc.py
del /S ui_*.py
del /S ui_*.h
del /S *_resource.rc

for /R %%s in (.) do ( 
	echo %%s
	cd %%s
	rd /s /q debug
	rd /s /q release
	rd /s /q X64
	rd /s /q .vs
	rd /s /q bin
	rd /s /q obj
	rd /s /q __pycache__
) 

cd %TRAINDEVHOME%