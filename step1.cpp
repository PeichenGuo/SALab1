#define _GUN_SOURCE
#define TESTBATCH 100000
#define MAXLENGTH 4096
#define KB 0x400

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
    int* a = new int[MAXLENGTH * KB];
    int test = 1;//in kb
    while(test < MAXLENGTH){
        int size = test * KB; 
        int step = size / TESTBATCH;
        int k = 0;
        clock_t start = clock();
        for(int i = 0; i < TESTBATCH; i ++){
            int b = a[k];
            k += step;
        }
        clock_t end = clock();
        printf("test %dkb: %lfms\n", test, (double)(end - start)/(double)(TESTBATCH));
        test *= 2;
    }
    delete[] a;

}