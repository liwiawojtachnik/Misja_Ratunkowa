#include "logger.h"
#include <stdio.h>

void save_swarm_to_csv(Swarm *swarm, int iteration, const char *filename) {
    FILE *f = fopen(filename, "a");
    if (!f) return;

    for (int i = 0; i < swarm->size; i++) {
        fprintf(f, "%d,%d,%.4f,%.4f,%.4f\n", 
                iteration, 
                i, 
                swarm->particles[i].x, 
                swarm->particles[i].y, 
                swarm->particles[i].current_val);
    }

    fclose(f);
}
