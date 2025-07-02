#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bmp.h"
#include"transformations.h"
#include<math.h>
#include<stdint.h>

void flip1(struct bmp_image* image)
{
    int width = image->header->width;
    int height = image->header->height;
    int i = 0;

    while(i < height) {
        for (int j = 0; j < width / 2; j++) {
            struct pixel temp = image->data[i * width + j];
            image->data[i * width + j] = image->data[i * width + (width - j - 1)];
            image->data[i * width + (width - j - 1)] = temp;
        }
        i++;
    }
}

void flip2(struct bmp_image* image)
{
    int width = image->header->width;
    int height = image->header->height;    
    int i = 0;
    while (i < height / 2) {
        for (int j = 0; j < width; j++) {
            struct pixel temp = image->data[i * width + j];
            image->data[i * width + j] = image->data[(height - i - 1) * width + j];
            image->data[(height - i - 1) * width + j] = temp;
        }
        i++;
    }
}

struct bmp_image* flip_horizontally(const struct bmp_image* image)
{
    // if(!image){
    //     return NULL;
    // }
    // if(image==NULL){
    //     return NULL;
    // }
    // struct bmp_image* foto=(struct bmp_image*)malloc(sizeof(struct bmp_image));
    // if(foto==NULL){
    //     return NULL;
    // }
    // memcpy(foto,image,sizeof(struct bmp_image));
    // //free_bmp_image(image);
    // flip1(foto);
    
    // return foto;
    if (image == NULL) {
        return NULL;
    }

    struct bmp_image* flipped_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
    if (flipped_image == NULL) {
        return NULL;
    }

    flipped_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    if (flipped_image->header == NULL) {
        free(flipped_image);
        return NULL;
    }

    memcpy(flipped_image->header, image->header, sizeof(struct bmp_header));

    int data_size = (image->header->width*3)*image->header->height;
    flipped_image->data = (struct pixel*)malloc(data_size);
    if (flipped_image->data == NULL) {
        free(flipped_image->header);
        free(flipped_image);
        return NULL;
    }

    memcpy(flipped_image->data, image->data, data_size);
    flip1(flipped_image);
    return flipped_image;
}

struct bmp_image* flip_vertically(const struct bmp_image* image)
{
    // if(image==NULL){
        
    //     return NULL;
    // }
    // struct bmp_image* foto1=(struct bmp_image*)malloc(sizeof(struct bmp_image));
    // if(foto1==NULL){
    //     return NULL;
    // }
    // memcpy(foto1,image,sizeof(struct bmp_image));
    // flip2(foto1);
    // return foto1;
   if (image == NULL) {
        return NULL;
    }

    struct bmp_image* flipped_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
    if (flipped_image == NULL) {
        return NULL;
    }

    flipped_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    if (flipped_image->header == NULL) {
        free(flipped_image);
        return NULL;
    }

    memcpy(flipped_image->header, image->header, sizeof(struct bmp_header));

    int data_size = (image->header->width*3)*image->header->height;
    flipped_image->data = (struct pixel*)malloc(data_size);
    if (flipped_image->data == NULL) {
        free(flipped_image->header);
        free(flipped_image);
        return NULL;
    }

    memcpy(flipped_image->data, image->data, data_size);
    flip2(flipped_image);
    return flipped_image;
}

// struct bmp_image* create_rotated_image(const struct bmp_header* original_header, int new_width, int new_height) {
//     struct bmp_image* im = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
//     if (im == NULL) {
//         return NULL;
//     }
//     im->header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
//     if (im->header == NULL) {
//         free(im);
//         return NULL;
//     }
//     memcpy(im->header, original_header, sizeof(struct bmp_header));

//     im->header->width = new_width;
//     im->header->height = new_height;

//     im->data = (struct pixel*)calloc(new_width * new_height, sizeof(struct pixel));
//     if (im->data == NULL) {
//         free(im->header);
//         free(im);
//         return NULL;
//     }

//     return im;
// }


int calculate_padding(int width) {
    return (4 - (width * 3) % 4) % 4;
}

void calculate_rotated_image_params(const struct bmp_header* input_header, struct bmp_header* output_header) {
    output_header->width = input_header->height;
    output_header->height = input_header->width;
    int padding = calculate_padding(output_header->width);
    output_header->image_size = (output_header->width * 3 + padding) * output_header->height;
    output_header->size = output_header->image_size + sizeof(struct bmp_header);
}

struct bmp_image* rotate_right(const struct bmp_image* image) {
    if (image == NULL) {
        return NULL;
    }

