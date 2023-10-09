
#define _CRT_SECURE_NO_WARNINGS 1
#define bool int
#define false 0
#define true (!false)

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//Preprocessor Variable
#define SIZE 5


//Stucture template for data part of the linked list
struct data {
	char number[10];
	char name[20];
	char author[20];
	int year;
	bool loan;
	char customerName[20];
	int amountLoan;
};

struct data s;

//Stucture template for one node
struct LinearNode {
	struct data* element;
	struct LinearNode* next;
};


int countList = 0;//Amount books in list

//Methods
void addBooks();
void viewAllBooks();
void deleteBook(char* value);
void borrowBook(char* value);
void returnBook(char* value, char* cName);
int countAuthor(char* value);
int mostPopular();
int leastPopular();
bool duplicate(char* value, char* name);
void saveToFile(FILE* fp);
void getFromFile(FILE* fp);
void specificBook(char* value);

// Global Variables
struct LinearNode* front = NULL; //front of the list

struct LinearNode* last = NULL; //pointer to last node in the list - not used in this code

/**************MAIN FUNCTION*******************/
void main() {
	int choice;
	char borrow[10];
	char delete[10];
	char retreive[10];
	char cName[20];
	char view[10];
	char author[20];
	int count, popular, least, i;
	FILE* fp;

	struct data s;

	//Start menu and ask user menu choice
	if ((fp = fopen("book.dat", "rb")) == NULL) {
		printf("\nNo Books please add some to the lst");


	}
	else {
		printf("\nBooks found in list");
		getFromFile(fp);
		saveToFile(fp);

	}
	while (1) {
		do {

			printf("\n             Library Menu");
			printf("\n=======================================");
			printf("\n1. Add new book to library");
			printf("\n2. Borrow book");
			printf("\n3. Return book");
			printf("\n4. Delete book");
			printf("\n5. View all books");
			printf("\n6. View a specific book");
			printf("\n7. Most popular & least popular books");
			printf("\n8. Count authors books in library");
			printf("\n9. Exit system");
			scanf("\n%d", &choice);

			if (choice == 1) {

				addBooks();
			}
			else if (choice == 2) {

				printf("\n=======================================");
				printf("\n             Borrow Book");
				printf("\n=======================================");
				printf("\nPlease enter book identifier you wish to borrow: ");
				scanf("%s", &borrow);
				borrowBook(borrow);
			}
			else if (choice == 3) {
				printf("\n=======================================");
				printf("\n            Return Book");
				printf("\n=======================================");
				printf("\nPlease enter book identifier you wish to return: ");
				scanf("%s", &retreive);
				printf("\nPlease enter customer name: ");
				getchar();
				gets(cName);
				returnBook(retreive, cName);
			}
			else if (choice == 4) {
				printf("\n=======================================");
				printf("\n            Delete Book");
				printf("\n=======================================");
				printf("\nPlease enter book identifier you wish to delete: ");
				scanf("%s", &delete);
				deleteBook(delete);

			}
			else if (choice == 5) {
				viewAllBooks();

			}
			else if (choice == 6) {
				printf("\n=======================================");
				printf("\n            View specific Book");
				printf("\n=======================================");
				printf("\nPlease enter book identifier: ");
				scanf("%s", &view);
				specificBook(view);

			}
			else if (choice == 7) {
				printf("\n=======================================");
				printf("\n  Most popular & least popular books");
				printf("\n=======================================");
				if (isEmpty()) {
					printf("\nError - there are no books in the list\n");
				}
				else {
					popular = mostPopular();
					printf("\nThe most popular book has been loaned %d times.\n", popular);
					least = leastPopular();
					printf("\nThe least popular book has been loaned %d times.\n", least);
				}

			}
			else if (choice == 8) {
				//Personal feature counts how many books under a certain authors name are in the list
				printf("\n=======================================");
				printf("\n            Author Book Count");
				printf("\n=======================================");
				printf("\nPlease enter authors name: ");
				getchar();
				gets(&author);
				count = countAuthor(author);
				printf("\n%s has %d books in the library.\n", author, count);
			}
			else if (choice == 9) {
				saveToFile(fp);
				exit(0);

			}

			if (choice > 9 || choice < 1) {
				printf("\nInvalid Input, must be a input between 1 - 9");

			}
		} while (choice > 9 || choice < 1);

	}

}

/**********ADD NODES TO THE LIST******************/
// Each new node is added to the front of the front

