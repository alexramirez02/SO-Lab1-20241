#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
FILE *input_file, *output_file;
char line[MAX_LINE_LENGTH];
// Manejar los diferentes casos de invocación
switch (argc) {
case 1: // Sin argumentos, leer de stdin y escribir en stdout
input_file = stdin;
output_file = stdout;
break;
case 2: // Un argumento, leer de archivo y escribir en stdout
input_file = fopen(argv[1], &quot;r&quot;);
if (input_file == NULL) {
perror(&quot;Error al abrir el archivo de entrada&quot;);
return 1;
}
output_file = stdout;
break;
case 3: // Dos argumentos, leer de archivo y escribir en archivo
input_file = fopen(argv[1], &quot;r&quot;);
if (input_file == NULL) {
perror(&quot;Error al abrir el archivo de entrada&quot;);
return 1;
}
output_file = fopen(argv[2], &quot;w&quot;);
if (output_file == NULL) {
perror(&quot;Error al abrir el archivo de salida&quot;);
return 1;
}
break;
default:
fprintf(stderr, &quot;Uso: %s [archivo_entrada]
[archivo_salida]\n&quot;, argv[0]);
return 1;
}
// Leer el archivo línea por línea y almacenarlas en un arreglo
char *lines[MAX_LINE_LENGTH];
int line_count = 0;
while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
lines[line_count++] = strdup(line);
}
// Escribir las líneas en orden inverso
for (int i = line_count - 1; i &gt;= 0; i--) {
fprintf(output_file, &quot;%s&quot;, lines[i]);
free(lines[i]);
}
// Cerrar los archivos
fclose(input_file);

if (output_file != stdout) {
fclose(output_file);
}
return 0;
}