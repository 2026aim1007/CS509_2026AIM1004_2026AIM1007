.PHONY: all run clean

all:
	cd assignment_01 && mingw32-make
	cd assignment_02 && mingw32-make
	cd assignment_03 && mingw32-make
	cd common_wrapper && mingw32-make

run:
	cd common_wrapper && mingw32-make run

clean:
	cd assignment_01 && mingw32-make clean
	cd assignment_02 && mingw32-make clean
	cd assignment_03 && mingw32-make clean
	cd common_wrapper && mingw32-make clean