void addBooks() {

	struct LinearNode* aNode;
	struct data* anElement;

	printf("\n=======================================");
	printf("\n             Add Book");
	printf("\n=======================================");

	do {
		printf("\nEnter book number: ");
		scanf("%s", &s.number);
		getchar();
		if (strlen(s.number) != 9 || (s.number[4] != '-') || !(s.number[0] <= '9') || !(s.number[0] >= '0') || !(s.number[1] <= '9') || !(s.number[1] >= '0') || !(s.number[2] <= '9') || !(s.number[2] >= '0') || !(s.number[3] <= '9') || !(s.number[3] >= '0') || !(s.number[5] <= '9') || !(s.number[5] >= '0') || !(s.number[6] <= '9') || !(s.number[6] >= '0') || !(s.number[7] <= '9') || !(s.number[7] >= '0') || !(s.number[8] <= '9') || !(s.number[8] >= '0')) {
			printf("Invalid Input, number must contain digits only and in form xxxx-xxxx\n");
		}

	} while (strlen(s.number) != 9 || (s.number[4] != '-') || !(s.number[0] <= '9') || !(s.number[0] >= '0') || !(s.number[1] <= '9') || !(s.number[1] >= '0') || !(s.number[2] <= '9') || !(s.number[2] >= '0') || !(s.number[3] <= '9') || !(s.number[3] >= '0') || !(s.number[5] <= '9') || !(s.number[5] >= '0') || !(s.number[6] <= '9') || !(s.number[6] >= '0') || !(s.number[7] <= '9') || !(s.number[7] >= '0') || !(s.number[8] <= '9') || !(s.number[8] >= '0'));

	printf("Enter name of book: ");
	gets(s.name);
	printf("Enter author of book: ");
	gets(s.author);

	do {
		printf("Enter publish year: ");
		scanf("%d", &s.year);
		if (s.year > 2017) {
			printf("Invalid Input, publish year can not be greater than 2017\n");
		}
	} while (s.year > 2017);

	if (duplicate(s.number, s.name) == true) {
		printf("Invalid Input, a book with this identifier or name already exists in the library\n");
	}
	else if (SIZE == countList) {
		printf("Error - book could not be added as the list is full\n");
	}
	else {
		//create space for new data element
		anElement = (struct data*)malloc(sizeof(struct data));
		// create space for new node
		aNode = (struct LinearNode*)malloc(sizeof(struct LinearNode));


		anElement->year = s.year;
		anElement->amountLoan = 0;
		anElement->loan = false;
		strcpy(anElement->number, s.number);
		strcpy(anElement->name, s.name);
		strcpy(anElement->author, s.author);
		strcpy(anElement->customerName, "");


		if (aNode == NULL)
			printf("Error - no space in list for book\n");

		else { // add data part to the node
			aNode->next = NULL;
			aNode->element = anElement;

			//add node to front of the node
			if (isEmpty())
			{
				front = aNode;
				last = aNode;
			}
			else {
				aNode->next = front;
				front = aNode;
			}
			countList += 1;
			printf("\nBook %s has been added to library\n", s.name);

		}

	}

}

//Method to display all details of all books in list
void viewAllBooks() {
	struct LinearNode* current;

	printf("\n=======================================");
	printf("\n           Display all Books");
	printf("\n=======================================");

	if (isEmpty())
		printf("\nError - there are no books in the list\n");
	else {
		current = front;
		while (current != NULL) {
			printf("\nBook number:%s", current->element->number);
			printf("\nAuthor:%s", current->element->author);
			printf("\nBook name:%s", current->element->name);
			printf("\nPublish year:%d", current->element->year);
			printf("\nCustomer Name:%s", current->element->customerName);
			printf("\nLoan status,0 = No/1 = Yes:%d", current->element->loan);
			printf("\nAmount of times loaned:%d", current->element->amountLoan);
			printf("\n=================================================");

			current = current->next;
		}
	}


}

//Method to delete a book passed as a parameter from the list
void deleteBook(char* value) {
	struct LinearNode* current, * previous;
	bool found = false;

	if (isEmpty())
		printf("\nError - there are no books in library\n");
	else {
		current = previous = front;

		while (!found && current != NULL) {
			if (strcmp(value, current->element->number) == 0)
				found = true;
			else {
				previous = current;
				current = current->next;
			}
		}

		if (!found)
			printf("\nError - there is no such book with identifier %s\n", value);
		else if (current->element->year < 2010) {
			printf("\nError - only books older than 2010 may be deleted");
		}
		else { //find out the position of the node to delete
			if (current == front) {
				front = front->next;
				free(current);
			}
			else if (current == last) {
				last = previous;
				last->next = NULL;
				free(current);
			}
			else { //delete an element in the middle of the list
				previous->next = current->next;
				free(current);
			}
			countList -= 1;
			printf("\nBook with identifier %s has been deleted from the list\n", value);
		}
	}
}

