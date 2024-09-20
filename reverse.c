#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para voltear el orden de las lineas
void reverse_lines(FILE *input, FILE *output) {
    size_t len = 0;
    char *line = NULL;
    char **lines = NULL;
    size_t num_lines = 0;
    size_t capacity = 1000;
    

    // Reservar memoria
    lines = malloc(capacity * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    // Leer las lineas 
    while (getline(&line, &len, input) != -1) {
        // remueve el codigo de nueva linea (\n) si hay al final del archivo
        size_t line_length = strlen(line);
        if (line_length > 0 && line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
        }
        
        if (num_lines >= capacity) {
            capacity *= 2;
            lines = realloc(lines, capacity * sizeof(char *));
            if (lines == NULL) {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }
        }

        // Guarda las lineas
        lines[num_lines] = strdup(line);
        if (lines[num_lines] == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        num_lines++;
    }
    free(line);

    // Imprime las lineas en el orden contrario
    for (size_t i = num_lines; i > 0; i--) {
        fprintf(output, "%s", lines[i - 1]);
        if (i > 1) { 
            fprintf(output, "\n");
        }
        free(lines[i - 1]);
    }
    free(lines);

    // Imprime un salto de linea en la ultima fila
    if (num_lines > 0) {
        fprintf(output, "\n");
    }
}
const char* get_filename(const char *path) {
    const char *filename = strrchr(path, '/');
    if (filename == NULL) {
        filename = strrchr(path, '\\');
    }
    return filename ? filename + 1 : path;
}

int main(int argc, char *argv[]) {
    // Valores default por si no se agregan los otros dos parametros
    FILE *input = stdin;
    FILE *output = stdout;

    // Imprime como utilizarlo si se usa mal, mas de dos intputs
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // Controla que el archivo de entrada se pueda abrir
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }

    // Controla que la salida se pueda abrir y que ambos archivos sean diferentes
    if (argc == 3) {
        if (strcmp(get_filename(argv[1]), get_filename(argv[2])) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            fclose(input);
            exit(1);
        }
    }


    // Llama la función
    reverse_lines(input, output);

    // Cierra los archivos de entrada y salida si los uso

    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);

    return 0;
    //Este es un cambio a mi repositorio
}
