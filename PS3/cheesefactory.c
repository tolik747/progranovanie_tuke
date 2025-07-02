#include <stdlib.h>
#include <stdio.h>

struct cheese_hole {
    int radius;
    int x_coord;
    int y_coord;
    int z_coord;
};
typedef struct cheese_hole CheeseHole;

double calculate_fx(CheeseHole **holes, int num_holes, int num_slices, double z2, const double cube_size);

double calculate_volume_all(CheeseHole **holes, int num_holes, const double cube_size);

double calculate_volume_segment(double radius, double a, double b, const double pi);

void free_cheese_holes(CheeseHole **holes, int num_holes);

int main(void) {
    int num_holes, num_slices;
    scanf("%d%d", &num_holes, &num_slices);
    while (getchar() != '\n');

    if (num_holes < 0 || num_holes > 1e4 || num_slices < 1 || num_slices > 100) {
        return 0;
    }

    CheeseHole **holes = NULL;
    if (num_holes > 0) {
        holes = (CheeseHole **)calloc(num_holes, sizeof(CheeseHole *));
        for (int i = 0; i < num_holes; i++) {
            holes[i] = (CheeseHole *)calloc(1, sizeof(CheeseHole));
            scanf("%d %d %d %d", &holes[i]->radius, &holes[i]->x_coord, &holes[i]->y_coord, &holes[i]->z_coord);
            while (getchar() != '\n');
            if (holes[i]->radius < 0 || holes[i]->radius > 1e5 ||
                holes[i]->x_coord < 0 || holes[i]->x_coord > 1e5 ||
                holes[i]->y_coord < 0 || holes[i]->y_coord > 1e5 ||
                holes[i]->z_coord < 0 || holes[i]->z_coord > 1e5) {
                return 0;
            }
        }
    }

    double *slice_volumes;
    const double EPSILON = 1e-8;
    const double CUBE_SIZE = 1e5;
    slice_volumes = (double*)calloc(num_slices, sizeof(double));
    double total_volume;
    double slice_volume;
    total_volume = calculate_volume_all(holes, num_holes, CUBE_SIZE);
    slice_volume = total_volume / (double)num_slices;
    double a;
    double b;
    double x;
    double tmp = 0.;
    for (int i = 0; i < num_slices; i++) {
        x = tmp + CUBE_SIZE / num_slices;
        if (num_holes) {
            a = 0.;
            b = CUBE_SIZE;
            for (;;) {
                if (b - a < EPSILON) break;
                x = (a + b) / 2.;
                if (calculate_fx(holes, num_holes, num_slices, x, CUBE_SIZE) > slice_volume * (double)(i + 1)) {
                    b = x;
                } else {
                    a = x;
                }
            }
        }
        slice_volumes[i] = x - tmp;
        tmp += slice_volumes[i];
        slice_volumes[i] *= 1e-3;
    }

    for (int i = 0; i < num_slices; i++) {
        printf("%.9lf\n", slice_volumes[i]);
    }

    free(slice_volumes);
    free_cheese_holes(holes, num_holes);
    return 0;
}

double calculate_fx(CheeseHole **holes, int num_holes, int num_slices, double z2, const double cube_size) {
    const double PI = 3.14159265358979323846;
    if (holes) {
        double slice_volume;
        double segment_volume;
        double a;
        double b;
        double z1 = 0.;
        double z3;
        double h;
        double c = z2 - z1;
        slice_volume = cube_size * cube_size * c;

        segment_volume = 0.;
        for (int i = 0; i < num_holes; i++) {
            z3 = holes[i]->z_coord - holes[i]->radius;
            h = z2 - z3;
            if (h > 0) {
                if (h > 2. * holes[i]->radius) {
                    a = holes[i]->radius;
                } else if (h >= holes[i]->radius) {
                    a = h - holes[i]->radius;
                } else {
                    a = -(holes[i]->radius - h);
                }
                if (z3 < z1) {
                    b = -holes[i]->radius - z3;
                } else {
                    b = -holes[i]->radius;
                }
                segment_volume += calculate_volume_segment(holes[i]->radius, a, b, PI);
            }
        }
        return slice_volume - segment_volume;
    }
    return 0.;
}

double calculate_volume_all(CheeseHole **holes, int num_holes, const double cube_size) {
    const double PI = 3.14159265358979323846;
    double volume = cube_size * cube_size * cube_size;
    
    int i = 0;
    while (i < num_holes) {
        volume -= 4. / 3. * PI * holes[i]->radius * holes[i]->radius * holes[i]->radius;
        i++;
    }
    
    return volume;
}

double calculate_volume_segment(double radius, double a, double b, const double pi) {
    if (radius < 0) 
    {
        return 0;
    }

    double volume = 0;
    double abs_a = a < 0 ? -a : a;
    double abs_b = b < 0 ? -b : b;

    if (abs_a <= 2 * radius && abs_b <= 2 * radius) {
        volume = pi * (radius * radius * (a - b) - 1. / 3. * (a * a * a - b * b * b));
    }
    return volume;
}

void free_cheese_holes(CheeseHole **holes, int num_holes) {
    if (holes == NULL) {
        return;
    }
    
    int i = 0;
    while (i < num_holes) {
        free(holes[i]);
        i++;
    }
    free(holes);
}
