/*Yicheng Kang
 * COEN 11
 * Lab 4
 * Wednesday 5:15pm
 */

#define SIZE 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef union extra_info {
	char phonenumber[20];
	int minage;
	float average;
} INFO;

typedef struct waitlist {
	char names[20];
	int groupsize;
	int maxage;
	INFO r_age;
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
//	RESSLOT *person = spots;
//	for(i=0; i<SIZE; i++, person++) {
//		person -> groupsize = 0;
//		person -> names[0] = '\0';
//	}
	
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
	//Only insert input if there are open slots
	if(size < SIZE) {
		char name[20];
		int maxage;
		int group;
		INFO extra;
		int i;
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
		
		printf("What is the maximum age in the group?\n");
		scanf("%d",&maxage);
		while(maxage<1) {
			printf("Use a real age please.\n");
			scanf("%d",&maxage);
		}
		if(maxage<18) {
			printf("Please enter the emergency contact of an adult.\n");
			scanf("%s", extra.phonenumber);
			strcpy(spots[size].r_age.phonenumber, extra.phonenumber);
		}
		else if(maxage>65) {
			printf("What is the minimum age in the group?\n");
			scanf("%d",&extra.minage);
			while(1>extra.minage || maxage<extra.minage) {
				printf("Enter a realistic minimum age please.\n");
				scanf("%d",&extra.minage);
			}
			spots[size].r_age.minage = extra.minage;
		}
		else {
			printf("What's the average age in the group?\n");
			scanf("%f",&extra.average);
			spots[size].r_age.average = extra.average;
		}

		//Increment counter and put name and group at end of list
		strcpy(spots[size].names,name);
		spots[size].groupsize = group;
		spots[size].maxage = maxage;
		size++;
		printf("You have successfully signed up on the waitlist.\n");
	}
	else
		printf("The waitlist is currently full, please try again later.\n");
	return;
}

//Check for duplicate names and let user know
int check_duplicate(char *str) {
	int i=0;
	while(i<size) {
		if(strcmp(str,spots[i].names)!=0) {
			i++;
		}
		else {
			printf("This name is already taken.\n");
			return 0;
		}
	}
	return 1;
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
		//Removes waitlist if enough spots available
		if(spotsleft >= spots[i].groupsize) {
			counter=1;
			printf("%s with groupsize %d has successfully made a reservation and removed from the waitlist.\n", spots[i].names, spots[i].groupsize);
			//Shifts the remaining spots up
			spotsleft -= spots[i].groupsize;
			for(j=i; j<size-1; j++) {
				spots[j] = spots[j+1];
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
	
	//Lists all spots with corresponding size
	for(i=0; i<size; i++) {
		printf("%s with a group of %d.\n", spots[i].names, spots[i].groupsize);
		if(spots[i].maxage<18) {
			printf("The oldest person is %d years old, with an emergency number as %s.\n", spots[i].maxage,spots[i].r_age.phonenumber);
		}
		else if(spots[i].maxage>65) {
			printf("The oldest person is %d years old and the youngest is %d years old.\n",spots[i].maxage,spots[i].r_age.minage);
		}
		else {
			printf("The oldest person is %d years old and the average age is %2.3f years old.\n",spots[i].maxage,spots[i].r_age.average);
		}
	}
}

void search_size(void) {
	int i;
	int answer;
	int x = (spots[i].groupsize);

	if(size == 0) {
		printf("The waitlist is empty right now.\n");
		return;
	}

	printf("What's the largest group size you'd like to see?\n");
	scanf("%d", &answer);

	//Outputs users with size less than or equal to inputted number
	for(i=0;i<size;i++) {
		if(spots[i].groupsize <= answer)
			printf("The number %d slot is waitlisted under %s with a size of %d.\n", i+1, spots[i].names, spots[i].groupsize);
	}
	if(x>answer)
		printf("There aren't any registered groups with this or under this size.\n");
	return;
}
