#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct Perfume {
    int codigo_de_perfume;
    char nombre_de_perfume[50];
    float precio;
    int num_de_unidades;
}perfu;

void capturar();
void mostrar();
void consultar();

FILE* arch;
char filename[] = "perfumes.txt";

int main() 
{
    capturar();
    mostrar();
    consultar();
    system("pause");
    return 0;
}

void capturar() {
    printf("Capturar perfume\n");
    if ((arch = fopen(filename, "a+")) != NULL) {
        struct Perfume perfume;
        printf("codigo de perfume: ");
        scanf("%d", &perfume.codigo_de_perfume);
        printf("Nombre de perfume: ");
        fflush(stdin);
        scanf("%s", perfume.nombre_de_perfume);
        printf("Precio: ");
        scanf("%f", &perfume.precio);
        printf("N�mero de unidades: ");
        scanf("%d", &perfume.num_de_unidades);

        fprintf(arch, "%d\t%s\t%.2f\t%d\n", perfume.codigo_de_perfume, perfume.nombre_de_perfume, perfume.precio, perfume.num_de_unidades);
        fclose(arch);
    } else {
        printf("No se puede abrir el archivo\n");
    }
}

void mostrar() {
    system("cls");
    printf("Leyendo archivo de perfumes...\n");
    if ((arch = fopen(filename, "r")) != NULL) {
        struct Perfume perfume;
        while (!feof(arch)) {
            fscanf(arch, "%d\t%s\t%f\t%d\n", &perfume.codigo_de_perfume, perfume.nombre_de_perfume, &perfume.precio, &perfume.num_de_unidades);
            printf("C�digo: %d, Nombre: %s, Precio: %.2f, Unidades: %d\n", perfume.codigo_de_perfume, perfume.nombre_de_perfume, perfume.precio, perfume.num_de_unidades);
        }
        fclose(arch);
    } else {
        printf("No se puede abrir el archivo\n");
    }
}

void consultar() {
    char nombre[50];
    int encontrado = 0;
    printf("Consultar perfume\n");
    printf("Nombre a buscar: ");
    fflush(stdin);
    scanf("%s", nombre);

    if ((arch = fopen(filename, "r")) != NULL) {
        struct Perfume perfume;
        while (!feof(arch)) {
            fscanf(arch, "%d\t%s\t%f\t%d\n", &perfume.codigo_de_perfume, perfume.nombre_de_perfume, &perfume.precio, &perfume.num_de_unidades);
            if (strcmp(nombre, perfume.nombre_de_perfume) == 0) {
                printf("C�digo: %d, Nombre: %s, Precio: %.2f, Unidades: %d\n", perfume.codigo_de_perfume, perfume.nombre_de_perfume, perfume.precio, perfume.num_de_unidades);
                encontrado = 1;
            }
        }
        fclose(arch);
    } else {
        printf("No se puede abrir el archivo\n");
    }

    if (!encontrado) {
        printf("Nombre no encontrado\n");
    }
}


