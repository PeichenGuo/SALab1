# SALab1

### 环境

GNU Make 4.2.1

gcc 9.3.0

### 使用说明

~~~ 
make run STEP=x
~~~

x=1,2,3 编译并运行前面几个

~~~
make matrix	
~~~

编译矩阵运算

~~~
make clean
~~~

清除.o和.exe

### Makefile

~~~makefile
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
~~~

可以见到矩阵优化我是关掉了编译器优化的

