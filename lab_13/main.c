#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { false, true } bool;
typedef enum { kWait, kOk, kExit } status;

#define HEADER_SIZE 10

int get_size(char *a) {
    return (a[0] & 0x7F) << 21 | (a[1] & 0x7F) << 14 | (a[2] & 0x7F) << 7 | (a[3] & 0x7F);
}

bool print_frames(FILE* file) {
    char buffer[HEADER_SIZE];
    fread(buffer, 1, HEADER_SIZE, file);

    if (buffer[0] == '\0') {
        return false;
    }

    int size = get_size(buffer + 4);
    printf("%4s: ", buffer);
    if (buffer[0] == 'A' && buffer[1] == 'P' && buffer[2] == 'I' && buffer[3] == 'C') {
        printf("offer your solution for withdrawal\n");
        return true;
    }

    char buf[size];
    fread(buf, 1, size, file);
    for (int i = 0; i < size; i++) {
        if (20 <= buf[i] && buf[i] <= 126) {
            printf("%c", buf[i]);
        }
    }
    printf("\n");

    return true;
}

void show_metadata(const char *filepath) {
    FILE* file = fopen(filepath, "rb");

    if (!file) {
        perror("Error opening file");
        return;
    }

    // Массив для считывания заголовка ID3v2
    char header[HEADER_SIZE];
    fread(header, 1, HEADER_SIZE, file);

    // Проверяем, начинается ли файл с заголовка "ID3"
    if (header[0] == 'I' && header[1] == 'D' && header[2] == '3') {
        int tag_size = get_size(header + 6);
        while (ftell(file) < tag_size) {
            if (!print_frames(file)) {
                break;
            }
        }
    } else {
        printf("ID3v2 tag not found in the file\n");
    }

    fclose(file);
}

bool set_value(FILE* file, FILE* out_file, const char* prop_name, const char* prop_value) {
    char buffer[HEADER_SIZE];
    fread(buffer, 1, HEADER_SIZE, file);
    fwrite(buffer, 1, HEADER_SIZE, out_file);

    int size = get_size(buffer + 4);
    char buf[size];
    fread(buf, 1, size, file);
    if (buffer[0] == prop_name[0] && buffer[1] == prop_name[1] && buffer[2] == prop_name[2] && buffer[3] == prop_name[3]) {
        for (int i = 0; i < size; i++) {
            buf[i] = '\0';
        }

        int value_len = strlen(prop_value);
        for (int i = 0; i < value_len; i++) {
            buf[i] = prop_value[i];
        }

        fwrite(buf, 1, size, out_file);
        return true;
    } else {
        fwrite(buf, 1, size, out_file);
    }

    return false;
}

// Функция для установки значения определенного поля метаинформации
void set_metadata(const char *filepath, const char *outpath, const char *prop_name, const char *prop_value) {
    FILE* file = fopen(filepath, "rb");
    FILE* out_file = fopen(outpath, "wb");

    fseek(file, 0, SEEK_END);
    int end = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (!file || !out_file) {
        perror("Error opening file");
        return;
    }

    // Массив для считывания заголовка ID3v2
    char header[HEADER_SIZE];
    fread(header, 1, HEADER_SIZE, file);
    fwrite(header, 1, HEADER_SIZE, out_file);

    // Проверяем, начинается ли файл с заголовка "ID3"
    if (header[0] == 'I' && header[1] == 'D' && header[2] == '3') {
        int tag_size = get_size(header + 6);
        bool found = false;
        while (ftell(file) < tag_size) {
            bool st = set_value(file, out_file, prop_name, prop_value);
            if (st) {
                while (ftell(file) != end) {
                    char fg = fgetc(file);
                    fputc(fg, out_file);
                }
                break;
            }
        }
    } else {
        printf("ID3v2 tag not found in the file\n");
    }

    fclose(file);
    fclose(out_file);
}

status print_frame(FILE* file, const char* prop_name) {
    char buffer[HEADER_SIZE];
    fread(buffer, 1, HEADER_SIZE, file);

    if (buffer[0] == '\0') {
        return kExit;
    }

    int size = get_size(buffer + 4);
    char buf[size];
    fread(buf, 1, size, file);
    if (buffer[0] == prop_name[0] && buffer[1] == prop_name[1] && buffer[2] == prop_name[2] && buffer[3] == prop_name[3]) {
        for (int i = 0; i < size; i++) {
            if (20 <= buf[i] && buf[i] <= 126) {
                printf("%c", buf[i]);
            }
        }
        printf("\n");
        return kOk;
    }

    return kWait;
}

// Функция для получения значения определенного поля метаинформации
void get_metadata(const char *filepath, const char *prop_name) {
    FILE* file = fopen(filepath, "rwb");

    if (!file) {
        perror("Error opening file");
        return;
    }

    // Массив для считывания заголовка ID3v2
    char header[HEADER_SIZE];
    fread(header, 1, HEADER_SIZE, file);

    // Проверяем, начинается ли файл с заголовка "ID3"
    if (header[0] == 'I' && header[1] == 'D' && header[2] == '3') {
        int tag_size = get_size(header + 6);
        while (ftell(file) < tag_size) {
            status st = print_frame(file, prop_name);
            if (st == kExit || st == kOk) {
                break;
            }
        }
    } else {
        printf("ID3v2 tag not found in the file\n");
    }

    fclose(file);
}

int main(int argc, char **argv) {
    if (argc > 4) {
        printf("Usage: %s --filepath=<file> [--show | --set=<prop_name> --value=<prop_value> | --get=<prop_name>]\n", argv[0]);
        return 1;
    }

    char *filepath = NULL;
    char *command = NULL;
    char *prop_name = NULL;
    char *prop_value = NULL;

    for (int i = 1; i < argc; i++) {
        if (strstr(argv[i], "--filepath=") != NULL) {
            filepath = argv[i] + strlen("--filepath=");
        } else if (strstr(argv[i], "--show") != NULL) {
            command = "--show";
        } else if (strstr(argv[i], "--set=") != NULL) {
            command = "--set";
            prop_name = argv[i] + strlen("--set=");
        } else if (strstr(argv[i], "--value=") != NULL) {
            prop_value = argv[i] + strlen("--value=");
        } else if (strstr(argv[i], "--get=") != NULL) {
            command = "--get";
            prop_name = argv[i] + strlen("--get=");
        }
    }

    if (filepath == NULL || command == NULL) {
        printf("Invalid command or file path\n");
        return 1;
    }

    if (strcmp(command, "--show") == 0) {
        // get_frame_size(filepath);
        show_metadata(filepath);
    } else if (strcmp(command, "--set") == 0) {
        if (prop_name != NULL && prop_value != NULL) {
            set_metadata(filepath, "kek.mp3", prop_name, prop_value);
        } else {
            printf("Invalid command format\n");
            return 1;
        }
    } else if (strcmp(command, "--get") == 0) {
        if (prop_name != NULL) {
            get_metadata(filepath, prop_name);
        } else {
            printf("Invalid command format\n");
            return 1;
        }
    }

    return 0;
}