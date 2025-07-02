#include <stdio.h>

unsigned long long sum_of_digits(unsigned long long n) {
    unsigned long long sum = 0;
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

unsigned long long mm_method(unsigned long long n) {
    while (n >= 10) {
        n = sum_of_digits(n);
    }
    return n;
}

int main() {
    unsigned long long sum = 0;
    char vod;
    do {
        scanf("%c", &vod);
        if (vod >= '0' && vod <= '9') {
            sum += (unsigned long long)(vod - '0');
        } else {
            break;
        }
    } while (1);

    unsigned long long result = mm_method(sum);
    printf("%llu\n", result);
    
    return 0;
}
