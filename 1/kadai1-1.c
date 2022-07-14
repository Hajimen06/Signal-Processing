#include <stdio.h>

int f(int k) {
    int result = 0;
    for (int i = 0; i < k; ++i) {
        result += i * i - 10 * i;
    }
    return result;
}

int main() {
    printf("%d\n", f(25));
    printf("%d\n", f(50));
}
