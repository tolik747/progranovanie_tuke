#include "hof.h"
#include <stdio.h>
#include <stdlib.h>



struct player* sort(const struct player list[], const int size);
void insertion_sort(struct player* list, const int size);


int load(struct player list[]) {
    FILE *fp = fopen("score", "r");
    if (fp == NULL)
    {
        return -1;
    }
    int count = 0;
    int df=0;
    for ( count = 0; count < 10; count++) {
        df++;
        if (fscanf(fp, "%29s", list[count].name) != 1 || fscanf(fp, "%d", &list[count].score) != 1) {
           
            break;
        }
    }
    df--;
    struct player* point = sort(list, count);
    for (int i = 0; i < count; i++)
    {
        list[i] = point[i];
    }
    free(point);
    fclose(fp);
    return df;
}


struct player* sort(const struct player list[], const int size)
{
    struct player* tmp_list = (struct player*)calloc((unsigned int)size, sizeof(struct player));
    if (tmp_list == NULL) {
        return NULL; // Check for successful memory allocation
    }
    for (int i = 0; i < size; i++) {
        tmp_list[i] = list[i];
    }

    insertion_sort(tmp_list, size);

    return tmp_list;
}

void insertion_sort(struct player* list, const int size)
{
    for (int i = 1; i < size; i++)
    {
        struct player key = list[i];
        int j = i - 1;
        while (j >= 0 && list[j].score < key.score) // Змінено < на >
        {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}
bool save(const struct player list[], const int size) {
   
    struct player* point = sort(list,size);
    FILE *vas=fopen("score","w");
    if(vas==NULL) {
        return false;
    }
    for(int g=0; g<size; g++) {
        fprintf(vas,"%s ",point[g].name);
        fprintf(vas,"%d\n",point[g].score);
    }
    free(point); // Free allocated memory after usage
    fclose(vas);
    return true;
}
 bool add_player(struct player list[], int* size, const struct player player)
{
   if (!list || !size || !player.name || *size < 0 || *size > 10)
        return false;

    // Якщо список порожній, просто додати гравця на початок
    if (*size == 0) {
        list[0] = player;
        (*size)++;
        return true;
    }

    // Пошук місця для вставки нового гравця
    int index_to_insert = -1;
    for (int i = 0; i < *size; i++) {
        if (player.score >= list[i].score) {
            index_to_insert = i;
            break;
        }
    }

    // Якщо місце для вставки не знайдено, але список не заповнений
    if (index_to_insert == -1 && *size < 10) {
        list[*size] = player;
        (*size)++;
        return true;
    }

    // Вставка нового гравця в потрібне місце
    if (index_to_insert != -1) {
        // Зсунути існуючих гравців вниз
        for (int j = *size - 1; j > index_to_insert; j--) {
            list[j] = list[j - 1];
        }
        list[index_to_insert] = player;

        // Оновити розмір списку, якщо не досягнуто максимуму
        if (*size < 10) {
            (*size)++;
        }
        return true;
    }

    return false; // Якщо не вдалося вставити гравця
}






// #include<stdio.h>
// #include"hof.h"
// #include<stdlib.h>
// #include<string.h>

// void sort_player(struct player list[], int left, int right)
// {
//     int i=left;
//     int j=right;
//     int pivot=list[(left+right)/2].score;
//     struct player rt;
//     while (i<=j)
//     {
//         while (list[i].score>pivot)
//         {
//             i++;
//         }
//         while (list[j].score<pivot)
//         {
//             j--;
//         }
//         if(i<=j)
//         {
//             rt=list[i];
//             list[i]=list[j];
//             list[j]=rt;
//             i++;
//             j--;

//         }
//     }
//     if(left<j)
//     {
//         sort_player(list,left,j);
//     }
//     if(i<right)
//     {
//         sort_player(list,i,right);
//     }
// }
// int load(struct player list[])
// {
//     FILE *sor=fopen("score","r");

//     if(sor==NULL)
//     {
//         return -1;
//     }
//     int rah=0;
//     while(!feof(sor)&&rah<10)
//     {
//         if(fscanf(sor,"%29s %d",list[rah].name,&list[rah].score)!=EOF)
//         {
//            if(list[rah].name[0]!='\0')
//            {
//                 rah++;
//            }
//         }
//     }
    
//     fclose(sor);
//     if(rah>0)
//     {
//         sort_player(list,0,rah-1);
//     }
//     return rah;
// }

// int sort_playe(const void *one,const void *two)
// {
//     const struct player *player_one=(const struct player *)one;
//     const struct player *player_two=(const struct player *)two;
//      if (player_one->score < player_two->score) {
//         return 1;
//     } else if (player_one->score > player_two->score) {
//         return -1;
//     } else {
//         return 0;
//     }
    
// }

// bool save(const struct player list[],const int size)
// {
//     qsort((void*)list,(size_t)size,sizeof(struct player),sort_playe);
//     FILE *arena=fopen("score","w");

//     if(arena==NULL)
//     {
//         return false;
//     }
//     for(int i=0;i<size;i++)
//     {
//         fprintf(arena,"%s ",list[i].name);
//         fprintf(arena,"%d\n",list[i].score);
//     }
//     fclose(arena);
//     return true;
// }

// bool is_valid_parameters(struct player list[], int* size, const struct player player) {
//     return (list && size && player.name && (*size) >= 0 && (*size) <= 10);
// }

// void shift_players(struct player list[], int size, int index) {
//     for (int j = size - 1; j > index; j--) {
//         list[j] = list[j - 1];
//     }
// }

// bool add_player(struct player list[], int* size, const struct player player) {
//     if (!is_valid_parameters(list, size, player)) {
//         return false;
//     }

//      if (*size == 0) {
//         list[0] = player;
//         (*size)++;
//         return true;
//     }

//     int i=0;
//     while(i<*size&&player.score<list[i].score)
//     {
//         i++;
//     }
//     if(i<10||player.score>list[10-1].score)
//     {
//         if(*size<10)
//         {
//             (*size)++;
//         }
//         shift_players(list,*size,i);
//         list[i]=player;
//         if(*size>10)
//         {
//             *size=10;
//         }
//         return true;
//     }

    
//     return false;
// }