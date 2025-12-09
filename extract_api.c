#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <regex.h>

void scan_directory(const char *dirpath, regex_t *regex) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char path[512];
        snprintf(path, sizeof(path), "%s/%s", dirpath, entry->d_name);

        struct stat st;
        if (stat(path, &st) != 0)
            continue;

        // If it's a directory → recurse
        if (S_ISDIR(st.st_mode)) {
            scan_directory(path, regex);
            continue;
        }

        // If it's not a .h file → ignore
        if (!strstr(entry->d_name, ".h"))
            continue;

        // Process header file
        FILE *f = fopen(path, "r");
        if (!f) continue;

        printf("=== %s ===\n", path);

        char line[1024];
        while (fgets(line, sizeof(line), f)) {
            // Trim leading whitespace
            char *trim = line;
            while (*trim == ' ' || *trim == '\t') trim++;

            // Match against function prototype pattern
            if (regexec(regex, trim, 0, NULL, 0) == 0) {
                printf("%s", trim);
            }
        }

        fclose(f);

        printf();
    }

    closedir(dir);
}

int main(void) {
    regex_t regex;

    // Very simplified C function prototype regex
    regcomp(&regex,
        "^[a-zA-Z_][a-zA-Z0-9_ \\*\t]*[ ]+[a-zA-Z_][a-zA-Z0-9_]*[ ]*\\([^;]*\\);",
        REG_EXTENDED);

    // Start recursive scan from the "library" folder
    scan_directory("Arduino_package/hardware/libraries", &regex);

    regfree(&regex);
    return 0;
}
