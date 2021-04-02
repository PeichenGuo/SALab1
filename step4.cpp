// #define _GNU_SOURCE
#define TESTBATCH 100000
#define MAXLENGTH 4096

#include <iostream>
#include <sched.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

void threadBund(){
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(10, &mask);
    if(sched_setaffinity(0, sizeof(mask), &mask) < 0){
        perror("sched_setaffinity went wrong\n");
    }else{
        printf("thread set done\n");
    }
}

int main(){
    threadBund();
    char* a = new char[TESTBATCH * 1024];//byte per elements
    int test = 1;//in kb
    // test LRU
    int size = test * 1024; 
    register int step = 64;
    register int k = 0;
    int register head = 0;

    clock_t start = clock();
    for(int i = 0; i < TESTBATCH; i ++){
        int tmp;
        asm volatile(
            "movl %1, %%edx\n\t"
            "movl %%edx, %0"
            :"=r"(tmp)
            :"m"(a[k])
            :"%edx"
        );
        k += step;
    }
    clock_t end = clock();
    printf("test %dkb: %lfms\n", test, (double)(end - start)/(double)(TESTBATCH));

    delete[] a;

}