#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bmp.h"


struct bmp_header* read_bmp_header(FILE *stream)
{
    if(stream==NULL || stream == stdin){
        return NULL;
    }
    struct bmp_header* hader = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    if (hader == NULL) {
        return NULL;
    }
    fseek(stream,0,SEEK_SET);
    fread(hader,sizeof(struct bmp_header),1,stream);
    return hader;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header)
{
     if (stream == NULL || header == NULL) {
        return NULL;
    }
    fseek(stream, header->offset, SEEK_SET);
    struct pixel* data = (struct pixel*)malloc(header->width * header->height * sizeof(struct pixel));
    if (data == NULL) {
        return NULL;
    }
    int padding = (4 - (header->width * 3) % 4) % 4;
    for (int i = 0; i < header->height; i++) {
            fread(&data[i * header->width],header->width * sizeof(struct pixel), 1, stream);
            fseek(stream, padding, SEEK_CUR);
    }
    return data;

}

struct bmp_image* read_bmp(FILE* stream)
{
     if (stream == NULL) {
        return NULL;
    }
    struct bmp_image* scan_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
    scan_image->header = read_bmp_header(stream);
    if(scan_image->header==NULL){
        fprintf(stderr, "Error: This is not a BMP file.\n");
        free_bmp_image(scan_image);
        return NULL;

    }
    if(scan_image->header->type!=0x4D42){
        fprintf(stderr, "Error: This is not a BMP file.\n");
        free_bmp_image(scan_image);
        return NULL;   
    }
    scan_image->data = read_data(stream,scan_image->header);
    if(scan_image->data == NULL){
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        free_bmp_image(scan_image);
        return NULL;
    }
    return scan_image;
    
}
bool write_bmp(FILE* stream, const struct bmp_image* image) {
    if (stream == NULL || image == NULL) {
        return false;
    }

    if (fwrite(image->header, sizeof(struct bmp_header), 1, stream) != 1) {
        return false;
    }

    size_t pixels_written = fwrite(image->data, sizeof(struct pixel), image->header->width * image->header->height, stream);
    if (pixels_written != image->header->width * image->header->height) {
        return false;
    }

    return true;
}
void free_bmp_image(struct bmp_image* image)
{
    if (image == NULL) {
        return;
    }
    if (image->header != NULL) {
        free(image->header);
    }
    if (image->data != NULL) {
        free(image->data);
    }
    free(image);
}
