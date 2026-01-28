#include "pso.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>

Swarm* init_swarm(int size, Map *map, double w, double c1, double c2) {
    Swarm *swarm = malloc(sizeof(Swarm));
    swarm->particles = malloc(size * sizeof(Particle));
    swarm->size = size;
    swarm->w = w;
    swarm->c1 = c1;
    swarm->c2 = c2;

    swarm->gBest_val = -DBL_MAX; 
    swarm->gBest_x = 0;
    swarm->gBest_y = 0;

    for (int i = 0; i < size; i++) {
        swarm->particles[i].x = random_double(0, map->width - 1);
        swarm->particles[i].y = random_double(0, map->height - 1);
        
        swarm->particles[i].vx = random_double(-1.0, 1.0);
        swarm->particles[i].vy = random_double(-1.0, 1.0);

        double val = get_map_value(map, swarm->particles[i].x, swarm->particles[i].y);
        swarm->particles[i].current_val = val;

        swarm->particles[i].pBest_x = swarm->particles[i].x;
        swarm->particles[i].pBest_y = swarm->particles[i].y;
        swarm->particles[i].pBest_val = val;

        if (val > swarm->gBest_val) {
            swarm->gBest_val = val;
            swarm->gBest_x = swarm->particles[i].x;
            swarm->gBest_y = swarm->particles[i].y;
        }
    }

    return swarm;
}

void update_swarm(Swarm *swarm, Map *map) {
    for (int i = 0; i < swarm->size; i++) {
        Particle *p = &swarm->particles[i];

        double r1 = random_double(0.0, 1.0);
        double r2 = random_double(0.0, 1.0);

        // v(t+1) = w*v + c1*r1*(pBest - x) + c2*r2*(gBest - x)
        p->vx = swarm->w * p->vx 
              + swarm->c1 * r1 * (p->pBest_x - p->x) 
              + swarm->c2 * r2 * (swarm->gBest_x - p->x);
        
        p->vy = swarm->w * p->vy 
              + swarm->c1 * r1 * (p->pBest_y - p->y) 
              + swarm->c2 * r2 * (swarm->gBest_y - p->y);

        //  x(t+1) = x(t) + v(t+1)
        p->x = p->x + p->vx;
        p->y = p->y + p->vy;

        double current_val = get_map_value(map, p->x, p->y);
        p->current_val = current_val;

        if (current_val > p->pBest_val) {
            p->pBest_val = current_val;
            p->pBest_x = p->x;
            p->pBest_y = p->y;
        }

        if (current_val > swarm->gBest_val) {
            swarm->gBest_val = current_val;
            swarm->gBest_x = p->x;
            swarm->gBest_y = p->y;
        }
    }
}

void free_swarm(Swarm *swarm) {
    if (swarm) {
        free(swarm->particles);
        free(swarm);
    }
}
