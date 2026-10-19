#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[50];
    float precio;
    int anio_salida;
    int duracion_estimada;
    char gama[50];
} Componente;

void capturar(FILE *archivo) {
    Componente componente;

    printf("Nombre: ");
    fflush(stdin);
    gets(componente.nombre);
    printf("Precio: ");
    scanf("%f", &componente.precio);
    printf("A�o de salida: ");
    scanf("%d", &componente.anio_salida);
    printf("Duraci�n estimada (en a�os): ");
    scanf("%d", &componente.duracion_estimada);
    printf("Gama: ");
    fflush(stdin);
    gets(componente.gama);

    fwrite(&componente, sizeof(Componente), 1, archivo);
}

void listado(FILE *archivo) {
    Componente componente;
    rewind(archivo);

    while (fread(&componente, sizeof(Componente), 1, archivo)) {
        printf("Nombre: %s, Precio: %.2f, A�o de salida: %d, Duraci�n estimada: %d, Gama: %s\n",
               componente.nombre, componente.precio, componente.anio_salida, componente.duracion_estimada, componente.gama);
    }
}

void consulta(FILE *archivo, const char *nombre_buscar) {
    Componente componente;
    int encontrado = 0;
    rewind(archivo);

    while (fread(&componente, sizeof(Componente), 1, archivo)) {
        if (strcmp(componente.nombre, nombre_buscar) == 0) {
            printf("Nombre: %s, Precio: %.2f, A�o de salida: %d, Duraci�n estimada: %d, Gama: %s\n",
                   componente.nombre, componente.precio, componente.anio_salida, componente.duracion_estimada, componente.gama);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Componente no encontrado.\n");
    }
}

void modificar(FILE *archivo, const char *nombre_buscar) {
    Componente componente;
    int encontrado = 0;
    long posicion;
    rewind(archivo);

    while (fread(&componente, sizeof(Componente), 1, archivo)) {
        if (strcmp(componente.nombre, nombre_buscar) == 0) {
            printf("Modificar los datos de %s\n", componente.nombre);
            printf("Nuevo precio: ");
            scanf("%f", &componente.precio);
            printf("Nuevo producto: ");
            fflush(stdin);
            gets(componente.nombre);

            posicion = ftell(archivo) - sizeof(Componente);
            fseek(archivo, posicion, SEEK_SET);
            fwrite(&componente, sizeof(Componente), 1, archivo);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Componente no encontrado.\n");
    }
}

int main() {
    FILE *archivo;
    int opcion;
    char nombre_buscar[50];

    archivo = fopen("componentes.dat", "r+b");
    if (archivo == NULL) {
        archivo = fopen("componentes.dat", "w+b");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo.\n");
            return 1;
        }
    }

    do {
        printf("\nMen�:\n");
        printf("1. Capturar\n");
        printf("2. Listado\n");
        printf("3. Consulta\n");
        printf("4. Modificar\n");
        printf("5. Salir\n");
        printf("Seleccione una opci�n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                capturar(archivo);
                break;
            case 2:
                listado(archivo);
                break;
            case 3:
                printf("Ingrese el nombre del componente a consultar: ");
                fflush(stdin);
                gets(nombre_buscar);
                consulta(archivo, nombre_buscar);
                break;
            case 4:
                printf("Ingrese el nombre del componente a modificar: ");
                fflush(stdin);
                gets(nombre_buscar);
                modificar(archivo, nombre_buscar);
                break;
            case 5:
                fclose(archivo);
                printf("Saliendo...\n");
                break;
            default:
                printf("Opci�n no v�lida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    return 0;
}
