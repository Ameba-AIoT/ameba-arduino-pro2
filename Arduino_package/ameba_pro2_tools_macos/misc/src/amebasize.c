/*

Compile:

Windows:
gcc.exe -o amebasize.exe tools\windows\src\amebasize.c -static
strip amebasize.exe
### mingw32-gcc.exe -o amebasize.exe tools\windows\src\amebasize.c -static

linux:
gcc -o amebasize tools/linux/src/amebasize.c -static
strip amebasize

macsox:
gcc -o tools/macos/amebasize tools/macos/src/amebasize.c
strip amebasize

*/

#include <stdio.h>

int main(int argc, char *argv[]) {

    int size;
    char filename[512];

    if (argc < 2) {
        return -1;
    }

#if defined(__WIN32__) // MINGW64
    sprintf(filename, "%s\\flash_ntz.bin", argv[1]);
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits  and OS X 64bits
    sprintf(filename, "%s/flash_ntz.bin", argv[1]);
#else
#error compiler is not supported!
#endif

    FILE* fp_flash_ntz = fopen(filename, "rb");
    if (fp_flash_ntz != NULL) {
        fseek(fp_flash_ntz, 0L, SEEK_END);
        size = ftell(fp_flash_ntz);
        fclose(fp_flash_ntz);
        printf("flash_ntz %d\n", size);
    }

    return 0;
}
