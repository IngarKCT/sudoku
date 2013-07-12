bin_PROGRAMS = sudokusolver

# Project C++ source files
sudokusolver_SOURCES = \
	cell.cc \
	main.cc \
	mainwindow.cc \
	solverwindow.cc \
	sudoku.cc \
	sudokuwidget.cc

# moc generated C++ source files
nodist_sudokusolver_SOURCES = \
	moc_mainwindow.cc \
	moc_solverwindow.cc \
	moc_sudokuwidget.cc

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cc: %.h
	moc $< -o $@

