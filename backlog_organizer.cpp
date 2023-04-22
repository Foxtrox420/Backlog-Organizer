#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct database{
	char name[150]; 
	char type[50]; 
	int status; 
	int price; 
	int year;  
	int qty; 
};

void printMenu(){
	printf("====Foxtrox Studios====\n"); 
	printf("1. Add New Entry (Needs Restart)\n"); 
	printf("2. Update Existing\n"); 
	printf("3. View List\n");
	printf("4. Exit\n"); 
	printf(">> "); 
}

void red () {
  printf("\033[1;31m");
}

void green(){
  printf("\033[0;32m");
}

void reset () {
  printf("\033[0m");
}

int main(){
	
	struct database Datas[500]; 
	
	char name[150], searchName[150], searchType[50], type[50];  
	int input, status, price, year, qty, n = 0, updateStatus, updatePrice; 
	char option1[2], option2[2]; 
	int size = sizeof(database), first = 0, count = 0, finished = 0, unfinished = 0; 
	

	FILE *read = fopen("data.txt", "r"); 
	if(read == NULL){
		printf("FILE NOT DETECTED!\n"); 
	}

	FILE *in = fopen("data.txt", "a"); 

	do{
		while(!feof(read)){
		fscanf(read, "%[^#]#%[^#]#%d#%d#%d\n", &Datas[n].name, &Datas[n].type, &Datas[n].status, &Datas[n].price, &Datas[n].year);
		n++;
		}
		system("cls");
		printMenu(); 
		scanf("%d", &input);
		switch(input){
			case 1 :
				system("cls"); 
				do{
					printf("Input Gunpla Type[HG|RG|MG|...]: "); scanf("%s", type); getchar(); 
					strcpy(Datas[size].type, type); 
				}while(strlen(type) > 5);
				do{
					printf("Input Gunpla Name[1...150]: "); scanf("%[^\n]", name); getchar(); 
					strcpy(Datas[size].name, name); 
				}while(strlen(name) > 150);
				do{
					printf("Input status [1 = finished, 0 = unfinished,] "); scanf("%d", &status); getchar(); 
					Datas[size].status = status; 
				}while(status > 1);
				do{
					printf("Input year bought [>2000]: "); scanf("%d", &year); getchar();
					Datas[size].year = year; 
				}while(year < 2000);
				do{
					printf("Input the price of the kit [Format (1 = 1,000 Rp)]: "); scanf("%d", &price); getchar();
					Datas[size].price = price; 
				}while(price < 0); 
				
				fprintf(in,"%s#%s#%d#%d#%d\n", Datas[size].name, Datas[size].type, Datas[size].status, Datas[size].price, Datas[size].year); 
				fclose(in); 
				printf("The program will stop shortly, please reset again\n"); 
				return 0; 
				break;
			case 2 :
				system("cls"); 
				printf("Insert the type/grade of the kit you want to update : "); scanf("%s", searchType); getchar();
				printf("Insert the entry you want to update : "); scanf("%[^\n]", searchName); getchar(); 
				for(int i = 0; i < n; i++){
					if(strcmp(Datas[i].name, searchName) == 0 && strcmp(Datas[i].type, searchType) == 0){
						printf("\n__DATA HAS BEEN FOUND !__\n");
						printf("Do you want to change the price[y|n]? ");  scanf("%s", option1); getchar(); 
						if(strcmp(option1, "y") == 0){
							printf("Insert new price : "); scanf("%d", &updatePrice); getchar(); 
							Datas[i].price = updatePrice;
							fclose(in);  
						}
						printf("Do you want to change the build status[y|n]? "); scanf("%s", option2); getchar();
						if(strcmp(option2, "y") == 0){
							printf("Data has been found, update status here : "); scanf("%d", &updateStatus); getchar();
							Datas[i].status = updateStatus; 
							fclose(in);
						} 
					}
				}
				break; 
			case 3 :
				system("cls"); 
				printf("===========================================================================================================\n");
				printf("| %-50s | %-10s | %-5s | %-5s  | %-20s |\n", "Gunpla Name", "Type/Grade", "Year", "Price", "Status");
				printf("===========================================================================================================\n");
				for(int i = 0; i < n; i++){
					if(Datas[i].status == 1){
						green();
						printf("| %-50s | %-10s | %-5d | %-5dK | %-20s |\n",Datas[i].name, Datas[i].type, Datas[i].year, Datas[i].price, "Status = Finished");
						finished++;
					}
					else{
						red(); 
						printf("| %-50s | %-10s | %-5d | %-5dK | %-20s |\n",Datas[i].name, Datas[i].type, Datas[i].year, Datas[i].price, "Status = Unfinished");
						unfinished++; 
					}
					
					count += Datas[i].price; 
				}
				reset();
				printf("===========================================================================================================\n");
				printf("\n\n");
				printf("Total Kits  = [%d]\n", n); 
				printf("Total Price = [%d K]\n", count);
				printf("Finished Kits = [%d]\n", finished); 
				printf("Unfinished Kits = [%d]\n", unfinished); 
				printf("\n\n");
			break; 
		} 
		if(input == 3){
			printf("Press enter to continue...\n"); getchar(); getchar(); 	
		}
		else{
			printf("Press enter to continue...\n"); getchar(); 
		}
		size++; 
	}while(input != 4); 
	fclose(read); 
	
	return 0; 
}
