#include "map.h"
#include <stdio.h>
#include <stdlib.h>

Map* load_map(const char *filename){    //wczytuje mape i zwraca wskaznik na strukture Map(zdefiniowana w map.h)
    FILE *f = fopen(filename, "r");
    if (f == NULL){
        fprintf(stderr, "Blad: nie mozna odczytac pliku: %s\n", filename);
        return NULL;
    }
    Map *map = malloc(sizeof(Map));
    if (map == NULL){
        fclose(f);
        return NULL;
    }
    if (fscanf(f, "%d %d", &map->width, &map->height) != 2){
        fprintf(stderr, "Blad: nieprawidlowy format naglowka mapy.\n");
        free(map);
        fclose(f);
        return NULL;
    }
    map->values = malloc(map->height * sizeof(double*));
    if (map->values == NULL){
        free(map);
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < map->height; i++){
        map->values[i] = malloc(map->width * sizeof(double));
        for (int j = 0; j < map->width; j++){
            if (fscanf(f, "%lf", &map->values[i][j]) != 1){
                for (int k = 0; k <= i; k++){
                    free(map->values[k]);
                }
                free(map->values);
                free(map);
                return NULL;
            }
        }
    }
    fclose(f);
    return map;
}
double get_map_value(Map *map, double x, double y){
    int col = (int)x;
    int row = (int)y;

    if (col < 0 || col >= map->width || row < 0 || row >= map->height){
        return -10000.0; //zawracamy drona, jezeli wyleci poza mape
    }
    return map->values[row][col];
}
void free_map(Map *map){    //zwalnianie miejsca
    if (map == NULL ){
        return;
    }
    for (int i = 0; i < map->height; i++){
        free(map->values[i]);
    }
    free(map->values);
    free(map);
}

