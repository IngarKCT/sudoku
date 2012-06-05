bin_PROGRAMS = sudosolve

# You have two .cpp files you wrote, editor.cpp and another.cpp
# Remember to include the name of the resource file with the .cpp extension.
sudosolve_SOURCES = \
	main.cc \
	mainwindow.cc \
	sudoku.cc

# You have one .h file, it's called editor.h. Therefore, here I list
# its mocced name, moc_editor.cpp.
nodist_sudosolve_SOURCES = \
	moc_mainwindow.cc \
	moc_sudoku.cc

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cc: %.h
	moc $< -o $@

