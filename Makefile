CC = gcc
CXX = g++ -std=c++11
(STEP) ?=
STEPFLAG = -D_GNU_SOURCE

step$(STEP).exe: step$(STEP).o
	$(CXX) -o step$(STEP).exe step$(STEP).o
step$(STEP).o: step$(STEP).cpp	
	$(CXX) $(STEPFLAG) -c step$(STEP).cpp
matrix_mul.o: matrix_mul.cpp
	$(CXX) $(STEPFLAG) -c matrix_mul.cpp
matrix_mul.exe: matrix_mul.o
	$(CXX) -g -O0 -o matrix_mul.exe matrix_mul.o 
clean:
	rm -rf *.o; rm -rf *.exe
run:
	make STEP=$(STEP);./step$(STEP).exe

matrix:
	make matrix_mul.exe;./matrix_mul.exe