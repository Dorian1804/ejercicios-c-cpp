#include <stdio.h>
#include <stdlib.h>

void escribirParrafo(const char *nombreArchivo);
void leerParrafo(const char *nombreArchivo);

int main() {
    const char *nombreArchivo = "escrito.txt";
    escribirParrafo(nombreArchivo);
    printf("P�RRAFO ESCRITO EN ARCHIVO\n");
    leerParrafo(nombreArchivo);
    return 0;
}

void escribirParrafo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escritura.\n");
        exit(1);
    }

    fprintf(archivo,"El principito.\n");
    fprintf(archivo,"Cuando yo ten�a seis a�os vi en un libro sobre la selva virgen que se titulaba Historias vividas.\n");
    fprintf(archivo,"una magn�fica l�mina. Representaba una serpiente boa que se tragaba a una fiera.\n");
    fprintf(archivo,"En el libro se afirmaba: La serpiente boa se traga su presa entera, sin masticarla. Luego ya no\n");
	fprintf(archivo,"puede moverse y duerme durante los seis meses que dura su digesti�n\n");
    fprintf(archivo,"Reflexion� mucho en ese momento sobre las aventuras de la jungla y a mi vez logr� trazar con\n");
    fprintf(archivo,"un l�piz de colores mi primer dibujo. Mi dibujo n�mero 1 era de esta manera:\n");
    fprintf(archivo,"Ense�� mi obra de arte a las personas mayores y les pregunt� si mi dibujo les daba miedo.\n");
    fprintf(archivo,"A trav�s de estas experiencias, el autor nos invita a mirar el mundo con ojos de ni�o y a valorar lo esencial que a menudo pasa desapercibido.\n");
	
	fclose(archivo);
    printf("P�rrafo escrito en el archivo '%s'.\n", nombreArchivo);
}

void leerParrafo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n");
        exit(1);
    }

    char linea[200];
    printf("Contenido del archivo '%s':\n", nombreArchivo);
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }

    fclose(archivo);
}

