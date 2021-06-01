/*Yicheng Kang
 * COEN 11
 * Lab 2
 * Wednesday 5:15pm
 */

#define SIZE 10
#define LENGTH 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char names[SIZE][LENGTH];
int groupsize[SIZE];
int size = 0;

void insert(void);
void removewl(void);
void list(void);

int main(void) {
	int option;
	int i;
	
	printf("Welcome to My Surf Lessons!\n");
	while(1) {
		printf("1 - Add to waitlist\n2 - Remove a waitlist\n3 - Show the waitlist\n0 - Exit\n\n");
		scanf("%d", &option);
		switch(option) {
			case 1:
				insert();
				break;
			case 2:
				removewl();
				break;
			case 3:
				list();
				break;
			case 0:
				return 0;
			default:
				printf("Not valid, please enter 1,2,3,or 0.\n");
		}
	}
}

void insert(void) {
	if(size < SIZE) {
		char name[LENGTH];
		int i = 0;
		int group;
		printf("What is the name under?\n");
		scanf("%s", &name);
		while(i < size) {
			if(strcmp(name,names[i])!=0) {
				i++;
			}
			else {
				printf("Sorry, that name was already taken.\n");
				return;
			}
		}
		printf("What is the size of the group?\n");
		scanf("%d", &group);
		while(group<1) {
			printf("Please enter a reasonable group size.\n");
			scanf("%d", &group);
		}
		strcpy(names[size], name);
		groupsize[size] = group;
		size++;
		printf("You have successfully signed up on the waitlist.\n");
	}
	else
		printf("The waitlist is currently full, please try again later.\n");
	return;
}

void removewl(void) {
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

	for(i=0; i<size; i++) {
		if(spotsleft >= groupsize[i]) {
			counter=1;
			printf("%s with groupsize %d has successfully made a reservation and removed from the waitlist.\n", names[i], groupsize[i]);
			spotsleft -= groupsize[i];
			for(j=i; j<size; j++) {
				strcpy(names[j], names[j+1]);
				groupsize[j] = groupsize[j+1];
			}
			i--;
			size--;
		}
		
	}
	if(counter == 0) {
		printf("This opening doesn't fit any group size on the waitlist.\n");
	}
}

void list(void) {
	int i;
	if (size == 0) {
		printf("There aren't any lessons at the moment.\n");
		return;
	}

	for(i=0; i<size; i++) {
		printf("%s with a group of %d.\n", names[i], groupsize[i]);
	}
}
