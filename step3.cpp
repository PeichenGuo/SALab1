#define _GNU_SOURCE
#define L1CACHESIZE 64 * KB
#define TESTBATCH 1000000
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

    char* a = new char[L1CACHESIZE * 2];//byte per elements
    int test = 2;//in kb
    while(test <= 5){
        int register ways = pow(2, test - 2);
        int register blocks = pow(2, test-2);
        int register pass = L1CACHESIZE * 2 / blocks;
        // int register k = 64 * (rand() % ways);
        int register k = 0;
        int tmp;
        clock_t start = clock();
        //way1 
        //only visit odd blocks, i.e. i += L1CACHESIZE/test
        for(int i = 0; i < TESTBATCH; i += 1){//same times
            asm volatile(
                "movl %1, %%edx\n\t"
                "movl %%edx, %0"
                :"=r"(tmp)
                :"m"(a[k])
                :"%edx"
            );
            k += 2 * pass; //visit odd
            k = k % (L1CACHESIZE * 2);
        }

        //way2
        // for(int i = 0; i < TESTBATCH; i += 1){//same times
        //     // a[k] = '1';
        //     asm volatile(
        //         "movl %1, %%edx\n\t"
        //         "movl %%edx, %0"
        //         :"=r"(tmp)
        //         :"m"(a[k])
        //         :"%edx"
        //     );
        //     k = 64 * (rand() % ways);
        // }

        //way3
        // int register ways = pow(2, test);
        // int register pass = L1CACHESIZE * 2 / ways;
        // int register k = 64 * (rand() % ways);
        // for(int l = 0; l < TESTBATCH; l ++){
        //     for(int register i = 0; i < ways; i += 2){
        //         for(int register j = 0; j < pass; j ++){
        //             a[pass * i + j] = 1;
        //         }
        //     }
        // }
        
        clock_t end = clock();
        printf("test %d ways: %lfms\n", (int) pow(2,test - 2), (double)(end - start)/(double)(TESTBATCH));
        test += 1;
    }
    delete[] a;

}