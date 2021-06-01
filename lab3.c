/*Yicheng Kang
 * COEN 11
 * Lab 3
 * Wednesday 5:15pm
 */

#define SIZE 10
#define LENGTH 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct waitlist {
	char names[LENGTH];
	int groupsize;
} RESSLOT;

RESSLOT spots[SIZE];
int size = 0;

void insert(void);
int check_duplicate(char *str);
void removewl(void);
void list(void);
void search_size(void);

int main(void) {
	char option;
	int i;
	RESSLOT *person = spots;
	for(i=0; i<SIZE; i++, person++) {
		person -> groupsize = 0;
		person -> names[0] = '\0';
	}
	
	printf("Welcome to My Surf Lessons!\n");
	while(1) {
		//Option Menu
		printf("1 - Add to waitlist\n2 - Remove a waitlist\n3 - Show the waitlist\n4 - Show waitlists under a group size\n0 - Exit\n\n");
		scanf(" %c", &option);
		switch(option) {
			case '1':
				//Insert waitlist
				insert();
				break;
			case '2':
				//Remove a waitlist
				removewl();
				break;
			case '3':
				//List the waitlist
				list();
				break;
			case '4':
				//List groups smaller than or equal to a size
				search_size();
				break;
			case '0':
				//End program
				return 0;
			default:
				printf("Not valid, please enter 1,2,3,4,or 0.\n");
		}
	}
}

void insert(void) {
	RESSLOT *person = spots;
	//Only insert input if there are open slots
	if(size < SIZE) {
		char name[LENGTH];
		int i = 0;
		int group;
		printf("What is the name under?\n");
		scanf("%s", &name);

		i = check_duplicate(name);
		if(i==0)
			return;
		
		printf("What is the size of the group?\n");
		scanf("%d", &group);
		while(group<1) {
			printf("Please enter a reasonable group size.\n");
			scanf("%d", &group);
		}

		//Increment counter and put name and group at end of list
		person += size;
		strcpy(person -> names, name);
		person -> groupsize=group;
		size++;
		printf("You have successfully signed up on the waitlist.\n");
	}
	else
		printf("The waitlist is currently full, please try again later.\n");
	return;
}

//Check for duplicate names and let user know
int check_duplicate(char *str) {
	RESSLOT *person = spots;
	int i=0;
	while(i<size) {
		if(strcmp(str, person -> names)!=0) {
			i++, person++;
		}
		else {
			printf("This name is already taken.\n");
			return 0;
		}
	}
	return 1;
}

void removewl(void) {
	RESSLOT *person = spots;
	RESSLOT *person2 = spots;
	int i;
	int j;
	int spotsleft;
	int counter=0;
	
	if(size == 0) {
		printf("The waitlist is empty.\n");
		return;
	}

	printf("How big was the size of your group?\n");
	scanf("%d", &spotsleft);

	for(i=0; i<size; i++, person++) {
		//Removes waitlist if enough spots available
		if(spotsleft >= person -> groupsize) {
			counter=1;
			printf("%s with groupsize %d has successfully made a reservation and removed from the waitlist.\n", person->names, person->groupsize);
			//Shifts the remaining spots up
			spotsleft -= person->groupsize;
			for(j=i; j<size-1; j++) {
				person[j] = person2[j+1];
			}
			i--, person--;
			size--;
		}
		
	}
	if(counter == 0) {
		printf("This opening doesn't fit any group size on the waitlist.\n");
	}
}

void list(void) {
	RESSLOT *person = spots;
	int i;
	if (size == 0) {
		printf("There aren't any lessons at the moment.\n");
		return;
	}
	
	//Lists all spots with corresponding size
	for(i=0; i<size; i++,person++) {
		printf("%s with a group of %d.\n", person->names, person->groupsize);
	}
}

void search_size(void) {
	RESSLOT *person = spots;
	int i;
	int answer;
	int x = (person -> groupsize);

	if(size == 0) {
		printf("The waitlist is empty right now.\n");
		return;
	}

	printf("What's the largest group size you'd like to see?\n");
	scanf("%d", &answer);

	//Outputs users with size less than or equal to inputted number
	for(i=0;i<size;i++,person++) {
		if(person -> groupsize <= answer)
			printf("The number %d slot is waitlisted under %s with a size of %d.\n", i+1, person->names, person->groupsize);
	}
	if(x>answer)
		printf("There aren't any registered groups with this or under this size.\n");
	return;
}
