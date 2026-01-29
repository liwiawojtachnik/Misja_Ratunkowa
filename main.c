#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "map.h"
#include "pso.h"
#include "logger.h"
#include "tests.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--test") == 0) {
            run_all_tests();
            return 0; 
        }
    }

    char *map_file = NULL;
    int particles_count = 30;
    int iterations = 100;
    char *config_file = NULL;
    int log_interval = 0;

    double w = 0.5;
    double c1 = 1.0;
    double c2 = 1.0;

    if (argc < 2) {
        printf("Uzycie: %s <plik_mapy> [-p n] [-i n] [-c config] [-n n]\n", argv[0]);
        return 1;
    }
    
    map_file = argv[1]; 

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            particles_count = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            iterations = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            config_file = argv[++i];
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            log_interval = atoi(argv[++i]);
        }
    }

    if (config_file) {
        FILE *cfg = fopen(config_file, "r");
        if (cfg) {
            fscanf(cfg, "%lf %lf %lf", &w, &c1, &c2);
            fclose(cfg);
            printf("Wczytano konfiguracje: w=%.2f, c1=%.2f, c2=%.2f\n", w, c1, c2);
        } else {
            printf("Nie udalo sie otworzyc pliku config, uzywam domyslnych.\n");
        }
    }

    printf("--- Start Symulacji ---\n");
    printf("Mapa: %s\nCzastek: %d\nIteracji: %d\n", map_file, particles_count, iterations);

    Map *map = load_map(map_file);
    if (!map) return 1;

    Swarm *swarm = init_swarm(particles_count, map, w, c1, c2);
    if (!swarm) { 
        free_map(map); 
        return 1; 
    }

    if (log_interval > 0) {
        FILE *f = fopen("results.csv", "w");
        if (f) {
            fprintf(f, "iteracja,id,x,y,wartosc\n"); 
            fclose(f);
        }
    }

    for (int i = 0; i < iterations; i++) {
        update_swarm(swarm, map);
        
        if (log_interval > 0 && (i % log_interval == 0)) {
            save_swarm_to_csv(swarm, i, "results.csv");
        }

        if (i % (iterations / 10 + 1) == 0) {
           
        }
    }

    printf("\n--- Wyniki ---\n");
    printf("Znalezione maksimum: %.4f\n", swarm->gBest_val);
    printf("Wspolrzedne: (x=%.2f, y=%.2f)\n", swarm->gBest_x, swarm->gBest_y);

    free_swarm(swarm);
    free_map(map);

    return 0;
}
