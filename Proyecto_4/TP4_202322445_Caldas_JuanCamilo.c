//Entrega Grupo 6

//Integrantes:
//Tomas Uribe Carrasco
//202321557
//t.uribe11@uniandes.edu.co

//Juan David Calderon
//jd.calderong12@uniandes.edu.co
//202320117

//Juan Camilo Caldas
//jc.caldas23@uniandes.edu.co
//202322445

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void intercambiarBits(unsigned char *vectorBytes, int indiceBit1, int indiceBit2) {
    int byte1, posBit1, byte2, posBit2, valorBit1, valorBit2;

    // Calcular byte1 y posBit1
    __asm {
        MOV EAX, indiceBit1
        MOV ECX, 8
        XOR EDX, EDX
        DIV ECX
        MOV byte1, EAX
        MOV posBit1, EDX
    }
   
    // Calcular byte2 y posBit2
    __asm {
        MOV EAX, indiceBit2
        MOV ECX, 8
        XOR EDX, EDX
        DIV ECX
        MOV byte2, EAX
        MOV posBit2, EDX
    }
   
    // Obtener valorBit1
    __asm {
        MOV EAX, posBit1
        MOV ECX, byte1
        MOV EDX, vectorBytes
        ADD ECX, EDX
        MOV BL, [ECX]  // Cargar el byte correspondiente con indexación de la linea anterior
        MOV ECX, 7
        SUB ECX, EAX
        SHR BL, CL
        AND BL, 1
        MOVZX EAX, BL
        MOV valorBit1, EAX
    }
   
    // Obtener valorBit2
    __asm {
        MOV EAX, posBit2
        MOV ECX, byte2
        MOV EDX, vectorBytes
        ADD ECX, EDX
        MOV BL, [ECX]  // Cargar el byte correspondiente con indexación de la linea anterior
        MOV ECX, 7
        SUB ECX, EAX
        SHR BL, CL
        AND BL, 1
        MOVZX EAX, BL
        MOV valorBit2, EAX
    }
   
   
       
    __asm {
		// Comparación if (valorBit1 != valorBit2)
		MOV EAX, valorBit1
		CMP EAX, valorBit2
		JE end_if
           
		// Cambiar el bit en byte1
        MOV EAX, posBit1
        MOV ECX, byte1
        MOV EDX, vectorBytes
        ADD EDX, ECX
        MOV BL, [EDX]  // Cargar el byte correspondiente con indexación
        MOV ECX, 7
        SUB ECX, EAX
        MOV AL, 1
        SHL AL, CL
        XOR [EDX], AL  // Modificar el byte con el bit intercambiado
       
		// Cambiar el bit en byte2
        MOV EAX, posBit2
        MOV ECX, byte2
        MOV EDX, vectorBytes
        ADD EDX, ECX
        MOV BL, [EDX]  // Cargar el byte correspondiente con indexación
        MOV ECX, 7
        SUB ECX, EAX
        MOV AL, 1
        SHL AL, CL
        XOR [EDX], AL  // Modificar el byte con el bit intercambiado
		end_if:
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
