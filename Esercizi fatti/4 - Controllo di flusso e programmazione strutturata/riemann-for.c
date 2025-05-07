// C program to calculate the Riemann sum of a zeta function with a for loop

#include <stdio.h>
#include <math.h>

int main () {
    double z = 0, zold;
    int s = 2, n = 1;
    for (n = 1; n < 1000; n++) {                // Looping through n
        zold = z;                               // Saving the old value of z
        z += 1.0 / pow(n, s);                   // Update z
        if (fabs(z - zold) <= 1e-6) break;      // Break if the difference is small enough
    }
    printf("z(%d) = %lf\n", s, z);
}