    struct bmp_image* output = (struct bmp_image*)malloc(sizeof(struct bmp_image));
    output->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    memcpy(output->header, image->header, sizeof(struct bmp_header));
    
    calculate_rotated_image_params(image->header, output->header);
    
    output->data = (struct pixel*)malloc(output->header->image_size);

    int insert_idx = 0;
    for (int i = image->header->width - 1; i >= 0; --i) {
        for (int j = 0; j < image->header->height; ++j) {
            output->data[insert_idx] = image->data[j * image->header->width + i];
            insert_idx++;
        }
    }
    return output;
}
// printf("Assertion 'rotated_image->header->size == 78' failed. [got %d]\n", image->header->size);

struct bmp_image* rotate_left(const struct bmp_image* image) {
    if (image == NULL) {
        return NULL;
    }

    struct bmp_image* output = (struct bmp_image*)malloc(sizeof(struct bmp_image));
    output->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    memcpy(output->header, image->header, sizeof(struct bmp_header));
    
    calculate_rotated_image_params(image->header, output->header);
    
    output->data = (struct pixel*)malloc(output->header->image_size);
    int insert_idx = 0;
    for (int i = 0; i < image->header->width; ++i) {
        for (int j = image->header->height - 1; j >= 0; --j) {
            output->data[insert_idx] = image->data[j * image->header->width + i];
            insert_idx++;
        }
    }
    return output;
}
//crop
struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width) {
    if (image == NULL || start_y >= image->header->height || start_x >= image->header->width || start_y + height > image->header->height || start_x + width > image->header->width) {
        return NULL;
    }
    struct bmp_image* cropped_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
    if (cropped_image == NULL) {
        return NULL;
    }
    cropped_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    if (cropped_image->header == NULL) {
        free(cropped_image);
        return NULL;
    }
    *cropped_image->header = *image->header;
    cropped_image->header->height = height;
    cropped_image->header->width = width;
    int padding = (4 - (width * 3) % 4) % 4;
    cropped_image->header->image_size = (width * 3 + padding) * height;
    cropped_image->header->size = sizeof(struct bmp_header) + cropped_image->header->image_size;
    cropped_image->data = (struct pixel*)malloc(cropped_image->header->image_size);
    if (cropped_image->data == NULL) {
        free(cropped_image->header);
        free(cropped_image);
        return NULL;
    }
    for (uint32_t i = 0; i < height; i++) {
        uint32_t original_row = image->header->height - 1 - (start_y + i);
        uint32_t cropped_row = height - 1 - i;
        for (uint32_t j = 0; j < width; j++) {
            cropped_image->data[cropped_row * width + j] = image->data[original_row * image->header->width + start_x + j];
        }
    }
   
    return cropped_image;
}
//scal
int calculate_new_dimension(int original_dimension, float factor) {
    return round(original_dimension * factor);
}

struct bmp_image* create_scaled_image(const struct bmp_image* image, int new_width, int new_height) {
    struct bmp_image* scaled_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
    if (scaled_image == NULL) {
        return NULL;
    }

    scaled_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    if (scaled_image->header == NULL) {
        free(scaled_image);
        return NULL;
    }
    
    *scaled_image->header = *image->header;
    scaled_image->header->width = new_width;
    scaled_image->header->height = new_height;

    int padding = calculate_padding(new_width);
    scaled_image->header->image_size = (new_width * 3 + padding) * new_height;
    scaled_image->header->size = sizeof(struct bmp_header) + scaled_image->header->image_size;

    scaled_image->data = (struct pixel*)malloc(scaled_image->header->image_size);
    if (scaled_image->data == NULL) {
        free(scaled_image->header);
        free(scaled_image);
        return NULL;
    }
    return scaled_image;
}

struct bmp_image* scale(const struct bmp_image* image, float factor) {
    if (image == NULL || factor <= 0) {
        return NULL;
    }

    int new_width, new_height;

    if (factor < 1 || factor > 1) {
        new_width = calculate_new_dimension(image->header->width, factor);
        new_height = calculate_new_dimension(image->header->height, factor);
    } else { // якщо фактор масштабування рівний 1 то зображення залишається без змін
        new_width = image->header->width;
        new_height = image->header->height;
    }

    struct bmp_image* scaled_image = create_scaled_image(image, new_width, new_height);
    int i=0;
    while ( i <new_height) {
        for (int j = 0; j < new_width; j++) {    
            int new_x = j * image->header->width / new_width;
            int new_y = i * image->header->height / new_height;
            
            new_x = (new_x >= image->header->width) ? image->header->width - 1 : new_x;
            new_y = (new_y >= image->header->height) ? image->header->height - 1 : new_y;
            
            scaled_image->data[i * new_width + j] = image->data[new_y * image->header->width + new_x];
        }
        i++;
    }
    return scaled_image;
}

