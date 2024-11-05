#include <stdio.h>

struct Bus
{
    int anchoBanda;
    float cicloBus;
    float frecReloj;
    float velTransferencia;   
} busParalelo;

double calcularVelTransferencia(struct Bus bus)
{
    return busParalelo.anchoBanda * busParalelo.cicloBus * busParalelo.frecReloj;
};

int main()
{
    printf("\nCalculadora de velocidad de transferencia de un bus paralelo\n");
    printf("\n-------------------------------------\n");
    printf("\nPor favor ingrese los siguientes datos para el calculo:\n");
    printf("\nAncho de banda del bus: ");
    scanf("%d", &busParalelo.anchoBanda);
    printf("Ciclos de bus: ");
    scanf("%d", &busParalelo.cicloBus);
    printf("Frecuencia de reloj: ");
    scanf("%d", &busParalelo.frecReloj);
    busParalelo.velTransferencia = calcularVelTransferencia(busParalelo);
    printf("\nLa velocidad de transferencia del bus es:\n%f bits/s", busParalelo.velTransferencia);
}