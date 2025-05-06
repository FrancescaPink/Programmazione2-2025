#include <math.h>

int main() {
    // Si tenti di interpretare le espressioni e si verifichi la correttezza delle aspettative con il debugger
	float a = 3 * 2 - 1;
	float b = 7 / 2 * 2;
	float c = 7 / 2.0 * 2;
	float d = 7 / 2 * 2.0;
	float e = 13 % 2 == 1;
	float f = 1 <= 3 && 2 <= 4;
    // Qualche esempio da evitare
	float g = 2 <= 3 <= 4;
	float h = (2 != 3) * 4;
	float i = 1 < 3 == 2 < 4;
    return 0;
}