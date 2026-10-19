/*
 * Registro de pacientes con archivos binarios (C)
 * Captura, listado, consulta y modificación de pacientes en pacientes.dat
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARCHIVO     "pacientes.dat"
#define MAX_LINEA   200
#define MAX_NOMBRE  50
#define MAX_DIR     100
#define MAX_TEL     16
#define MAX_FECHA   20

typedef struct {
    char nombre_paciente[MAX_NOMBRE];
    int  num_paciente;
    char direccion_paciente[MAX_DIR];
    char telefono_paciente[MAX_TEL];   /* texto: un teléfono no cabe en un int */
    int  num_consultorio;
    char fecha_consulta[MAX_FECHA];
} Paciente;

/* ---------- Entrada de datos ---------- */

/* Lee una línea completa (con espacios), sin el salto de línea final. */
static void leer_texto(const char *mensaje, char *destino, size_t tam) {
    char buffer[MAX_LINEA];
    for (;;) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            destino[0] = '\0';
            return;
        }
        if (strchr(buffer, '\n') == NULL) {          /* línea más larga que el buffer */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Texto demasiado largo (máximo %zu caracteres).\n", tam - 1);
            continue;
        }
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (buffer[0] == '\0') {
            printf("No puede estar vacío.\n");
            continue;
        }
        if (strlen(buffer) >= tam) {
            printf("Texto demasiado largo (máximo %zu caracteres).\n", tam - 1);
            continue;
        }
        strcpy(destino, buffer);
        return;
    }
}

/* Entero >= 0. Devuelve -1 si se acaba la entrada (EOF). */
static int leer_entero(const char *mensaje) {
    char buffer[MAX_LINEA], *fin;
    for (;;) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof buffer, stdin) == NULL) return -1;
        long valor = strtol(buffer, &fin, 10);
        if (fin != buffer && (*fin == '\n' || *fin == '\r' || *fin == '\0') && valor >= 0)
            return (int)valor;
        printf("Ingrese un número entero válido.\n");
    }
}

/* Teléfono: solo dígitos, de 7 a 15. */
static void leer_telefono(const char *mensaje, char *destino) {
    for (;;) {
        leer_texto(mensaje, destino, MAX_TEL);
        size_t n = strlen(destino), i;
        for (i = 0; i < n && isdigit((unsigned char)destino[i]); i++) { }
        if (n >= 7 && i == n) return;
        if (destino[0] == '\0') return;              /* EOF */
        printf("Ingrese solo dígitos (de 7 a 15).\n");
    }
}

static int igual_sin_mayusculas(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == *b;
}

static void imprimir_paciente(const Paciente *p) {
    printf("Nombre: %s\n", p->nombre_paciente);
    printf("Registro: %d\n", p->num_paciente);
    printf("Dirección: %s\n", p->direccion_paciente);
    printf("Teléfono: %s\n", p->telefono_paciente);
    printf("Consultorio: %d\n", p->num_consultorio);
    printf("Fecha de consulta: %s\n", p->fecha_consulta);
}

/* ---------- Operaciones sobre el archivo ---------- */

void capturar(FILE *archivo) {
    Paciente p;
    memset(&p, 0, sizeof p);

    leer_texto("Nombre del paciente: ", p.nombre_paciente, MAX_NOMBRE);
    p.num_paciente = leer_entero("Número de paciente: ");
    leer_texto("Dirección del paciente: ", p.direccion_paciente, MAX_DIR);
    leer_telefono("Teléfono del paciente: ", p.telefono_paciente);
    p.num_consultorio = leer_entero("Número de consultorio: ");
    leer_texto("Fecha de consulta (dd/mm/aaaa): ", p.fecha_consulta, MAX_FECHA);

    fseek(archivo, 0, SEEK_END);                     /* siempre agregar al final */
    if (fwrite(&p, sizeof p, 1, archivo) != 1) {
        printf("Error al escribir en el archivo.\n");
        return;
    }
    fflush(archivo);
    printf("Paciente guardado.\n");
}

void listado(FILE *archivo) {
    Paciente p;
    int total = 0;

    rewind(archivo);
    while (fread(&p, sizeof p, 1, archivo) == 1) {
        printf("\n");
        imprimir_paciente(&p);
        total++;
    }
    if (total == 0) printf("No hay pacientes registrados.\n");
}

void consulta(FILE *archivo, const char *nombre_buscar) {
    Paciente p;

    rewind(archivo);
    while (fread(&p, sizeof p, 1, archivo) == 1) {
        if (igual_sin_mayusculas(p.nombre_paciente, nombre_buscar)) {
            printf("Paciente encontrado:\n");
            imprimir_paciente(&p);
            return;
        }
    }
    printf("No encontrado.\n");
}

void modificar(FILE *archivo, const char *nombre_buscar) {
    Paciente p;
    long posicion;

    rewind(archivo);
    for (;;) {
        posicion = ftell(archivo);                   /* inicio del registro que se va a leer */
        if (fread(&p, sizeof p, 1, archivo) != 1) break;

        if (igual_sin_mayusculas(p.nombre_paciente, nombre_buscar)) {
            printf("Modificar datos de: %s\n", p.nombre_paciente);
            p.num_paciente = leer_entero("Nuevo número de paciente: ");
            leer_texto("Nueva dirección: ", p.direccion_paciente, MAX_DIR);
            leer_telefono("Nuevo teléfono: ", p.telefono_paciente);
            p.num_consultorio = leer_entero("Nuevo número de consultorio: ");
            leer_texto("Nueva fecha de consulta (dd/mm/aaaa): ", p.fecha_consulta, MAX_FECHA);

            fseek(archivo, posicion, SEEK_SET);      /* obligatorio entre leer y escribir */
            if (fwrite(&p, sizeof p, 1, archivo) != 1) {
                printf("Error al escribir en el archivo.\n");
                return;
            }
            fflush(archivo);
            printf("Paciente actualizado.\n");
            return;
        }
    }
    printf("No encontrado.\n");
}

/* ---------- Programa principal ---------- */

int main(void) {
    FILE *archivo;
    int opcion;
    char nombre_buscar[MAX_NOMBRE];

    archivo = fopen(ARCHIVO, "r+b");
    if (archivo == NULL) {
        archivo = fopen(ARCHIVO, "w+b");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo.\n");
            return 1;
        }
    }

    do {
        printf("\nMenú\n");
        printf("1. Capturar\n");
        printf("2. Listado\n");
        printf("3. Consulta\n");
        printf("4. Modificar\n");
        printf("5. Salir\n");
        opcion = leer_entero("Elegir una opción: ");
        if (opcion < 0) opcion = 5;                  /* fin de la entrada */

        switch (opcion) {
            case 1:
                capturar(archivo);
                break;
            case 2:
                listado(archivo);
                break;
            case 3:
                leer_texto("Ingrese el nombre del paciente a consultar: ", nombre_buscar, MAX_NOMBRE);
                consulta(archivo, nombre_buscar);
                break;
            case 4:
                leer_texto("Ingrese el nombre del paciente a modificar: ", nombre_buscar, MAX_NOMBRE);
                modificar(archivo, nombre_buscar);
                break;
            case 5:
                printf("Saliendo.\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 5);

    fclose(archivo);
    return 0;
}
