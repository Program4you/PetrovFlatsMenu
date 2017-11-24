#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// описание структуры
typedef struct flat_t {
	char address[19];
	double price;
	int rooms;
	char surname[14];
	char name[14];
	char patronymic[14];
} flat_t;

// добавлеине в базу новой квартиры
void add_flat(flat_t **flats, int *n, int *capacity) {
	if (*flats == NULL) {
		*flats = (flat_t *)malloc(sizeof(flat_t)); // если квартир ещё не было, то создаём 1 квартиру
		*capacity = 1;
	}
	else if (*n + 1 >= *capacity) {
		*capacity *= 2;
		*flats = (flat_t *)realloc(*flats, *capacity * sizeof(flat_t)); // иначе увеличиваем максимальный размер базы в два раза, если новая запись не вмещается
	}

	// вводим новую запись
	printf("Enter address: ");
	scanf("%s", (*flats)[*n].address);
	printf("Enter price: ");
	scanf("%lf", &(*flats)[*n].price);
	printf("Enter number of rooms: ");
	scanf("%d", &(*flats)[*n].rooms);
	printf("Enter surname: ");
	scanf("%s", (*flats)[*n].surname);
	printf("Enter name: ");
	scanf("%s", (*flats)[*n].name);
	printf("Enter patronymic: ");
	scanf("%s", (*flats)[*n].patronymic);

	(*n)++; // увеличиваем число элементов в массиве
}

// удаление квартиры из базы
void remove_flat(flat_t *flats, int *n) {
	if (!*n) {
		printf("No flats was added!\n");
		return;
	}

	flat_t flat; // создаём квартиру для поиска и удаления

	printf("Enter address: ");
	scanf("%s", flat.address);
	printf("Enter price: ");
	scanf("%lf", &flat.price);
	printf("Enter number of rooms: ");
	scanf("%d", &flat.rooms);
	printf("Enter surname: ");
	scanf("%s", flat.surname);
	printf("Enter name: ");
	scanf("%s", flat.name);
	printf("Enter patronymic: ");
	scanf("%s", flat.patronymic);
	int count = 0; // количество найденных квартир

	for (int i = 0; i < *n; i++) {
		if (!strcmp(flat.address, flats[i].address) && flat.price == flats[i].price && flat.rooms == flats[i].rooms &&
			!strcmp(flat.surname, flats[i].surname) && !strcmp(flat.name, flats[i].name) && !strcmp(flat.patronymic, flats[i].patronymic)) { // если нашли квартиру в базе
			(*n)--; // уменьшаем число квартир в базе
			count++; // количество удалённых

			for (int j = i; j < *n; j++)
				flats[j] = flats[j + 1]; // сдвигаем элементы влево на 1
		}
	}

	// выводим нужное сообщение
	if (count == 0)
		printf("No flats found in database...\n");
	else
		printf("Removed\n");
}

// вывод базы, отсортированной по адресу по алфавиту
void print_by_address(flat_t *flats, int n) {
	if (!n) {
		printf("No flats was added!\n");
		return;
	}
	
	// сортировка
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (strcmp(flats[j].address, flats[j + 1].address) > 0) {
				flat_t tmp = flats[j];
				flats[j] = flats[j + 1];
				flats[j + 1] = tmp;
			}
		}
	}

	printf("\n\n");
	printf("+--------------------------------------------------------------------------------------+\n");
	printf("|                            Flats after sorting by address                            |\n");
	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");
	printf("|      Address      | Price | Rooms |     Surname    |      Name      |   Patronymic   |\n");
	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");

	for (int i = 0; i < n; i++)
		printf("| %17s | %5.2lf | %5d | %14s | %14s | %14s |\n", flats[i].address, flats[i].price, flats[i].rooms, flats[i].surname, flats[i].name, flats[i].patronymic);

	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");
}

// вывод базы отсортированной по цене по убыванию
void print_by_price(flat_t *flats, int n) {
	if (!n) {
		printf("No flats was added!\n");
		return;
	}

	// сортировка
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (flats[j].price < flats[j + 1].price) {
				flat_t tmp = flats[j];
				flats[j] = flats[j + 1];
				flats[j + 1] = tmp;
			}
		}
	}

	printf("\n\n");
	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");
	printf("|                             Flats after sorting by price                             |\n");
	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");
	printf("|      Address      | Price | Rooms |     Surname    |      Name      |   Patronymic   |\n");
	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");

	for (int i = 0; i < n; i++)
		printf("| %17s | %5.2lf | %5d | %14s | %14s | %14s |\n", flats[i].address, flats[i].price, flats[i].rooms, flats[i].surname, flats[i].name, flats[i].patronymic);

	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");
}

// поиск по имени
void find_by_name(flat_t *flats, int n) {
	if (!n) {
		printf("No flats was added!\n");
		return;
	}

	char name[14];
	printf("Enter part of name: ");
	scanf("%s", name); // вводим имя (или его часть)
	int count = 0; // число найденных

	printf("\n\n");
	printf("+--------------------------------------------------------------------------------------+\n");
	printf("|                                 Search flat by name                                  |\n");
	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");
	printf("|      Address      | Price | Rooms |     Surname    |      Name      |   Patronymic   |\n");
	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");

	for (int i = 0; i < n; i++) {
		if (strstr(flats[i].name, name)) { // если такая подстрока есть в имени
			printf("| %17s | %5.2lf | %5d | %14s | %14s | %14s |\n", flats[i].address, flats[i].price, flats[i].rooms, flats[i].surname, flats[i].name, flats[i].patronymic);
			count++; // то выводим квартиру и увеличиваем счётчик выведенных
		}
	}

	if (count == 0) // если ничего не нашли, выводим сообщение об этом
		printf("|                                    No flats found                                    |\n");

	printf("+-------------------+-------+-------+----------------+----------------+----------------+\n");
}

int main() {
	int exit = 0;
	flat_t *flats = NULL;
	int n = 0;
	int capacity = 1;

	do {
		system("cls");
		printf("What do you want to do?\n");
		printf("1: Add flat\n");
		printf("2: Remove flat\n");
		printf("3: Print by address\n");
		printf("4: Print by price\n");
		printf("5: Find by name\n");
		printf("6: Exit\n");
		printf(">");
		
		char buf[256];
		int variant;
		scanf("%s", buf);

		while (sscanf(buf, "%d", &variant) != 1 || variant < 1 || variant > 6) {
			printf("Incorrect variant. Try again: ");
			scanf("%s", buf);
		}

		switch (variant) {
		case 1:
			add_flat(&flats, &n, &capacity);
			break;

		case 2:
			remove_flat(flats, &n);
			break;

		case 3:
			print_by_address(flats, n);
			break;

		case 4:
			print_by_price(flats, n);
			break;

		case 5:
			find_by_name(flats, n);
			break;

		case 6: 
			exit = 1;
			break;
		}

		if (!exit) {
			printf("\nPress enter to back to menu: ");
			getchar();
			getchar();
		}			
	} while (!exit);

    return 0;
}

