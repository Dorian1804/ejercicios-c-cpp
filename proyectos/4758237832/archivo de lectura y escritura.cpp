#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Alumno {
    char nombre_alumno[50];
    int matricula;
    char especialidad[50];
    float nota1, nota2, nota3;
};

void capturar();
void mostrar();
void consultar();

int main() {
    int opcion;
    do {
        printf("\nMen�:\n");
        printf("1. Capturar alumno\n");
        printf("2. Mostrar alumnos\n");
        printf("3. Consultar alumno\n");
        printf("4. Salir\n");
        printf("Ingrese una opci�n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                capturar();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                consultar();
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opci�n inv�lida. Intente nuevamente.\n");
        }
    } while (opcion != 4);

    return 0;
}

void capturar() {
    struct Alumno alumno;
    FILE *file = fopen("alumnos.txt", "a");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    printf("Ingrese el nombre del alumno: ");
    scanf("%s", alumno.nombre_alumno);
    printf("Ingrese la matr�cula del alumno: ");
    scanf("%d", &alumno.matricula);
    printf("Ingrese la especialidad del alumno: ");
    scanf("%s", alumno.especialidad);
    printf("Ingrese la nota 1: ");
    scanf("%f", &alumno.nota1);
    printf("Ingrese la nota 2: ");
    scanf("%f", &alumno.nota2);
    printf("Ingrese la nota 3: ");
    scanf("%f", &alumno.nota3);

    fprintf(file, "%s %d %s %.2f %.2f %.2f\n", alumno.nombre_alumno, alumno.matricula, alumno.especialidad, alumno.nota1, alumno.nota2, alumno.nota3);
    fclose(file);
}

void mostrar() {
    char buffer[200];
    FILE *file = fopen("alumnos.txt", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while (fgets(buffer, 200, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

void consultar() {
    char nombre_buscar[50];
    printf("Ingrese el nombre del alumno que desea buscar: ");
    scanf("%s", nombre_buscar);

    FILE *file = fopen("alumnos.txt", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    struct Alumno alumno;
    int encontrado = 0;

    while (fscanf(file, "%s %d %s %f %f %f", alumno.nombre_alumno, &alumno.matricula, alumno.especialidad, &alumno.nota1, &alumno.nota2, &alumno.nota3) != EOF) {
        if (strcmp(alumno.nombre_alumno, nombre_buscar) == 0) {
            printf("Alumno encontrado:\n");
            printf("Nombre: %s\n", alumno.nombre_alumno);
            printf("Matr�cula: %d\n", alumno.matricula);
            printf("Especialidad: %s\n", alumno.especialidad);
            printf("Notas: %.2f, %.2f, %.2f\n", alumno.nota1, alumno.nota2, alumno.nota3);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontr� un alumno con ese nombre.\n");
    }

    fclose(file);
}

