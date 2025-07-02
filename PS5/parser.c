#include<stdio.h>
#include"parser.h"
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h> 



void plus_comand(struct parser* parser, struct command* command) {
    struct container* new_command = create_container(parser->commands, COMMAND, command);

    if (parser->commands == NULL) {
        parser->commands = new_command;
    }
}
struct parser* create_parser(){
    struct parser* nieco=(struct parser*)calloc(1,sizeof(struct parser));
    int io=12;
    if(io==12){
        plus_comand(nieco, create_command("KONIEC", "Prikaz ukonci rozohratu hru. Nastavi prislusny stav hry.", "(KONIEC)", 1));
        plus_comand(nieco, create_command("SEVER", "Presun do miestnosti nachadzajucej sa na sever od aktualnej. Zmeni referenciu aktualnej miestnosti.", "(SEVER)", 1));
        plus_comand(nieco, create_command("JUH", "Presun do miestnosti nachadzajucej sa na juh od aktualnej. Zmeni referenciu aktualnej miestnosti.", "(JUH)", 1));
        plus_comand(nieco, create_command("VYCHOD", "Presun do miestnosti nachadzajucej sa na vychod od aktualnej. Zmeni referenciu aktualnej miestnosti.", "(VYCHOD)", 1));
        plus_comand(nieco, create_command("ZAPAD", "Presun do miestnosti nachadzajucej sa na zapad od aktualnej. Zmeni referenciu aktualnej miestnosti.", "(ZAPAD)", 1));
        plus_comand(nieco, create_command("ROZHLIADNI SA", "Prikaz vypise aktualne informacie o miestnosti, v ktorej sa hrac prave nachadza.", "(ROZHLIADNI SA)", 1));
        plus_comand(nieco, create_command("PRIKAZY", "Prikaz vypise na obrazovku zoznam vsetkych prikazov, ktore hra poskytuje.", "(PRIKAZY)", 1));
        plus_comand(nieco, create_command("VERZIA", "Prikaz zobrazi cislo verzie hry, lubovolny sprievodny text a meno a priezvisko autora s kontaktom (e-mailova adresa, webova stranka).", "(VERZIA)", 1));
        plus_comand(nieco, create_command("RESTART", "Znovu spusti hru od zaciatku. Zmeni stav hry na pozadovany.", "(RESTART)", 1));
        plus_comand(nieco, create_command("O HRE", "Prikaz zobrazi kratky text, ktory posluzi ako uvod do pribehu. Ako dobry zaciatok sa javi znamy text: Kde bolo tam bolo, ", "(O HRE)", 1));
        plus_comand(nieco, create_command("VEZMI", "Vlozi predmet z miestnosti do batohu. Prikaz ma jeden povinny parameter, ktorym je nazov predmetu. Ak predmet nebude zadany, program vypise na obrazovku vhodnu hlasku (napr. Neviem, co chces vziat.).", "(VEZMI)", 1));
        plus_comand(nieco, create_command("INVENTAR", "Zobrazi obsah hracovho batohu.", "(INVENTAR)", 1));
        plus_comand(nieco, create_command("PRESKUMAJ", "Vypise opis predmetu, ktory sa musi nachadzat v miestnosti alebo batohu. Prikaz ma jeden povinny parameter, ktorym je nazov predmetu. Ak predmet nebude zadany alebo sa nenajde v batohu alebo v miestnosti, program vypise na obrazovku vhodnu hlasku (napr. Neviem, co chces preskumat.).", "(PRESKUMAJ)", 1));
        plus_comand(nieco, create_command("POLOZ", "Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)", "(POLOZ)", 1));
        plus_comand(nieco, create_command("POUZI", "Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).", "(POUZI)", 1));
        plus_comand(nieco, create_command("NAHRAJ", "Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.", "(NAHRAJ)", 1));
        plus_comand(nieco, create_command("ULOZ", "Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.", "(ULOZ)", 1));
    }

    return nieco;
}
struct parser* destroy_parser(struct parser* parser){
    if(parser->commands!=NULL){
        destroy_containers(parser->commands);
    }
    if(parser->history!=NULL){
        destroy_containers(parser->history);
    }
    free(parser);
    return NULL;
}
struct command* parse_input(struct parser* parser, char* input){
    if(parser == NULL || input == NULL){
        return NULL;
    }
    
    size_t input_length = strlen(input);
    char* end = input + input_length - 1;
    
    while (isspace(*input)) {
        input++;
    }
    
    while ((end > input) && isspace(*end)) {
        *end-- = '\0';
    }
    
    char* trimmed_input = (char*)malloc(strlen(input) + 1);
    if (trimmed_input == NULL) {
        return NULL;
    }
    
    strcpy(trimmed_input, input);
    
    struct container* current_command = parser->commands;
    while (current_command != NULL) {
        struct command* cmd = (struct command*) current_command->command;
        if (strcasecmp(trimmed_input, cmd->name) == 0) {
            free(trimmed_input);
            return cmd;
        }
        current_command = current_command->next;
    }
    
    free(trimmed_input);
    return NULL;
}