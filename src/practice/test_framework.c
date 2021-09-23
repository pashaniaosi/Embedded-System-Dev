#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "setjmp.h"

typedef struct
{
    int output;
    // function input
    int a;
    int b;
    // function point
    int (*TestEMFunc)(int, int);
} S_EMTest;

// add a function to test
S_EMTest *addFunc(int (*TestEMFunc)(int, int), int a, int b, int output)
{
    S_EMTest *t_EMTest = (S_EMTest *)malloc(sizeof(S_EMTest));
    t_EMTest->a = a;
    t_EMTest->b = b;
    t_EMTest->TestEMFunc = TestEMFunc;
    t_EMTest->output = output;
    return t_EMTest;
}

// run test program to check the function
void runEMTest(S_EMTest *p_EMTest)
{
    if (p_EMTest != NULL)
    {
        int count = p_EMTest->TestEMFunc(p_EMTest->a, p_EMTest->b);
        if (count == p_EMTest->output)
        {
            printf("success.\n");
        }
        else
        {
            printf("failed %d != %d.\n", count, p_EMTest->output);
        }
    }
    free(p_EMTest);
}

// function to test
int add(int a, int b)
{
    return a + b;
}

int main(void)
{
    printf("start test.\n");
    S_EMTest *t_EMTest = addFunc(add, 1, 2, 4);
    runEMTest(t_EMTest);
}