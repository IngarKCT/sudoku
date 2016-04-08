SUFFIXES=rc
# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cc: %.h
	moc $< -o $@
	
# This rule lets GNU make compile *.rc windows resource files
.rc.o:
	windres $< -o $@

bin_PROGRAMS = sudoku

# Project C++ source files
sudoku_SOURCES = \
	cell.cc \
	main.cc \
	mainwindow.cc \
	settings.cc \
	solverwindow.cc \
	sudoku.cc \
	sudokuwidget.cc
	
EXTRA_sudoku_SOURCES = \
	icon.rc

sudoku_DEPENDENCIES = \
	$(EXEICON)

sudoku_LDADD =\
	$(EXEICON)
	
# moc generated C++ source files
nodist_sudoku_SOURCES = \
	moc_mainwindow.cc \
	moc_solverwindow.cc \
	moc_sudokuwidget.cc