//Method to borrow book from list
void borrowBook(char* value) {
	struct LinearNode* current, * previous;
	bool found = false;
	struct data s;

	if (isEmpty())
		printf("\nError - there are no books in the list\n");
	else {
		current = previous = front;

		while (!found && current != NULL) {
			if (strcmp(value, current->element->number) == 0)
				found = true;
			else {
				previous = current;
				current = current->next;
			}
		}

		if (!found) {
			printf("\nError - there is no book with identifier %s\n", value);
		}
		else if (current->element->loan != false) {
			printf("\nError - this book is currently loaned\n");
		}
		else { //Search for element ton change loan status
			if (current == front) {
				current->element->loan = true;
				current->element->amountLoan++;
			}
			else if (current == last) {

				current->element->loan = true;
				current->element->amountLoan++;
			}
			else {

				current->element->loan = true;
				current->element->amountLoan++;

			}

			printf("\nInput customer name:");
			getchar();
			gets(s.customerName);
			printf("\nThe book %s has been loaned out", current->element->name);
			strcpy(current->element->customerName, s.customerName);

		}
	}
}

//Method to display details of a sepcific book passed as parameter
void specificBook(char* value) {
	struct LinearNode* current, * previous;
	bool found = false;
	struct data s;

	if (isEmpty())
		printf("\nError - there are no books in the list\n");
	else {
		current = previous = front;

		while (!found && current != NULL) {
			if (strcmp(value, current->element->number) == 0)
				found = true;
			else {
				previous = current;
				current = current->next;
			}
		}

		if (!found) {
			printf("\nError - there is no book with identifier %s\n", value);
		}

		else {
			if (current == front) {

				printf("\nBook number:%s", current->element->number);
				printf("\nAuthor:%s", current->element->author);
				printf("\nBook name:%s", current->element->name);
				printf("\nPublish year:%d", current->element->year);
				printf("\nCustomer Name:%s", current->element->customerName);
				printf("\nLoan status:%d", current->element->loan);
				printf("\nAmount of times loaned:%d", current->element->amountLoan);
				printf("\n=================================================");

			}
			else if (current == last) {

				printf("\nBook number:%s", current->element->number);
				printf("\nAuthor:%s", current->element->author);
				printf("\nBook name:%s", current->element->name);
				printf("\nPublish year:%d", current->element->year);
				printf("\nCustomer Name:%s", current->element->customerName);
				printf("\nLoan status:%d", current->element->loan);
				printf("\nAmount of times loaned:%d", current->element->amountLoan);
				printf("\n=================================================");
			}
			else {

				printf("\nBook number:%s", current->element->number);
				printf("\nAuthor:%s", current->element->author);
				printf("\nBook name:%s", current->element->name);
				printf("\nPublish year:%d", current->element->year);
				printf("\nCustomer Name:%s", current->element->customerName);
				printf("\nLoan status:%d", current->element->loan);
				printf("\nAmount of times loaned:%d", current->element->amountLoan);
				printf("\n=================================================");

			}

		}
	}

}
//Method to return a book to list and change its loan status
void returnBook(char* value, char* cName) {
	struct LinearNode* current, * previous;
	bool found = false;
	struct data s;

	if (isEmpty())
		printf("\nError - there are no books in the list\n");
	else {
		current = previous = front;

		while (!found && current != NULL) {
			if (strcmp(value, current->element->number) == 0 && strcmp(cName, current->element->customerName) == 0)
				found = true;
			else {
				previous = current;
				current = current->next;
			}
		}

		if (!found) {
			printf("\nError - there is no book with identifier %s\n", value);
		}
		else if (current->element->loan != true) {
			printf("\nError - this book is currently not on loan and is availaible to borrow\n");
		}
		else { //Search for element to change loan status & input customer name
			if (current == front) {
				current->element->loan = false;
				strcpy(current->element->customerName, "");

			}
			else if (current == last) {

				current->element->loan = false;
				strcpy(current->element->customerName, "");

			}
			else {

				current->element->loan = false;
				strcpy(current->element->customerName, "");


			}
			printf("\nThank you the book %s has been returned", current->element->name);

		}
	}
}

//Method which takes an authors name as a parameter and compares it other authors in the list if found it will return the number of books that author has in library
int countAuthor(char* value)
{
	int i, count = 0;


	for (struct LinearNode* current = front; current != NULL; current = current->next) {

		if (strcmp(value, current->element->author) == 0)
		{
			count += 1;
		}
	}
	return count;
}

