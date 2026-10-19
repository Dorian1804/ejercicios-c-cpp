#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Estudiante {
char nombre_estudiante[50];
int registro;
char carrera[50];
float cal1, cal2, cal3;
};

void capturar();
void mostrar();
void consultar();


int main()
{
int opcion;
do
{
printf("\nMen�:\n");
printf("1. Capturar estudiante\n");
printf("2. Mostrar estudiantes\n");
printf("3. Consultar estudiantes\n");
printf("4. Salir\n");
printf("Ingrese una opci�n: ");
scanf("%d", &opcion);

switch (opcion)
{
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

void capturar()
{
struct Estudiante estudiante;
FILE *file = fopen("estudiantes.txt", "a");
if (file == NULL)
{
printf("No se pudo abrir el archivo.\n");
return;
}

printf("Ingrese el nombre del estudiante: ");
scanf("%s", estudiante.nombre_estudiante);
printf("Ingrese el registro del estudiante: ");
scanf("%d", &estudiante.registro);
printf("Ingrese la carrera del estudiante: ");
scanf("%s", estudiante.carrera);
printf("Ingrese la calificaci�n 1: ");
scanf("%f", &estudiante.cal1); 
printf("Ingrese la calificaci�n 2: ");
scanf("%f", &estudiante.cal2);
printf("Ingrese la calificaci�n 3: ");
scanf("%f", &estudiante.cal3);

fprintf(file, "%s %d %s %.2f %.2f %.2f\n", estudiante.nombre_estudiante, estudiante.registro, estudiante.carrera, estudiante.cal1, estudiante.cal2, estudiante.cal3);
fclose(file);
}

void mostrar()
{
char buffer[200];
FILE *file = fopen("estudiantes.txt", "r");
if (file == NULL) {
printf("No se pudo abrir el archivo.\n");
return;
}

while (fgets(buffer, 200, file) != NULL)
{
printf("%s", buffer);
}
fclose(file);
}

void consultar()
{
char nombre_buscar[50];
printf("Ingrese el nombre del estudiante que desea buscar: ");
scanf("%s", nombre_buscar);

FILE *file = fopen("estudiantes.txt", "r");
if (file == NULL)
{
printf("No se pudo abrir el archivo.\n");
return;
}

struct Estudiante estudiante;
int encontrado = 0;

while (fscanf(file, "%s %d %s %f %f %f", estudiante.nombre_estudiante, &estudiante.registro, estudiante.carrera, &estudiante.cal1, &estudiante.cal2, &estudiante.cal3) != EOF) {
if (strcmp(estudiante.nombre_estudiante, nombre_buscar) == 0)
{
printf("Estudiante encontrado:\n");
printf("Nombre: %s\n", estudiante.nombre_estudiante);
printf("Registro: %d\n", estudiante.registro);
printf("Carrera: %s\n", estudiante.carrera);
printf("Calificaciones: %.2f, %.2f, %.2f\n", estudiante.cal1, estudiante.cal2, estudiante.cal3);
encontrado = 1;
break;
}
}

if (!encontrado)
{
printf("No se encontr� un estudiante con ese nombre.\n");
}

fclose(file);
}
