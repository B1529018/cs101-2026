#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_GROUPS 5
#define NUMBERS_PER_GROUP 7
#define MAX_NUMBER 69

static void shuffle(int numbers[], int size)
{
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
}

int main(void)
{
    int n;
    do {
        printf("歡迎光臨長庚樂透彩購買機台\n");
        printf("請問您要買幾組樂透：");

        if (scanf("%d", &n) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* 清除非數字輸入 */
            }
            n = 0;
        }
    } while (n < 1 || n > MAX_GROUPS);

    srand((unsigned int)time(NULL));

    FILE *fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        perror("無法建立 lotto.txt");
        return 1;
    }

    time_t current_time = time(NULL);
    char *time_text = ctime(&current_time);
    if (time_text != NULL) {
        time_text[strcspn(time_text, "\n")] = '\0';
    }

    fprintf(fp, "==================== lotto649 ====================\n");
    fprintf(fp, "= %s =\n", time_text != NULL ? time_text : "unknown time");

    for (int group = 0; group < n; group++) {
        int numbers[MAX_NUMBER];

        for (int i = 0; i < MAX_NUMBER; i++) {
            numbers[i] = i + 1;
        }

        shuffle(numbers, MAX_NUMBER);

        fprintf(fp, "[%d]:", group + 1);
        for (int i = 0; i < NUMBERS_PER_GROUP; i++) {
            fprintf(fp, " %02d", numbers[i]);
        }
        fprintf(fp, "\n");
    }

    for (int group = n; group < MAX_GROUPS; group++) {
        fprintf(fp, "[%d]: -- -- -- -- -- -- --\n", group + 1);
    }

    fprintf(fp, "==================== csie@CGU ====================\n");
    fclose(fp);

    printf("以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