bool is_valid_color(char c) {
    return (c == 'r' || c == 'g' || c == 'b');
}
struct pixel extract_color(const struct pixel* original_pixel, const char* colors_to_keep) {
    struct pixel extracted_pixel = {0, 0, 0};
    if (original_pixel == NULL || colors_to_keep == NULL) {
        return extracted_pixel;
    }

    for (size_t i = 0; i < strlen(colors_to_keep); i++) {
        switch (colors_to_keep[i]) {
            case 'r':
                extracted_pixel.red = original_pixel->red;
                break;
            case 'g':
                extracted_pixel.green = original_pixel->green;
                break;
            case 'b':
                extracted_pixel.blue = original_pixel->blue;
                break;
            default:
                // Невідомий символ в рядку вибору кольорової складової
                return extracted_pixel;
        }
    }
    return extracted_pixel;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep) {
    if (image == NULL || colors_to_keep == NULL) {
        return NULL;
    }

    size_t color_count = strlen(colors_to_keep);
    for (size_t i = 0; i < color_count; i++) {
        if (!is_valid_color(colors_to_keep[i])) {
            return NULL;
        }
    }

    struct bmp_image* extracted_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
    if (extracted_image == NULL) {
        return NULL;
    }

    extracted_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    if (extracted_image->header == NULL) {
        free(extracted_image);
        return NULL;
    }
    memcpy(extracted_image->header, image->header, sizeof(struct bmp_header));

    extracted_image->data = (struct pixel*)malloc(image->header->width * image->header->height * sizeof(struct pixel));
    if (extracted_image->data == NULL) {
        free(extracted_image->header);
        free(extracted_image);
        return NULL;
    }

    for (uint32_t y = 0; y < image->header->height; y++) {
        for (uint32_t x = 0; x < image->header->width; x++) {
            struct pixel original_pixel = image->data[y * image->header->width + x];
            struct pixel extracted_pixel = extract_color(&original_pixel, colors_to_keep);
            extracted_image->data[y * image->header->width + x] = extracted_pixel;
        }
    }

    return extracted_image;
}

//
// struct pixel extract_color(const struct pixel* original_pixel, const char* colors_to_keep) {
//     struct pixel extracted_pixel = {0, 0, 0};
//     if (original_pixel == NULL || colors_to_keep == NULL) {
//         return extracted_pixel;
//     }

//     for (size_t i = 0; i < strlen(colors_to_keep); i++) {
//         switch (colors_to_keep[i]) {
//             case 'r':
//                 extracted_pixel.red = original_pixel->red;
//                 break;
//             case 'g':
//                 extracted_pixel.green = original_pixel->green;
//                 break;
//             case 'b':
//                 extracted_pixel.blue = original_pixel->blue;
//                 break;
//             default:
//                 // Невідомий символ в рядку вибору кольорової складової
//                 return extracted_pixel;
//         }
//     }
//     return extracted_pixel;
// }

// struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep) {
//     if (image == NULL || colors_to_keep == NULL) {
//         return NULL;
//     }

//     size_t color_count = strlen(colors_to_keep);
//     for (size_t i = 0; i < color_count; i++) {
//         if (!is_valid_color(colors_to_keep[i])) {
//             // Рядок вибору кольорової складової містить неправильний символ
//             return NULL;
//         }
//     }

//     struct bmp_image* extracted_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
//     if (extracted_image == NULL) {
//         return NULL;
//     }

//     extracted_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
//     if (extracted_image->header == NULL) {
//         free(extracted_image);
//         return NULL;
//     }
//     memcpy(extracted_image->header, image->header, sizeof(struct bmp_header));

//     extracted_image->data = (struct pixel*)malloc(image->header->width * image->header->height * sizeof(struct pixel));
//     if (extracted_image->data == NULL) {
//         free(extracted_image->header);
//         free(extracted_image);
//         return NULL;
//     }

//     for (uint32_t y = 0; y < image->header->height; y++) {
//         for (uint32_t x = 0; x < image->header->width; x++) {
//             struct pixel original_pixel = image->data[y * image->header->width + x];
//             struct pixel extracted_pixel = extract_color(&original_pixel, colors_to_keep);
//             extracted_image->data[y * image->header->width + x] = extracted_pixel;
//         }
//     }

//     return extracted_image;
// }
