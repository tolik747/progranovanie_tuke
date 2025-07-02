#include <stdio.h>
#include "command.h"
#include <stdlib.h>
#include<string.h>

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){

    if (name == NULL || description == NULL || *name == '\0' || *description == '\0') {
        return NULL;
    }

    struct command* nez = (struct command*)calloc(1, sizeof(struct command));
    if (nez == NULL) {
        return NULL;
    }

    nez->name = (char*)calloc(strlen(name) + 1, sizeof(char));
    nez->description = (char*)calloc(strlen(description) + 1, sizeof(char));
    if (nez->description == NULL || nez->name == NULL) {
        free(nez->name);
        free(nez->description);
        free(nez);
        return NULL;
    }

    strcpy(nez->name, name);
    strcpy(nez->description, description);

    return nez;
}
struct command* destroy_command(struct command* command){
    if(command==NULL){
        return NULL;
    }
    if(command!=NULL){
        free(command->description);
        free(command->name);
    }
    free(command);
    return NULL;
}