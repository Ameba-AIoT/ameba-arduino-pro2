/*
 This sketch shows how to check whether a item is a directory or a file.
 */

#include "AmebaFatFS.h"

AmebaFatFS fs;

void setup() {
    char buf[512];
    char path[512];
    char *p;

    fs.begin();

    fs.readDir(fs.getRootPath(), buf, sizeof(buf));

    p = buf;
    while (strlen(p) > 0) {
        printf("\"%s\" is ", p);

        sprintf(path, "%s%s", fs.getRootPath(), p);
        if (fs.isDir(path)) {
            printf("dir\r\n");
        }

        if (fs.isFile(path)) {
            printf("file\r\n");
        }

        p += strlen(p) + 1;
    }

    fs.end();
}

void loop() {
    // put your main code here, to run repeatedly:
    delay(1000);
}
