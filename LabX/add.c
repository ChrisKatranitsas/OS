#include <stdio.h>

void add(int *a, int *b, int *c, int *sum) {
    *sum = *a + *b + *c;
}

int main() {
    int num1 = 10, num2 = 20, num3 = 30, result = 0;

    add(&num1, &num2, &num3, &result);

    printf("The sum of %d, %d, and %d is %d\n", num1, num2, num3, result);
    return 0;
}
