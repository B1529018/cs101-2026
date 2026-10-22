#include <stdio.h>

int main(void)
{
    FILE *fp;

    int a[] = {0, 1, 2};
    char b[] = "ABC";
    float c[] = {1.1f, 1.2f, 1.3f};

    int ra[3];
    char rb[3];
    float rc[3];

    /* Open binary file for writing */
    fp = fopen("a.bin", "wb");
    if (fp == NULL) {
        printf("File open error!\n");
        return 1;
    }

    fwrite(a, sizeof(int), 3, fp);
    fwrite(b, sizeof(char), 3, fp);
    fwrite(c, sizeof(float), 3, fp);

    fclose(fp);

    /* Open binary file for reading */
    fp = fopen("a.bin", "rb");
    if (fp == NULL) {
        printf("File open error!\n");
        return 1;
    }

    fread(ra, sizeof(int), 3, fp);
    fread(rb, sizeof(char), 3, fp);
    fread(rc, sizeof(float), 3, fp);

    fclose(fp);

    /* Print the contents */
    for (int i = 0; i < 3; i++)
        printf("%d ", ra[i]);

    printf("\n");

    for (int i = 0; i < 3; i++)
        printf("%c ", rb[i]);

    printf("\n");

    for (int i = 0; i < 3; i++)
        printf("%f ", rc[i]);

    printf("\n");

    return 0;
}
