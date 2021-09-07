#include <stdio.h>

typedef struct Book_ *Book;

struct Book_ {
	int copies;
	int price;
};

int main() {

	printf("test\n");
	struct Book_ book1;
	book1.copies = 100;
	book1.price = 25;

	Book newBook = &book1;
	// struct Book_ book1;
	// book1.copies = 100;
	// book1.price = 25;




	printf("test\n");

	printf("%d\n", newBook->price);
	printf("%d\n", newBook->copies);

}