CC = gcc
CXX = g++ -std=c++11
# AR ?= ar
# ARFLAGS = -scurv
# RANLIB ?= ranlib
 
# CFLAGS ?=
# CXXFLAGS ?=
# INCLUDE ?=
# LDFLAGS ?=
 
# CFLAGS   += -Wall -g -fPIC -pipe -Wl,-z -Wl,defs -DDEBUG
# CXXFLAGS += -Wall -g -fPIC -pipe -Wl,-z -Wl,defs -DDEBUG
 
# %.o: %.cpp 
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<
 
# %.o: %.c
# 	$(CC) $(CFLAGS) $(INCLUDE) -c $<

STEP1FLAG = -D _GNU_SOURCE

step1: step1.o
	$(CXX) -o step1 step1.o
step1.o: step1.cpp	
	$(CXX) $(STEP1FLAG) -c step1.cpp
clean:
	rm *.o; rm step1
run:
	make;./step1