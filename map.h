#ifndef MAP_H
#define MAP_H

typedef struct {
    int width;  
    int height;
    double **values;
} Map;

Map* load_map (const char *filename);

double get_map_value(Map *map, double x, double y);

void free_map(Map *map);

#endif