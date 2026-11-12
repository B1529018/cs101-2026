#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPLOYEE_COUNT 3
#define EMPLOYEE_FILE "employee.bin"

typedef struct employee {
    int id;
    char name[10];
    int age;
    float salary;
} employee_t;

void emp_info(employee_t emp) {
    printf("employee id = %d\n", emp.id);
    printf("employee name = %s\n", emp.name);
    printf("employee age = %d\n", emp.age);
    printf("employee salary = %.2f\n", emp.salary);
}

int emp_average_age(const employee_t emp[], int n) {
    int sum = 0;

    if (n <= 0) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        sum += emp[i].age;
    }

    return sum / n;
}

void emp_writefile(const employee_t emp[], int n) {
    FILE *fp = fopen(EMPLOYEE_FILE, "wb");

    if (fp == NULL) {
        perror("Cannot open employee.bin for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        if (fwrite(&emp[i], sizeof(employee_t), 1, fp) != 1) {
            perror("Cannot write employee.bin");
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fp);
}

int emp_readfile(employee_t emp[], int capacity) {
    FILE *fp = fopen(EMPLOYEE_FILE, "rb");
    int count = 0;

    if (fp == NULL) {
        perror("Cannot open employee.bin for reading");
        return 0;
    }

    while (count < capacity &&
           fread(&emp[count], sizeof(employee_t), 1, fp) == 1) {
        count++;
    }

    fclose(fp);
    return count;
}

int main(void) {
    employee_t emp[EMPLOYEE_COUNT] = {
        {1, "IU",     20, 30000.0f},
        {2, "taylor", 26, 36000.0f},
        {3, "swift",  31, 90000.0f}
    };

    int average_age = emp_average_age(emp, EMPLOYEE_COUNT);
    printf("Average age: %d\n", average_age);

    emp_writefile(emp, EMPLOYEE_COUNT);

    employee_t read_emp[EMPLOYEE_COUNT];
    int read_count = emp_readfile(read_emp, EMPLOYEE_COUNT);

    for (int i = 0; i < read_count; i++) {
        emp_info(read_emp[i]);
    }

    return 0;
}
