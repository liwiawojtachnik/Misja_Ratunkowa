#ifndef PSO_H
#define PSO_H

#include "map.h"

typedef struct {
    double x, y;          
    double vx, vy;        
    double pBest_x, pBest_y; 
    double pBest_val;    
    double current_val;   
} Particle;

typedef struct {
    Particle *particles;  
    int size;             
    double gBest_x, gBest_y; 
    double gBest_val;     
    
    double w;  
    double c1; 
    double c2; 
} Swarm;

Swarm* init_swarm(int size, Map *map, double w, double c1, double c2);
void update_swarm(Swarm *swarm, Map *map);
void free_swarm(Swarm *swarm);

#endif
