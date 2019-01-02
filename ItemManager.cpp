// ItemManager.cpp : Defines	 the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define NAMELEN		6
#define USERNAME	"Tom"
#define PASSWORD	"a123"

typedef struct item_info{
	char item_code[NAMELEN];
	float price;
	int remain_num;
	struct item_info *next;
}ITEM_INFO;

ITEM_INFO *header;
int valid();
int login();
void show();
void insert(char code[], float price, int remain_num);
void deleted(char code[]);
void search(char code[]);
void purchase(char code[]);
void exit();
int menu();

int valid(char pwd[NAMELEN]){

	int i;
	int ascii;

	if(strcmp(pwd, "") == 0){
		printf("password can't be empty.\n");
		return 0;
	}

	for(i = 0; i < NAMELEN; i ++ ){
		ascii = pwd[i];
		if(ascii <= 0){
			break;
		}

		if((ascii >=48 && ascii <= 57) 
			|| (ascii >= 65 && ascii <= 90) 
			|| (ascii >= 97 && ascii <= 122)){
			return 1;
		} else {
			printf("Only use letters and digits.\n");
			return 0;
		}
	}

}

int login(){
	char user[NAMELEN], pwd[NAMELEN];
	printf("Need login, please input user and password\n");
	printf("User:");
	gets(user);
	printf("Password:");
	gets(pwd);

	if(valid(pwd)){
		if(strcmp(USERNAME, user) == 0 && strcmp(PASSWORD, pwd) == 0){
			printf("Login successfully.\n");
			return 1;
		} else {
			printf("Username or password error, Login fail.\n");
			return 0;
		}
	} else {
		return 0;
	}

}

void show(){	
	ITEM_INFO *ptr = header->next;
	if(header->next == NULL){
		printf("Empty list!\n");
		return;
	}
	
	printf("====================== Item Info =====================\n");
	printf("ItemCode\tPrice\tRemaining\n");	
	
	while(1){
		printf("%s\t\t%.2f\t\t%d\n", ptr->item_code, ptr->price, ptr->remain_num);
		if(ptr->next == NULL){
			break;
		} else {
			ptr = ptr->next;
		}
	}
}

void insert(char code[], float price, int remain_num){
	ITEM_INFO *item = ((struct item_info *)malloc(sizeof(struct item_info)));;
	strcpy(item->item_code, code);
	item->price = price;
	item->remain_num = remain_num;
	item->next = NULL;
	printf("ItemCode\tPrice\tRemaining\n");
	printf("%s\t\t%.2f\t\t%d\n", item->item_code, item->price, item->remain_num);
	
	ITEM_INFO *ptr = NULL;
	ptr = header->next;
	header->next = NULL;
	item->next = ptr;
	header->next = item;
}

void deleted(char code[]){
	ITEM_INFO *prev = header;
	ITEM_INFO *next = header->next;
	if(header->next == NULL){
		printf("Empty list!\n");
		return;
	}

	while(1){
		if(strcmp(code, next->item_code) == 0){
			prev->next = next->next;
			break;
		}
		
		if(next->next == NULL){
			break;
		} else {
			prev = next;
			next = next->next;
		}
	}
}

void search(char code[]){
	ITEM_INFO *next = header->next;
	if(header->next == NULL){
		printf("Empty list!\n");
		return;
	}

	while(1){
		if(strcmp(code, next->item_code) == 0){
			printf("%s\t\t%.2f\t\t%d\n", next->item_code, next->price, next->remain_num);
			break;
		}
		
		if(next->next == NULL){
			break;
		} else {
			next = next->next;
		}
	}
}

void purchase(char code[]){
	ITEM_INFO *next = header->next;
	if(header->next == NULL){
		printf("Empty list!\n");
		return;
	}

	while(1){
		if(strcmp(code, next->item_code) == 0){
			next->remain_num --;
			break;
		}
		
		if(next->next == NULL){
			break;
		} else {
			next = next->next;
		}
	}
}

void exit(){
}

int menu(){
	int choose, remain_num;
	float price;
	char code[NAMELEN];

	printf("====================== Main Menu =====================\n");
	printf("\t\t1.Show Current Item\n");
	printf("\t\t2.Insert Item\n");
	printf("\t\t3.Delete Item\n");
	printf("\t\t4.Search Item\n");
	printf("\t\t5.Purchase Item\n");
	printf("\t\t6.Exit the program\n\n");
	printf("Please input your choose:");
	scanf("%d",&choose); 
	switch(choose){
		case 1:		
			printf("Show Current Item\n");
			show();
			break;
		case 2:
			printf("Insert Item\n");
			printf("Please input item code:");
			scanf("%s", &code);
			printf("Please input price:");
			scanf("%f",&price);
			printf("Please input remain num:");
			scanf("%d",&remain_num);
			insert(code, price, remain_num);
			break;
		case 3:
			printf("Delete Item\n");
			printf("Please input delete item code:");
			scanf("%s", &code);
			deleted(code);
			break;
		case 4:
			printf("Search Item\n");
			printf("Please input search item code:");
			scanf("%s", &code);
			search(code);	
			break;
		case 5:
			printf("Purchase Item\n");
			printf("Please input purchase item code:");
			scanf("%s", &code);
			purchase(code);
			break;
		case 6:
			printf("Exit the pargram\n");
			exit();
		default:
			return 0;
	}
	return 1;
}


int main(int argc, char* argv[]){

	header = ((struct item_info *)malloc(sizeof(struct item_info)));
	header->next = NULL;
	printf("======================= Welcome =======================\n");
	if(login()){
		while(1){
			if(menu() == 0){
				return 0;				
			}
		}
		
	} else {
		return 0;
	}	
}
