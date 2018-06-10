#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



struct message
{
	char* content;
	char* receiver;
	uint32_t size;
	uint32_t id;
};

typedef struct message* mptr;

struct note
{
	unsigned int size;
	char* name;
	char* content;

};
typedef struct note* nptr;

mptr m;
nptr n;

void menu()
{
	printf("Menu\n");
	printf("1.Create Message\n");
	printf("2.Read Message\n");
	printf("3.Remove Receiver\n");
	printf("4.Edit Message\n");
	printf("5.Create Note\n");
	printf("6.Edit Note's Name\n");
	printf("7.Read Note\n");
	printf("8.Exit\n");
}

int create_message()
{
	unsigned int size =0 ;
    if(m)
    	return -1;

	m = malloc(sizeof(struct message));
	if(!m)
		exit(0);

	m->id = -1;
	m->receiver = malloc(0x28);
	if(!m->receiver)
		exit(0);
	puts("Input receiver's name:");
	read_str(m->receiver,0x28);

	puts("Input size:");
	scanf("%u",&m->size);

    m->content = malloc(m->size);
	if(!m->content)
		exit(0);
	puts("Input content:");
	read_str(m->content,m->size);

	return 0;
}




int remove_receiver()
{
	if(!m)
    	return -1;

	if(m->receiver)
	{
		free(m->receiver);
		m->receiver = 0;
	}
}



int edit_message()
{
	if(!m)
    	return -1;

    puts("Input id:");
  	read(0,&m->id,strlen(&m->id));

	if(m->receiver)
	{
		puts("Input receiver's name:");
		read_str(m->receiver,0x28);
	}
	puts("Input content:");
	read_str(m->content,m->size);
	
}


int read_message()
{
	if(!m)
    	return -1;

    printf("Id :%s\n",m->id);
    if(m->receiver)
    	printf("Receiver :%s\n",m->receiver);
	printf("Content :%s\n",m->content);
}


int read_note()
{
	if(!n)
    	return -1;

    printf("Name :%s\n",n->name);
	printf("Content :%s\n",n->content);
}

void read_str(char* buffer,unsigned int size)
{
	unsigned int n = read(0,buffer,size);
	if(buffer[n - 1] == '\n')
		buffer[n - 1] = '\x00';
}

int create_note()
{
	unsigned int size = 0 ;
	if(!n)
		n = malloc(sizeof(struct note));
	if(!n)
		exit(0);

	puts("Input name's size:");
	scanf("%u",&n->size);

	n->name = malloc(n->size);
	if(!n->name)
		exit(0);

	puts("Input name:");
	read_str(n->name,n->size);

	puts("Input content's size:");
	scanf("%u",&size);

	n->content = malloc(size);
	if(!n->content)
		exit(0);

	puts("Input content:");
	read_str(n->content,size);

	return 0;
}

void edit_name()
{
	if(!n)
    	return -1;

	puts("Input name:");
	read_str(n->name,n->size);

}



int main()
{
	int choice = 0;
	while(1)
	{
		menu();
		scanf("%i",&choice);
		switch(choice)
		{
			case 1:
				create_message();
				break;
			case 2:
				read_message();
				break;
			case 3:
				remove_receiver();
				break;
			case 4:
				edit_message();
				break;
			case 5:
				create_note();
				break;
			case 6:
				edit_name();
				break;
			case 7:
				read_note();
				break;
			case 8:
				puts("See you next time.");
				return 0;
			default:
				puts("Invalid choice");
				break;

		}
	}
	return 0;
}