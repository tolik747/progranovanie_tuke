#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmp.h"
#include "transformations.h"

int main() {
    struct bmp_image* image;
    FILE *file = fopen("input.bmp", "rb");
    image = read_bmp(file);
    fclose(file); 
    image = flip_horizontally(image);
    image = flip_vertically(image);
    image = rotate_left(image);
    image = rotate_right(image);
    uint32_t start_x = 2;
    uint32_t start_y = 2;
    uint32_t width = 20;
    uint32_t height = 2;
    image = crop(image, start_y, start_x, height, width);

    int factor = 1;
    image = scale(image, factor);
    const char* colors_to_keep = "bg";
    image = extract(image, colors_to_keep);
    // // Write the modified image to a new file
    if(image){
        write_bmp(fopen("output.bmp", "wb"), image);
        free_bmp_image(image);
    }
    
    return 0;
}
