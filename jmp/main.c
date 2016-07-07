#include <stdio.h>
#include <setjmp.h>
 
jmp_buf jumper;
 
int div(int a, int b) {
    if (b == 0) { // can't divide by 0
        longjmp(jumper, -3);//跳到以jumper 所在的jmp point，进行处理，-3 相当于具体的exception code.
    }
    return a / b;

}
 
int main(int argc, char *argv[]) {
    int jstatus = setjmp(jumper);//相当于java catch,如果发生 jumper 异常，那么会跳回到这个jmp point
    if (jstatus == 0) {//第一次执行的时候是正确的setjmp return 0.
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        printf("%d/%d", a, b);
        int result = div(a, b);
        printf("=%d\n", result);
    } 
    else if (jstatus == -3)
        printf(" --> Error:divide by zero\n");
    else
        printf("Unhandled Error Case");
}

