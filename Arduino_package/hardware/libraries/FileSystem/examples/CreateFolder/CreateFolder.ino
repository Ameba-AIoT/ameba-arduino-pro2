/*
 This sketch shows how to create a folder and open a file under it.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/File%20System/Simple%20applications%20with%20SD%20card.html
*/

#include "AmebaFatFS.h"

char dirname[] = "testdir";
char filename[] = "test.txt";
char write_content[] = "hello world!";

AmebaFatFS fs;

void setup()
{
    char buf[128];
    char path[128];

    fs.begin();

    sprintf(path, "%s%s", fs.getRootPath(), dirname);
    fs.mkdir(path);
    printf("create dir at \"%s\"\r\n", path);

    sprintf(path, "%s%s/%s", fs.getRootPath(), dirname, filename);
    File file = fs.open(path);
    file.println(write_content);
    file.close();
    printf("create file at \"%s\"\r\n", path);

    printf("read back from \"%s\"\r\n", path);
    file = fs.open(path);

    memset(buf, 0, sizeof(buf));
    file.read(buf, sizeof(buf));

    file.close();
    printf("==== content ====\r\n");
    printf("%s", buf);
    printf("====   end   ====\r\n");

    fs.end();
}

void loop()
{
    delay(1000);
}
