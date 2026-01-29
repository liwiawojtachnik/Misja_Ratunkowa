#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tests.h"
#include "map.h"

void assert_test(const char* test_name, int condition) {
    if (condition) {
        printf("[ OK ] %s\n", test_name);
    } else {
        printf("[FAIL] %s\n", test_name);
    }
}

void run_all_tests() {
    printf("--- Rozpoczynam Testy Jednostkowe ---\n");

    FILE *f = fopen("temp_test_map.txt", "w");
    if (f) {
        fprintf(f, "2 2\n1.0 2.0\n3.0 4.0\n");
        fclose(f);
    }

    Map *map = load_map("temp_test_map.txt");
    assert_test("Wczytanie mapy z pliku", map != NULL);

    if (map) {
        
        assert_test("Poprawne wymiary (2x2)", map->width == 2 && map->height == 2);

        double val = get_map_value(map, 1, 1);
        assert_test("Wartosc w punkcie (1,1) == 4.0", fabs(val - 4.0) < 0.001);

        double out_of_bounds = get_map_value(map, 5, 5);
        assert_test("Wyjscie poza zakres zwraca kare (-10000)", out_of_bounds == -10000.0);

        double negative_coords = get_map_value(map, -1, 0);
        assert_test("Ujemne wspolrzedne zwracaja kare", negative_coords == -10000.0);

        free_map(map);
    } else {
        printf("[FAIL] Nie udalo sie stworzyc mapy do testow.\n");
    }

    remove("temp_test_map.txt");

    printf("--- Koniec Testow ---\n");
}