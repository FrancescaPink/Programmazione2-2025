// C program to calculate the Riemann sum of a zeta function

#include <stdio.h>
#include <math.h>

int main () {
    double z = 0, zold;
    int s = 2, n = 1;
    do {
        zold = z;                   // Saving the old value of z
        z += 1.0 / pow(n, s);       // Update z
        n++;                        // Update n
    } while (fabs(z - zold) > 1e-6);
    printf("z(%d) = %lf\n", s, z);
}
