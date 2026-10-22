#include <stdio.h>

int main(void) {
    int a[] = {0, 1, 2};
    char b[] = "ABC";
    float c[] = {1.1f, 1.2f, 1.3f};

    int read_a[3];
    char read_b[4] = {0};
    float read_c[3];

    FILE *fp = fopen("a.bin", "wb");
    if (fp == NULL) {
        perror("無法建立 a.bin");
        return 1;
    }

    if (fwrite(a, sizeof(a[0]), 3, fp) != 3 ||
        fwrite(b, sizeof(b[0]), 3, fp) != 3 ||
        fwrite(c, sizeof(c[0]), 3, fp) != 3) {
        fprintf(stderr, "寫入 a.bin 失敗\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    fp = fopen("a.bin", "rb");
    if (fp == NULL) {
        perror("無法讀取 a.bin");
        return 1;
    }

    if (fread(read_a, sizeof(read_a[0]), 3, fp) != 3 ||
        fread(read_b, sizeof(b[0]), 3, fp) != 3 ||
        fread(read_c, sizeof(read_c[0]), 3, fp) != 3) {
        fprintf(stderr, "讀取 a.bin 失敗\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    for (int i = 0; i < 3; i++) {
        printf("%d%c", read_a[i], i == 2 ? '\n' : ' ');
    }

    printf("%s\n", read_b);

    for (int i = 0; i < 3; i++) {
        printf("%f%c", read_c[i], i == 2 ? '\n' : ' ');
    }

    return 0;
}
