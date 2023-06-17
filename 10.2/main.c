#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Описание структуры города
struct City {
    char name[50];  // Название города
    int population;
    struct City *next; // указатель на следующий элемент списка
};

// Размер хэш-таблицы (можно выбрать любое другое простое число)
#define TABLE_SIZE 1009

// Хэш-функция для названия города
unsigned int hash(char *name) {
    unsigned int h = 0;
    for (int i = 0; name[i]; i++)
        h = (h * 31 + name[i]) % TABLE_SIZE;
    return h;
}

// Каждый элемент хэш-таблицы - указатель на первый элемент списка городов
struct City* table[TABLE_SIZE];

// Функция добавления города в хэш-таблицу
void add(char *name, int population) {
    unsigned int h = hash(name);
    struct City *new_city = malloc(sizeof(struct City));
    strcpy(new_city->name, name);
    new_city->population = population;
    new_city->next = table[h];
    table[h] = new_city;
}

// Функция вывода списка всех городов
void list() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct City *curr = table[i];
        while (curr) {
            printf("%s: %d\n", curr->name, curr->population);
            curr = curr->next;
        }
    }
}

// Функция добавления города через терминал
void add_city() {
    char input[100];
    fgets(input, sizeof(input), stdin);
    char name[50];
    int population;
    if (sscanf(input, "%s %d", name, &population) != 2) {
        printf("Ошибка ввода\n");
        return;
    }
    add(name, population);
    printf("Город %s добавлен\n", name);
}

// Функция удаления города из хэш-таблицы
void remove_city(char *name) {
    unsigned int h = hash(name);
    struct City *prev = NULL;
    struct City *curr = table[h];
    while (curr) {
        if (strcmp(curr->name, name) == 0) { // если город найден
            if (prev) // если текущий элемент не первый в списке
                prev->next = curr->next;
            else // иначе изменяем указатель на первый элемент списка в таблице
                table[h] = curr->next;
            free(curr); // освобождаем память, занятую элементом списка
            printf("Город %s удален\n", name);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Город %s не найден\n", name);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int cmd;
    char name[50];
    do {
        printf("Меню программы:\n1. Список городов\n2. Добавить город(Пример: 2 Magadan 300000)\n3. Удалить город\n4. Выход\n");
        scanf("%d", &cmd);
        switch (cmd) {
            case 1:
                list();
                break;
            case 2:
                add_city();
                break;
            case 3:
                printf("Введите название города для удаления: ");
                scanf("%s", name);
                remove_city(name);
                break;
            case 4:
                printf("Выход\n");
                break;
            default:
                printf("Некорректный ввод, попробуйте еще раз\n");
        }
    } while (cmd != 4);

    return 0;
}

