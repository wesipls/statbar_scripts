#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define NUM_COLUMNS 10

void print_column_sums(unsigned long long column_sums[], int num_columns) {
    for (int i = 0; i < num_columns; i++) {
        printf("The sum of column %d is: %llu\n", i, column_sums[i]);
    }
}

void calculate_column_sums(FILE *file, unsigned long long column_sums[], int num_columns) {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "cpu", 3) == 0 && isdigit(line[3])) {
            char *token = strtok(line, " "); // First token is "cpuX"
            int column_index = 0;

            while (token != NULL && column_index < num_columns) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    column_sums[column_index++] += strtoull(token, NULL, 10);
                }
            }
        }
    }
}

FILE* open_file(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Failed to open file");
    }
    return file;
}

int main() {
    unsigned long long column_sums[NUM_COLUMNS] = {0};
    FILE *file = open_file("/proc/stat");
    if (file == NULL) {
        return 1;
    }

    calculate_column_sums(file, column_sums, NUM_COLUMNS);
    fclose(file);

    print_column_sums(column_sums, NUM_COLUMNS);

    return 0;
}
