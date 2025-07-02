#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int distance;
    int speed;
} Move;

double calculateFunctionValue(double x, Move **moveSet, int n, int totalTime) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += (double)moveSet[i]->distance / (moveSet[i]->speed + x);
    }
    result -= totalTime;
    return result;
}

int main() {
    int n, totalTime;
    scanf("%d%d", &n, &totalTime);

    if (n < 1 || n > 1000 || totalTime < 1 || totalTime > 1000000) {
        return 1;
    }

    Move **moveSet = (Move **)malloc(n * sizeof(Move *));
    if (moveSet == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        moveSet[i] = (Move *)malloc(sizeof(Move));
        if (moveSet[i] == NULL) {
            // Освободить память для ранее выделенных структур Move
            for (int j = 0; j < i; j++) {
                free(moveSet[j]);
            }
            free(moveSet);
            return 1;
        }
    }

    int i = 0;
    while (i < n) {
        scanf("%d%d", &moveSet[i]->distance, &moveSet[i]->speed);
        if (moveSet[i]->distance < 1 || moveSet[i]->distance > 1000 || abs(moveSet[i]->speed) > 1000) {
            // Освободить память для всех структур Move и для массива указателей moveSet
            for (int j = 0; j <= i; j++) {
                free(moveSet[j]);
            }
            free(moveSet);
            return 1;
        }
        i++;
    }

    int minSpeed = moveSet[0]->speed;
    for (i = 1; i < n; i++) {
        if (moveSet[i]->speed < minSpeed) {
            minSpeed = moveSet[i]->speed;
        }
    }
    double a = -minSpeed;
    double b = 2001; 
    double k=0.0;
    double eps = 1e-8;
    
    while ((b - a) > eps) {
        k = (a + b) / 2;
        if (calculateFunctionValue(k, moveSet, n, totalTime) > 0) {
            a = k;
        } else {
            b = k;
        }
    }
    for (int i = 0; i < n; i++) {
        free(moveSet[i]);
    }
    free(moveSet);

    printf("%.9lf\n", k);

    return 0;
}