//Returns most popular book as an integer based of amount of times loaned
int mostPopular() {
	struct LinearNode* current;
	int max = INT_MIN;
	current = front;

	while (current != NULL) {
		if (max < current->element->amountLoan)
			max = current->element->amountLoan;
		current = current->next;

	}
	return max;
}

//Returns least popular book as an integer based of amount of times loaned
int leastPopular() {
	struct LinearNode* current;
	int min = INT_MAX;
	current = front;


	while (current != NULL) {
		if (min > current->element->amountLoan)
			min = current->element->amountLoan;
		current = current->next;

	}

	return min;
}

//Checks if list is empty
bool isEmpty() {
	if (front == NULL)
		return true;
	else
		return false;
}

//Checks for duplicate books in list and returnds true if found
bool duplicate(char* value, char* name) {

	bool find = false;
	for (struct LinearNode* current = front; current != NULL; current = current->next) {
		if (strcmp(value, current->element->number) == 0 || strcmp(name, current->element->name) == 0) {
			find = true;
		}

	}
	return find;

}

/*
//Only 1 element from linked is saved to file
void saveToFile(FILE* fp) {
	fp = fopen("book.dat", "wb");
	struct LinearNode* aNode;
	int i;
	for (i = 0; i < SIZE; i++)
		fwrite(&s, sizeof(struct data), 1, fp);
	fclose(fp);
}
*/

void saveToFile() {
	FILE* fp = fopen("book.dat", "wb");
	if (fp == NULL) {
		printf("Error: failed to open file\n");
		return;
	}

	struct LinearNode* curr = front;
	while (curr != NULL) {
		fwrite(curr->element, sizeof(struct data), 1, fp);
		curr = curr->next;
	}

	fclose(fp);
}

void getFromFile() {
	FILE* fp = fopen("book.dat", "rb");
	if (fp == NULL) {
		printf("Error: failed to open file\n");
		return;
	}

	// create a new front node for the first data item in the file
	struct data s;
	if (fread(&s, sizeof(struct data), 1, fp) == 1) {
		struct data* anElement = malloc(sizeof(struct data));
		if (anElement == NULL) {
			printf("Error - no space in list for book\n");
			return;
		}
		anElement->year = s.year;
		anElement->loan = s.loan;
		anElement->amountLoan = s.amountLoan;
		strcpy(anElement->number, s.number);
		strcpy(anElement->name, s.name);
		strcpy(anElement->author, s.author);
		strcpy(anElement->customerName, s.customerName);

		struct LinearNode* aNode = malloc(sizeof(struct LinearNode));
		if (aNode == NULL) {
			printf("Error - no space in list for book\n");
			free(anElement);
			return;
		}
		aNode->element = anElement;
		aNode->next = NULL;
		front = aNode;
		last = aNode;
		countList++;
	}

	// read the remaining data items from the file and append to the list
	while (fread(&s, sizeof(struct data), 1, fp) == 1) {
		struct data* anElement = malloc(sizeof(struct data));
		if (anElement == NULL) {
			printf("Error - no space in list for book\n");
			break;
		}
		anElement->year = s.year;
		anElement->loan = s.loan;
		anElement->amountLoan = s.amountLoan;
		strcpy(anElement->number, s.number);
		strcpy(anElement->name, s.name);
		strcpy(anElement->author, s.author);
		strcpy(anElement->customerName, s.customerName);

		struct LinearNode* aNode = malloc(sizeof(struct LinearNode));
		if (aNode == NULL) {
			printf("Error - no space in list for book\n");
			free(anElement);
			break;
		}
		aNode->element = anElement;
		aNode->next = NULL;
		last->next = aNode;
		last = aNode;
		countList++;
	}

	fclose(fp);
}

/*

void getFromFile(FILE* fp) {
	struct LinearNode* aNode;

	struct data* anElement;
	printf("\nRetriving books from file...\n");
	fread(&s, sizeof(struct data), 1, fp);

		anElement = (struct data*)malloc(sizeof(struct data));
	aNode = (struct LinearNode*)malloc(sizeof(struct data));

	anElement->year = s.year;
	anElement->loan = s.loan;
	anElement->amountLoan = s.amountLoan;
	strcpy(anElement->number, s.number);
	strcpy(anElement->name, s.name);
	strcpy(anElement->author, s.author);
	strcpy(anElement->customerName, s.customerName);


	if (aNode == NULL)
		printf("Error - no space in list for book\n");

	else { // add data part to the node
		aNode->next = NULL;
		aNode->element = anElement;

		//add node to front of the node
		if (isEmpty())
		{
			front = aNode;
			last = aNode;
		}
		else {
			aNode->next = front;
			front = aNode;
		}

		countList += 1;


	}

	fclose(fp);
}
*/
