
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

#define PREFIX "simfs_"
#define NAME_SIZE 64
#define PATH_SIZE (sizeof(PREFIX) + NAME_SIZE)
#define TEXT_SIZE 512

typedef struct {
    char name[NAME_SIZE];
} SimFile;

/* Read one complete line from the user. */
int read_line(const char* prompt, char* buffer, size_t size) {
    printf("%s", prompt);

    if (fgets(buffer, (int)size, stdin) == NULL)
        return 0;

    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        printf("Input is too long.\n");
        return 0;
    }

    return 1;
}

/* Accept safe names such as notes.txt or report-1. */
int valid_name(const char *name) {
    if (name[0] == '\0' || strlen(name) >= NAME_SIZE)
        return 0;

    for (size_t i = 0; name[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)name[i];

        if (!isalnum(ch) && ch != '_' && ch != '-' && ch != '.')
            return 0;
    }

    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
        return 0;

    return 1;
}

/* Build the managed file's path. */
int make_path(const char* name, char* path, size_t size) {
    if (!valid_name(name))
        return 0;

    int len = snprintf(path, size, PREFIX "%s", name);
    return len >= 0 && (size_t)len < size;
}

/* Create a new file without intentionally replacing an existing one. */
void create_file(void) {
    char name[NAME_SIZE], path[PATH_SIZE];

    if (!read_line("Enter file name: ", name, sizeof name))
        return;

    if (!make_path(name, path, sizeof path)) {
        printf("Invalid file name.\n");
        return;
    }

    FILE* check = fopen(path, "rb");

    if (check != NULL) {
        fclose(check);
        printf("File already exists.\n");
        return;
    }

    FILE* file = fopen(path, "wb");

    if (file == NULL) {
        perror("Could not create file");
        return;
    }

    if (fclose(file) != 0) {
        perror("Could not finish creating file");
        return;
    }

    printf("File created: %s\n", name);
}

/* Replace all existing contents with new text. */
void write_file(void) {
    char name[NAME_SIZE], path[PATH_SIZE], text[TEXT_SIZE];

    if (!read_line("Enter file name: ", name, sizeof name) ||
        !make_path(name, path, sizeof path)) {
        printf("Invalid file name.\n");
        return;
    }

    if (!read_line("Enter text (one line): ", text, sizeof text))
        return;

    FILE *file = fopen(path, "wb");

    if (file == NULL) {
        perror("Could not open file for writing");
        return;
    }

    int success = fputs(text, file) != EOF;

    if (fclose(file) != 0) success = 0;

    if (success) printf("File written successfully.\n");
    else printf("An error occurred while writing the file.\n");
}

/* Display the file's contents. */
void read_file(void) {
    char name[NAME_SIZE], path[PATH_SIZE];
    char buffer[TEXT_SIZE];

    if (!read_line("Enter file name: ", name, sizeof name) ||
        !make_path(name, path, sizeof path)) {
        printf("Invalid file name.\n");
        return;
    }

    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        perror("Could not open file");
        return;
    }

    printf("\n--- Contents of %s ---\n", name);

    while (fgets(buffer, sizeof buffer, file) != NULL)
        fputs(buffer, stdout);

    if (ferror(file))
        printf("\nError while reading file.\n");

    printf("\n----------------------\n");
    fclose(file);
}

/* Add text to the end of an existing file. */
void append_file(void) {
    char name[NAME_SIZE], path[PATH_SIZE], text[TEXT_SIZE];

    if (!read_line("Enter file name: ", name, sizeof name) ||
        !make_path(name, path, sizeof path)) {
        printf("Invalid file name.\n");
        return;
    }

    if (!read_line("Enter text to append: ", text, sizeof text))
        return;

    FILE *file = fopen(path, "ab");

    if (file == NULL) {
        perror("Could not open file for appending");
        return;
    }

    int success = fputs(text, file) != EOF;

    if (fclose(file) != 0)
        success = 0;

    if (success)
        printf("Text appended successfully.\n");
    else
        printf("An error occurred while appending.\n");
}

/* Delete a managed file. */
void delete_file(void) {
    char name[NAME_SIZE], path[PATH_SIZE];

    if (!read_line("Enter file name: ", name, sizeof name) ||
        !make_path(name, path, sizeof path)) {
        printf("Invalid file name.\n");
        return;
    }

    if (remove(path) == 0)
        printf("File deleted: %s\n", name);
    else
        perror("Could not delete file");
}

/* List files that use this program's prefix. */
void list_files(void) {
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("Could not open current directory");
        return;
    }

    struct dirent* entry;
    size_t prefix_len = strlen(PREFIX);
    int count = 0;

    printf("\n--- Managed files ---\n");

    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, PREFIX, prefix_len) == 0) {
            printf("%s\n", entry->d_name + prefix_len);
            count++;
        }
    }

    if (count == 0)
        printf("No files found.\n");

    closedir(dir);
}

/* Parse a menu choice without accepting trailing junk. */
int read_choice(int *choice) {
    char line[32], *end;
    long value;

    if (!read_line("Choose: ", line, sizeof line))
        return 0;

    value = strtol(line, &end, 10);

    while (isspace((unsigned char)*end))
        end++;

    if (end == line || *end != '\0' ||
        value < 0 || value > 6) {
        printf("Invalid choice.\n");
        return -1;
    }

    *choice = (int)value;
    return 1;
}

int main(void) {
    int choice;

    for (;;) {
        printf("\n--- Simple File System ---\n");
        printf("1. Create file\n");
        printf("2. Write/replace file contents\n");
        printf("3. Read file\n");
        printf("4. Append to file\n");
        printf("5. Delete file\n");
        printf("6. List managed files\n");
        printf("0. Exit\n");

        int result = read_choice(&choice);

        if (result == 0)
            break;

        if (result == -1)
            continue;

        switch (choice) {
            case 1: create_file(); break;
            case 2: write_file(); break;
            case 3: read_file(); break;
            case 4: append_file(); break;
            case 5: delete_file(); break;
            case 6: list_files(); break;
            case 0: return 0;
        }
    }

    return 0;
}
