typedef enum Case_type {
    CASE_DIRT,
    CASE_ROCK,
    CASE_SAND,
    CASE_WATER,
    CASE_GRASS,
    CASE_IDK1,
    CASE_IDK2,
    CASE_IDK3,
    CASE_IDK4,
    CASE_IDK5,
    
    CASE_AMOUNT
} Case_type;

#define EPSILON 2

int abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

// give a pseudo random sign depending on the given value
int random_sign(int start) {
    if (start < EPSILON) {
        return 1;
    }
    if (start > CASE_AMOUNT - EPSILON) {
        return -1;
    }
    return rand() % 2 ? 1 : -1;
}

void clamp(int min, int max, int *num) {
    if (*num < min) {
        *num = min;
        return;
    }
    if (*num > max) {
        *num = max;
        return;
    }
}

// fonction générant la carte aléatoirement
int map_generator(int **map) {
    // on vérifie que le pointeur n'est pas nul pour être sûr qu'il n'y ai pas de segmentation fault
    if (map == NULL) {
        return false;
    }

    int min, max;

    // generation aléatoire
    for (int y = 0; y < SIZE_MAP; y++) {
        for (int x = 0; x < SIZE_MAP; x++) {
            if (x == 0 && y == 0) {
                // no case before
                map[y][x] = rand() % CASE_AMOUNT;

            } else if (y == 0) {
                // no case before, on top
                map[y][x] = map[y][x - 1] + random_sign(map[y][x - 1]) * (rand() % EPSILON);

            } else if (x == 0) {
                // no case before, same line
                map[y][x] = map[y - 1][x] + random_sign(map[y - 1][x]) * (rand() % EPSILON);

            } else {
                // ase before, same line and on top
                // it's not possible to find +/- epislon value that fit our goal
                if (abs(map[y - 1][x] - map[y][x - 1]) > EPSILON) {
                    map[y][x] = (map[y - 1][x] + map[y][x - 1]) / 2;

                } else {
                    // here it can, so we take the min value and add rand()%espilon
                    if (map[y - 1][x] > map[y][x - 1]) {
                        min = map[y][x - 1];
                        max = map[y - 1][x];
                    } else {
                        min = map[y - 1][x];
                        max = map[y][x - 1];
                    }

                    if (max == min) {
                        map[y][x] = map[y - 1][x] + (rand() % 2 ? 1 : -1) * (rand() % EPSILON);
                    } else {
                        // choose randomly where to apply epsilon
                        if (rand() % 2) {
                            map[y][x] = max - rand() % EPSILON;
                        } else {
                            map[y][x] = min + rand() % EPSILON;
                        }
                    }
                }
            }

            // bound our numbers
            clamp(0, CASE_AMOUNT, &map[y][x]);

            // affichage
            printf("%d ", map[y][x]);
        }
        printf("\n");
    }
    return true;
}
