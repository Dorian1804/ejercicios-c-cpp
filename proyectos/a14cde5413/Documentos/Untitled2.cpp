#include <stdio.h>
#include <string.h>

typedef struct {
    char nombre_paciente[50];
    int num_paciente;  // Corrected data type
    char direccion_paciente[100];
    int telefono_paciente;
    int num_consultorio;
    char fecha_consulta[20];
} pacientes;

void capturar(FILE* archivo) {
    pacientes paciente1;

    printf("Nombre del paciente: ");
    fflush(stdin);
    fgets(paciente1.nombre_paciente, sizeof(paciente1.nombre_paciente), stdin);

    printf("Numero de paciente: ");
    scanf("%d", &paciente1.num_paciente);

    printf("Direccion del paciente: ");
    fflush(stdin);
    fgets(paciente1.direccion_paciente, sizeof(paciente1.direccion_paciente), stdin);

    printf("Telefono del paciente: ");
    scanf("%d", &paciente1.telefono_paciente);

    printf("Numero de consultorio: ");
    scanf("%d", &paciente1.num_consultorio);

    printf("Fecha de consulta: ");
    fflush(stdin);
    fgets(paciente1.fecha_consulta, sizeof(paciente1.fecha_consulta), stdin);

    fwrite(&paciente1, sizeof(pacientes), 1, archivo);
}

void listado(FILE* archivo) {
    pacientes paciente1;
    rewind(archivo);

    while (fread(&paciente1, sizeof(pacientes), 1, archivo)) {
        printf("Nombre: %s, Registro: %d, Direccion: %s, Telefono: %d, Consultorio: %d, Fecha: %s\n",
               paciente1.nombre_paciente, paciente1.num_paciente, paciente1.direccion_paciente,
               paciente1.telefono_paciente, paciente1.num_consultorio, paciente1.fecha_consulta);
    }
}

void consulta(FILE* archivo, const char* nombre_buscar) {
    pacientes paciente1;
    int encontrado = 0;
    rewind(archivo);

    while (fread(&paciente1, sizeof(pacientes), 1, archivo)) {
        if (strcmp(paciente1.nombre_paciente, nombre_buscar) == 0) {
            printf("Nombre: %s, Registro: %d, Direccion: %s, Telefono: %d, Consultorio: %d, Fecha: %s\n",
                   paciente1.nombre_paciente, paciente1.num_paciente, paciente1.direccion_paciente,
                   paciente1.telefono_paciente, paciente1.num_consultorio, paciente1.fecha_consulta);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No encontrado.\n");
    }
}

void modificar(FILE* archivo, const char* nombre_buscar) {
    pacientes paciente1;
    int encontrado = 0;
    long posicion;
    rewind(archivo);

    while (fread(&paciente1, sizeof(pacientes), 1, archivo)) {
        if (strcmp(paciente1.nombre_paciente, nombre_buscar) == 0) {
            printf("Modificar datos de:\n%s\n", paciente1.nombre_paciente);
            printf("Nuevo numero de registro: ");
            scanf("%d", &paciente1.num_paciente);
            printf("Nueva direccion: ");
            fflush(stdin);
            fgets(paciente1.direccion_paciente, sizeof(paciente1.direccion_paciente), stdin);
            printf("Nueva fecha: ");
            fgets(paciente1.fecha_consulta, sizeof(paciente1.fecha_consulta), stdin);

            posicion = ftell(archivo) - sizeof(paciente1);
            fseek(archivo, posicion, SEEK_SET);
            fwrite(&paciente1, sizeof(pacientes), 1, archivo);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No encontrado.\n");
    }
}

int main() {
    FILE* archivo;
    int opcion;
    char nombre_buscar[50];

    archivo = fopen("pacientes.dat", "r+b");
    if (archivo == NULL) {
        archivo = fopen("pacientes.dat", "w+b");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo\n");
            return 1;
        }
    }

    do {
        printf("\nMenu\n");
        printf("1. Capturar\n");
        printf("2. Listado\n");
        printf("3. Consulta\n");
        printf("4. Modificar\n");
        printf("5. Salir\n");
        printf("Elegir una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                capturar(archivo);
                break;
            case 2:
                listado(archivo);
                break;
            case 3:
                printf("Ingrese el nombre del paciente a consultar: ");
                fflush(stdin);
                fgets(nombre_buscar, sizeof(nombre_buscar), stdin);
                consulta(archivo, nombre_buscar);
                break;
            case 4:
                printf("Ingrese el nombre del paciente a modificar: ");
                fflush(stdin);
                fgets(nombre_buscar, sizeof(nombre_buscar), stdin);
                modificar(archivo, nombre_buscar);
                break;
            case 5:
                fclose(archivo);
                printf("Saliendo.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 5);

    return 0;
}



