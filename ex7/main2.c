#include <stdio.h>
#include <stdlib.h>

#define BOOK_COUNT 6
#define TITLE_SIZE 128

typedef struct Books {
    int id;
    int price;
    char title[TITLE_SIZE];
} book_t;

int total_price(const book_t books[], int count)
{
    int total = 0;

    for (int i = 0; i < count; i++) {
        total += books[i].price;
    }

    return total;
}

void list_books(const book_t books[], int count)
{
    printf("%-4s %-8s %s\n", "Id", "Price", "Title");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-4d %-8d %s\n",
               books[i].id,
               books[i].price,
               books[i].title);
    }
}

static int save_books(const char *filename, const book_t books[], int count)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("無法建立 Book.bin");
        return 0;
    }

    size_t written = fwrite(books, sizeof(book_t), (size_t)count, fp);
    fclose(fp);

    return written == (size_t)count;
}

static int load_books(const char *filename, book_t books[], int capacity)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("無法讀取 Book.bin");
        return 0;
    }

    size_t read_count = fread(books, sizeof(book_t), (size_t)capacity, fp);
    fclose(fp);

    return (int)read_count;
}

int main(void)
{
    book_t books[BOOK_COUNT] = {
        {1, 1000, "All the Light We Cannot See"},
        {2,  300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4,  550, "Killers of the Flower Moon"},
        {5,  870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    if (!save_books("Book.bin", books, BOOK_COUNT)) {
        return 1;
    }

    book_t loaded_books[BOOK_COUNT];
    int count = load_books("Book.bin", loaded_books, BOOK_COUNT);
    if (count <= 0) {
        return 1;
    }

    list_books(loaded_books, count);
    printf("\nTotal price: %d\n", total_price(loaded_books, count));

    return 0;
}
