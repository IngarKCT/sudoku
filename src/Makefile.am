bin_PROGRAMS = sudokusolver

# You have two .cpp files you wrote, editor.cpp and another.cpp
# Remember to include the name of the resource file with the .cpp extension.
sudokusolver_SOURCES = \
	cell.cc \
	main.cc \
	mainwindow.cc \
	solverwindow.cc \
	sudoku.cc \
	sudokuwidget.cc

# You have one .h file, it's called editor.h. Therefore, here I list
# its mocced name, moc_editor.cpp.
nodist_sudokusolver_SOURCES = \
	moc_mainwindow.cc \
	moc_solverwindow.cc \
	moc_sudokuwidget.cc

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cc: %.h
	moc $< -o $@

