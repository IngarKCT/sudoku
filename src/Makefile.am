SUFFIXES=rc
# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cc: %.h
	moc $< -o $@
	
# This rule lets GNU make compile *.rc windows resource files
.rc.o:
	windres $< -o $@

bin_PROGRAMS = sudokusolver

# Project C++ source files
sudokusolver_SOURCES = \
	cell.cc \
	main.cc \
	mainwindow.cc \
	solverwindow.cc \
	sudoku.cc \
	sudokuwidget.cc
	
EXTRA_sudokusolver_SOURCES = \
	icon.rc

sudokusolver_DEPENDENCIES = \
	$(EXEICON)

sudokusolver_LDADD =\
	$(EXEICON)
	
# moc generated C++ source files
nodist_sudokusolver_SOURCES = \
	moc_mainwindow.cc \
	moc_solverwindow.cc \
	moc_sudokuwidget.cc
