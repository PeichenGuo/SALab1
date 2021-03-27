// #define _GNU_SOURCE
#define L1CACHESIZE 64
#define TESTBATCH 10000
// #define ARRAYSIZE 5 * L1CACHESIZE * 1024 + 13
#define ARRAYSIZE 5 * 4096 * 1024 + 13
#define KB 0x400
#define BYTE 0x8

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
    
    char* a = new char[256 * TESTBATCH];//byte per elements
    int test = 1;//in kb
    int tmp;
    while(test <= 256){
        clock_t start = clock();
        for(int i = 0; i < TESTBATCH*test; i += test){
            asm volatile(
                "movl %1, %%edx\n\t"
                "movl %%edx, %0"
                :"=r"(tmp)
                :"m"(a[i])
                :"%edx"
            );
        }
        clock_t end = clock();
        printf("test %db: %lfms\n", test, (double)(end - start)/(double)(TESTBATCH));
        test *= 2;
    }
    delete[] a;

}