// C program to convert Celsius to Fahrenheit using the formula: f = 32 + c * 9/5
#include <stdio.h>

int main() {
    float c = 18;
    /* Vale l'uguaglianza: c * 9/5 = f – 32 */
    float f = 32 + c * 9/ 5.0;
    printf("Celsius: %.2f\n", c);
}