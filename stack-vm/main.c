/*
 * File: main.cpp
 * Description: Application entry point
 * Created at: 2018-3-31
 */

#include <glib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack-vm.h"

/*
 * Read the program.
 */
GArray *read_prog(char *filename);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    GArray *prog = read_prog(argv[1]);
    load_program(prog);
    run();
    g_array_free(prog, FALSE);
    return 0;
}

GArray *read_prog(char *filename) {
    FILE *f;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    GArray *res = g_array_new(FALSE, FALSE, sizeof(uint32_t));
    f = fopen(filename, "r");
    uint32_t i;
    while ((read = getline(&line, &len, f)) != -1) {
        sscanf(line, "%u\n", &i);
        g_array_append_val(res, i);
    }
    return res;
}
