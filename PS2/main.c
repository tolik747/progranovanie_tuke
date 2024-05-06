#include <stdio.h>
#include "hof.h"
#include "ui.h"
#include "k.h"
#include <stdbool.h>



int main(){


struct player player = {.name="Jack", .score=1849};
int size=10;
struct player list[10] = {
    {.score= 1880, .name="John"},
    {.score= 1568, .name="Jack"},
    {.score= 1123, .name="Jack"},
    {.score= 1035, .name="Manager"},
    {.score=  975, .name="Manager"},
    {.score=  844, .name="John"},
    {.score=  803, .name="John"},
    {.score=  749, .name="Sue"},
    {.score=  577, .name="Samuel"},
    {.score=  173, .name="Sue"}
};
bool result1 = add_player(list, &size, player);
printf("Result: %d\n", result1);
for(int g = 0; g < size; g++){
    printf("%s %d\n", list[g].name, list[g].score);
}
printf("Size: %d\n", load(list));
printf("Save: %d\n", save(list, size));

    return 0;
}