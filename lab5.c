/*Yicheng Kang
 * COEN 11
 * Lab 5
 * Wednesday 5:15pm
 */

#define SIZE 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct waitlist {
	char names[20];
	int groupsize;
	struct waitlist *next;
} RESSLOT;

int size=0;

void insert(void);
int check_duplicate(char *str);
void removewl(void);
void list(void);
void search_size(void);

RESSLOT *head = NULL;
RESSLOT *tail = NULL;

int main(void) {
	char option;
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
	RESSLOT *p;
	if((p=(RESSLOT *)malloc(sizeof(RESSLOT))) == (RESSLOT *) NULL) {
		printf("Memory can't be allocated.\n");
		return;
	}
	char name[20];
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

	//Links the structure and empties list
	if(head == NULL) {
		head = p;
		tail = p;
	}
	else {
		tail->next = p;
	}
	strcpy(p -> names, name);
	p -> groupsize=group;
	tail = p;
	p->next = NULL;
	printf("You have successfully signed up on the waitlist.\n");
	return;
}

//Check for duplicate names and let user know
int check_duplicate(char *str) {
	RESSLOT *p = head;
	while(p != NULL) {
		if(strcmp(str, p -> names)!=0) {
			p = p->next;
		}
		else {
			printf("This name is already taken.\n");
			return 0;
		}
	}
	return 1;
}

void removewl(void) {
	if(head == NULL) {
		printf("There are currently no spots to remove.\n");
		return;
	}
	int spotsleft;
	int counter=0;

	printf("How big was the size of your group?\n");
	scanf("%d", &spotsleft);
	
	RESSLOT *p=head;
	RESSLOT *q=head;
	while(p!=NULL) {
		//Removes waitlist if enough spots available
		if(spotsleft >= p -> groupsize) {
			counter=1;
			printf("%s with groupsize %d has successfully made a reservation and removed from the waitlist.\n", p->names, p->groupsize);
			//Shifts the remaining spots up
			spotsleft -= p->groupsize;
			if(head->next == NULL) {
				head=NULL;
				tail=NULL;
				free(p);
				return;
			}
			//first slot
			else if(head==p) {
			head=p->next;
			free(q);
			q=head;
			p=head;
			}
			//last slot
			else if(tail==p) {
				tail=q;
				q->next=NULL;
				free(p);
				return;
			}
			//slots in the middle
			else {
				q->next = p->next;
				free(p);
				p=q->next;
			}
		}
		else {
			q=p;
			p=p->next;
		}
	}

	if(counter == 0) {
		printf("This opening doesn't fit any group size on the waitlist.\n");
	}
}

void list(void) {
	RESSLOT *p = head;
	int i=1;
	if (p==NULL) {
		printf("There aren't any lessons at the moment.\n");
	}
	
	//Lists all spots with corresponding size
	while(p != NULL) {
		printf("The number %d slot: %s with a group of %d.\n", i, p->names, p->groupsize);
		i++;
		p=p->next;
	}
	printf("\n");
	return;
}

void search_size(void) {
	RESSLOT *p = head;
	int i=1;
	int answer;
	int x = (p -> groupsize);

	printf("What's the largest group size you'd like to see?\n");
	scanf("%d", &answer);

	//Outputs users with size less than or equal to inputted number
	while(p != NULL) {
		if(p -> groupsize <= answer)
			printf("The number %d slot is waitlisted under %s with a size of %d.\n", i, p->names, p->groupsize);
		i++;
		p = p->next;
	}
	if(x>answer)
		printf("There aren't any registered groups with this or under this size.\n");
	return;
}
