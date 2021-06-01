/*Yicheng Kang
 * COEN 11
 * Lab 7
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
} SLOT;

typedef struct waitlistgroup {
	SLOT person;
	SLOT *head;
	SLOT *tail;
} RESSLOT;

int size=0;

void read_all(char *filename);
void save_all(char *filename);
void insert(char *name, int group);
int check_duplicate(char *str);
void removewl(void);
void list(void);
void search_size(void);
void freeall(void);

RESSLOT wl[4];

int main(int argc, char  *argv[]) {
	char option;
	char name[20];
	int group;
	int i;
	printf("Welcome to My Surf Lessons!\n");
	if(argc==1) {
		printf("The name of the file is missing!\n");
		return 1;
	}
	read_all (argv[1]);
	while(1) {
		//Option Menu
		printf("1 - Add to waitlist\n2 - Remove a waitlist\n3 - Show the waitlist\n4 - Show waitlists under a group size\n0 - Exit\n\n");
		scanf(" %c", &option);
		switch(option) {
			case '1':
				//Insert waitlist
				printf("What's the name under?\n");
				scanf("%s",name);
				printf("What's the size of the group?\n");
				scanf("%d",&group);
				while(group<1) {
					printf("Please enter a reasonable group size.\n");
					scanf("%d", &group);
				}
				i = check_duplicate(name);
				if(i==0) {
					continue;
				}
				insert(name, group);
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
				if(argc==1) {
					save_all("init");
					printf("Waitlist has been saved.\n");
				}
				else {
					save_all(argv[1]);
					printf("Waitlist has been updated.\n");
				}
				freeall();
				return 0;
			default:
				printf("Not valid, please enter 1,2,3,4,or 0.\n");
		}
	}
}

void read_all(char *filename) {
	//file can open
	FILE *infp;
	if((infp=fopen(filename,"r"))==NULL) {
		printf("There was an error loading the file.\n");
		return;
	}
//	fseek(infp,35,SEEK_SET);
	char name[20];
	int i;
	int group;
	while(fscanf(infp,"%s%d", name, &group)==2) {
		i = check_duplicate(name);
		if(i==0) {
			continue;
		}
		insert(name, group);
	}
	printf("The file for the waiting list has been loaded.\n");
	list();
	fclose(infp);
	return;
}

void save_all(char *filename) {
	//file can open
	FILE *outfp;
	if((outfp = fopen(filename, "w"))==NULL) {
		printf("There was an error saving the file.\n");
		return;
	}
//	fprintf(outfp, "Name\tGroup Size\n--------------------\n");
	int i;
	SLOT *p;
	for(i = 0; i < 4; i++) {
		p=wl[i].head;
		while(p != NULL) {
			fprintf(outfp,"%s\t%d\n",p -> names, p -> groupsize);
			p = p -> next;
		}
	}
	fclose(outfp);
	return;
}
void insert(char *name, int group) {
	SLOT *p;
	if((p=(SLOT *)malloc(sizeof(SLOT))) == (SLOT *) NULL) {
		printf("Memory can't be allocated.\n");
		return;
	}
	int i;
		
	//Puts it into appropriate list
	i = (group < 7) ? (group-1)/2 : 3;

	//Links the structure and empties list
	if(wl[i].head == NULL) {
		wl[i].head = p;
		wl[i].tail = p;
	}
	else {
		wl[i].tail->next = p;
	}
	strcpy(p -> names, name);
	p -> groupsize=group;
	wl[i].tail = p;
	p->next = NULL;
	printf("You have successfully signed up on the waitlist.\n");
	return;
}

//Check for duplicate names and let user know
int check_duplicate(char *str) {
	SLOT *p;
	int i;
	for(i=0;i<4;i++) {
		p = wl[i].head;
		while(p != NULL) {
			if(strcmp(str, p -> names)==0) {
				printf("This name is already taken.\n");
				return 0;
			}
			p = p -> next;
		}
	}
	return 1;
}

void removewl(void) {
	
	int spotsleft;
	int counter=0;

	printf("How big was the size of your group?\n");
	scanf("%d", &spotsleft);
	
	SLOT *p;
	SLOT *q;
	int i;
	//Checks waitlist in order from smallest to largest
	for(i=0;i<4;i++) {
		switch(i) {
			case 0:
				if(spotsleft<1) {
					printf("No slots to remove.\n");
					return;
				}
				break;
			case 1:
				if(spotsleft<3) {
					printf("No slots to remove.\n");
					return;
				}
				break;
			case 2:
				if(spotsleft<5) {
					printf("No more slots to remove.\n");
					return;
				}
				break;
			case 3:
				if(spotsleft<7) {
					printf("No more slots to remove.\n");
					return;
				}
				break;
		}
		p=wl[i].head;
		q=wl[i].head;

		while(p!=NULL) {
			//Removes waitlist if enough spots available
			if(spotsleft >= p -> groupsize) {
				counter=1;
				printf("%s with groupsize %d has successfully made a reservation and removed from the waitlist.\n", p->names, p->groupsize);
				//Shifts the remaining spots up
				spotsleft -= p->groupsize;
				if(wl[i].head->next == NULL) {
					wl[i].head=NULL;
					wl[i].tail=NULL;
					free(p);
					break;
				}
				//first slot
				else if(wl[i].head==p) {
					wl[i].head=p->next;
					free(q);
					q=wl[i].head;
					p=q;
				}
				//last slot
				else if(wl[i].tail==p) {
					wl[i].tail=q;
					q->next=NULL;
					free(p);
					break;
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
	}
	return;

	if(counter == 0) {
		printf("This opening doesn't fit any group size on the waitlist.\n");
	}
}

void list(void) {
	int i,j;

	for(i=0;i<4;i++) {
		SLOT *p = wl[i].head;
		j=1;
		//Lists all spots with corresponding size
		while(p != NULL) {
			printf("In range %d the number %d slot: %s with a group of %d.\n", i, j, p->names, p->groupsize);
			j++;
			p=p->next;
		}
		printf("\n");
	}
	return;
}

void search_size(void) {
	SLOT *p;
	int i;
	int j=1;
	int answer;

	printf("What's the largest group size you'd like to see?\n");
	scanf("%d", &answer);
	
	for(i=0;i<4;i++) {
		if(wl[i].head == NULL) {
			printf("There's noone in range %d.\n", i);
		}
	}

	//Outputs users with size less than or equal to inputted number
	for(i=0;i<4;i++) {
		p=wl[i].head;
		while(p != NULL) {
			if(p -> groupsize <= answer) {
				printf("The number %d slot in range %d is waitlisted under %s with a size of %d.\n", j, i, p->names, p->groupsize);
			}
			j++;
			p = p->next;
		}
		switch(i) {
			case 0:
				if(answer < 3) {
					return;
				}
				break;
			case 1:
				if(answer < 5) {
					return;
				}
				break;
			case 2:
				if(answer < 7) {
					return;
				}
				break;
		}
	}
	return;
}

void freeall(void) {
	int i;
	SLOT *q, *p;
	
	for(i=0;i<4;i++) {
		p = wl[i].head;
		q = wl[i].head;
		while (p != NULL) {
			q = q -> next;
			free(p);
			p = q;
		}
	}
	return;
}
