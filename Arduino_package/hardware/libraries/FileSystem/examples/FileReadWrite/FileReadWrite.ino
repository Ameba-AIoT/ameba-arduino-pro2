/*
 This sketch shows how to open/close file and perform read/write to it.
 */

#include "AmebaFatFS.h"

char filename[] = "test.txt";
char write_content[] = "hello world!";

AmebaFatFS fs;

void setup() {
    char buf[128];
    char path[128];

    fs.begin();

    printf("write something to \"%s\"\r\n", filename);
    sprintf(path, "%s%s", fs.getRootPath(), filename);
    File file = fs.open(path);

    file.println(write_content);

    file.close();
    printf("write finish\r\n\r\n");

    printf("read back from \"%s\"\r\n", filename);
    file = fs.open(path);

    memset(buf, 0, sizeof(buf));
    file.read(buf, sizeof(buf));

    file.close();
    printf("==== content ====\r\n");
    printf("%s", buf);
    printf("====   end   ====\r\n");

    fs.end();
}

void loop() {
    delay(1000);
}
