#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

struct passport{
  char surname[50];
  char name[50];
  char last_name[50];
  char gender[20];
  char date_of_born[20];
  char numberID[20];
  int cnt_children;
  int* ID_children;  
} peoples;

void PrintInfo(struct passport peoples[], int count) {
  for (int i = 0; i < count; i++) {
    printf("-------------------------\n");
    printf("Person %d\n", i);
    printf("FIO %s %s %s\n", peoples[i].surname, peoples[i].name, peoples[i].last_name);
    printf("gender %s\n", peoples[i].gender);
    printf("date of born %s\n", peoples[i].date_of_born);
    printf("ID  %s\n", peoples[i].numberID);
    printf("ID childrens: ");
    for (int j = 0; j < peoples[i].cnt_children; j++) {
      printf("%u ", (unsigned int)peoples[i].ID_children[j]);
    }
    printf("\n");

    free(peoples[i].ID_children);
  }
}
void ReadingFromFile(char* filename, struct passport* peoples, int count) {
    FILE* file;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
    }
    for (int i = 0; i < count; i++) {
        fgets(peoples[i].surname, sizeof(peoples[i].surname), file);
        peoples[i].surname[strcspn(peoples[i].surname, "\n")] = '\0';

        fgets(peoples[i].name, sizeof(peoples[i].name), file);
        peoples[i].name[strcspn(peoples[i].name, "\n")] = '\0';

        fgets(peoples[i].last_name, sizeof(peoples[i].last_name), file);
        peoples[i].last_name[strcspn(peoples[i].last_name, "\n")] = '\0';

        fgets(peoples[i].gender, sizeof(peoples[i].gender), file);
        peoples[i].gender[strcspn(peoples[i].gender, "\n")] = '\0';

        fgets(peoples[i].date_of_born, sizeof(peoples[i].date_of_born), file);
        peoples[i].date_of_born[strcspn(peoples[i].date_of_born, "\n")] = '\0';

        fgets(peoples[i].numberID, sizeof(peoples[i].numberID), file);
        peoples[i].numberID[strcspn(peoples[i].numberID, "\n")] = '\0';

        fscanf(file, "%d", &peoples[i].cnt_children);

        // Изменение конструкции чтения 
        peoples[i].ID_children = malloc(sizeof(int) * peoples[i].cnt_children);
        for (int j = 0; j < peoples[i].cnt_children; j++) {
            fscanf(file, "%d", &peoples[i].ID_children[j]);
        }
        fgetc(file);
    }

    fclose(file);
}
void EnterStruct(struct passport peoples[], int count){
	 int childrens;
  for (int i = 0; i < count; i++) {
    printf("Enter Surname %d person: \n", i+1);
    scanf("%s", peoples[i].surname);
    printf("Enter name %d person: \n", i+1);
    scanf("%s", peoples[i].name);
    printf("Enter last name %d person: \n", i+1);
    scanf("%s", peoples[i].last_name);
    printf("Enter gender %d person: \n", i+1);
    scanf("%s", peoples[i].gender);
    printf("Enter date of born %d person: \n", i+1);
    scanf("%s", peoples[i].date_of_born);
    printf("Enter ID %d people: \n", i+1);
    scanf("%s", peoples[i].numberID);
    int length = strlen(peoples[i].numberID);
    peoples[i].numberID[length] = '\0';
    printf("Enter count children %d person: \n", i+1);
    scanf("%d", &childrens);
    peoples[i].cnt_children = childrens;
    peoples[i].ID_children = (int*)malloc(sizeof(int) * childrens);
    for (int j = 0; j < childrens; j++) {
      printf("Enter id %d child for %d person: ", j+1, i+1);
      scanf("%d", &peoples[i].ID_children[j]);
    }
  }
}
void FindBornDate(struct passport peoples[], int count, char mas[]) {
	int found = 0;
    //printf("Enter date of birth (d/m/y):\n");
    //int len = strlen(mas);
    //printf("People born on this date:\n");
    for(int i = 0; i < count; i++) {
        if(strcmp(peoples[i].date_of_born, mas) == 0) {
            printf("%s %s %s\n", peoples[i].surname, peoples[i].name ,peoples[i].last_name);
            found = 1;
        }
    }
    if(!found){
		printf("Not found\n");
		}
}
void FindParents(struct passport people[], int count, const char id_children[]) {
    int temp[count];
    int index = 0;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < people[i].cnt_children; j++) {
            if (people[i].ID_children[j] == atoi(id_children)) {
                temp[index] = i;
                index++;
                FindParents(people,count,people[i].numberID);
            }
        }
    }
    if (index == 0) {
        printf("Child with ID %s not found.\n", id_children);
    } else {
        printf("Parents of child with ID %s:\n", id_children);
        for (int i = 0; i < index; i++) {
            printf("%s %s %s\n", people[temp[i]].surname, people[temp[i]].name, people[temp[i]].last_name);
        }
    }
}

void SurnameAll(struct passport peoples[], int count, char mas2[]);
int IsRelative(struct passport peoples[], int count, int index);
int IsParent(struct passport person1, struct passport person2);
int HaveCommonChildren(struct passport person1, struct passport person2);

void SurnameAll(struct passport peoples[], int count, char mas2[]) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(peoples[i].surname, mas2) == 0) {
            if (!IsRelative(peoples, count, i)) {
                printf("%s %s %s\n", peoples[i].surname, peoples[i].name, peoples[i].last_name);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Not found\n");
    }
}
int IsRelative(struct passport peoples[], int count, int index) {
    for (int i = 0; i < count; i++) {
        if (i != index &&
            (IsParent(peoples[i], peoples[index]) || HaveCommonChildren(peoples[i], peoples[index]))) {
            return 1;
        }
    }

    return 0;
}

int IsParent(struct passport person1, struct passport person2) {
    for (int i = 0; i < person2.cnt_children; i++) {
        if (person2.ID_children[i] == atoi(person1.numberID)) {
            return 1;
        }
    }

    return 0;
}

int HaveCommonChildren(struct passport person1, struct passport person2) {
    for (int i = 0; i < person1.cnt_children; i++) {
        for (int j = 0; j < person2.cnt_children; j++) {
            if (person1.ID_children[i] == person2.ID_children[j]) {
                return 1;
            }
        }
    }

    return 0;
}
	
int main() {
  setlocale(LC_ALL,"ru_RU.UTF-8");
  char* filename = "test.txt";
  int count = 0;
  printf("Enter count persons: ");
  scanf("%d", &count);
  struct passport *peoples = malloc(sizeof(struct passport)*count);
  ReadingFromFile(filename,peoples,count);
  //EnterStruct(peoples,count);
  char date[20];
  printf("Enter date:\n");
  scanf("%s",date);
  FindBornDate(peoples, count, date);
  char childID[20];
  printf("Enter child ID to find parents: ");
  scanf("%s", childID);
  FindParents(peoples, count, childID);
  char surname[20];
  printf("Enter surname:");
  scanf("%s", surname);
  SurnameAll(peoples,count,surname);
  
  PrintInfo(peoples,count);
  free(peoples);
  return 0;
}
