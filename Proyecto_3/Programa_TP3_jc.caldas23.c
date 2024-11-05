#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Función para intercambiar dos bits específicos en un vector de bytes:
void intercambiarBits(unsigned char *vectorBytes, int indiceBit1, int indiceBit2) {

    // Determinar en qué byte y posición está cada bit:
    int byte1 = indiceBit1 / 8, posBit1 = indiceBit1 % 8;
    int byte2 = indiceBit2 / 8, posBit2 = indiceBit2 % 8;

    // Obtener los valores de los bits (0 o 1):
    int valorBit1 = (vectorBytes[byte1] >> (7 - posBit1)) & 1;
    int valorBit2 = (vectorBytes[byte2] >> (7 - posBit2)) & 1;

    // Intercambiar los bits si son diferentes:
    if (valorBit1 != valorBit2) {
        vectorBytes[byte1] ^= (1 << (7 - posBit1));  // Cambiar el bit en byte1
        vectorBytes[byte2] ^= (1 << (7 - posBit2));  // Cambiar el bit en byte2
    }
}

// Función para invertir una secuencia de bits en un vector de bytes:
void invertirSecuenciaBits(unsigned char *vectorBytes, int inicio, int fin) {

    // Continuar invirtiendo bits mientras el inicio sea menor que fin:
    while (inicio < fin) {
        intercambiarBits(vectorBytes, inicio, fin);  // Intercambiar los bits en las posiciones
        inicio++;
        fin--;
    }
}

int main() {

    // Variables para el tamaño del vector y el número de bits a rotar:
    int tamanioVector, bitsRotar;

    // Solicitar el tamaño del vector al usuario:
    printf("Ingrese el tamanio del vector (en numero de bytes): ");
    scanf("%d", &tamanioVector);

    // Validar que el tamaño sea mayor a cero:
    if (tamanioVector <= 0) {
        printf("El tamanio del vector debe ser mayor que 0.\n");
        return 1;
    }

    // Asignar memoria dinámica para el vector de bytes:
    unsigned char *vectorBytes = (unsigned char *)calloc(tamanioVector, sizeof(unsigned char));
    if (vectorBytes == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Solicitar los elementos del vector al usuario:
    printf("Ingrese los %d elementos del vector (en decimal):\n", tamanioVector);
    for (int i = 0; i < tamanioVector; i++) {
        int valorElemento;
        scanf("%d", &valorElemento);
        vectorBytes[i] = (unsigned char)valorElemento;  // Almacenar el valor ingresado en el vector
    }

    // Solicitar el número de bits a rotar:
    printf("Ingrese el numero de bits para rotar: ");
    scanf("%d", &bitsRotar);

    // Calcular el número total de bits en el vector y ajustar el número de rotaciones:
    int totalBits = 8 * tamanioVector;
    bitsRotar = bitsRotar % totalBits;

    // Realizar la rotación de bits utilizando la inversión de secuencia:
    invertirSecuenciaBits(vectorBytes, 0, totalBits - 1);            // Invertir todos los bits del vector
    invertirSecuenciaBits(vectorBytes, 0, totalBits - bitsRotar - 1);  // Invertir la primera parte
    invertirSecuenciaBits(vectorBytes, totalBits - bitsRotar, totalBits - 1);  // Invertir la segunda parte

    // Mostrar el resultado en formato hexadecimal:
    printf("Resultado en hexadecimal:\n");
    for (int i = 0; i < tamanioVector; i++) {
        printf("%02X", vectorBytes[i]);
    }
    printf("\n");

    // Liberar la memoria asignada al vector:
    free(vectorBytes);
    return 0;
}
