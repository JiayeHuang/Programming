#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cell_struct
{
	struct Cell_struct* next;
	struct Cell_struct* prev;
	char* word;
}Cell;

typedef struct
{
	struct Cell_struct* head;
	struct Cell_struct* tail;
}List;

/*append word to the list*/
List append(char* word, List l)
{
	Cell* s=malloc(sizeof(Cell));
	s->word=malloc(sizeof(char)*(strlen(word)+1));
	s->word=word;

	if(l.head==NULL){l.head=s;s->prev=NULL;s->next=NULL;l.tail=s;} //in case l is an empty list
	else{s->prev=l.tail;l.tail->next=s;s->next=NULL;l.tail=s;}
	return l;
}

/*print all the words in the list*/
void print_list(List l)
{
	Cell *tmp;
	tmp=l.head;
	while(tmp!=NULL)
	{
		printf("%s ",tmp->word);
		tmp=tmp->next;
	}
}

/*free the memory*/
void free_list(List l)
{
	Cell *del,*tmp;
	del=l.head;
	while(del!=NULL)
	{
		free(del->word);
		tmp=del->next;
		free(del);
		del=tmp;
	}
}

/*insert a new string into the sequence*/
List insert_before(char* find,char* new_word,List l)
{
	Cell *s=malloc(sizeof(Cell));
	s->word=malloc(sizeof(char)*(strlen(new_word)+1));
	s->word=new_word;

	Cell *seek;
	seek=l.head;
	while(seek!=NULL)
	{
		if(strcmp(find,seek->word)==0)
		{
			if(seek->prev==NULL)
			{
				s->prev=NULL;
				s->next=seek;
				seek->prev=s;
				l.head=s;
			}
			else
			{
				s->prev=seek->prev;
				s->next=seek;
				seek->prev->next=s;
				seek->prev=s;
			}
			break;
		}
		else {seek=seek->next;}
	}
	if(seek==NULL)
	{
		printf("The target word not found!Output the existing list!\n");
		free(s->word);free(s);
	}
	return l;
}

List insert_after(char* find,char* new_word,List l)
{
	Cell *s=malloc(sizeof(Cell));
	s->word=malloc(sizeof(char)*(strlen(new_word)+1));
	s->word=new_word;

	Cell *seek;
	seek=l.head;
	while(seek!=NULL)
	{
		if(strcmp(find,seek->word)==0)
		{
			if(seek->next==NULL)
			{
				s->next=NULL;
				s->prev=seek;
				seek->next=s;
				l.tail=s;
			}
			else
			{
				s->prev=seek;
				s->next=seek->next;
				seek->next->prev=s;
				seek->next=s;
			}
			break;
		}
		else {seek=seek->next;}
	}
	if(seek==NULL)
	{
		printf("The target word not found!Output the existing list!\n");
		free(s->word);free(s);
	}
	return l;
}

/*reversing the order of the sequence*/
List reverse(List l)
{
	Cell *ffore,*fore,*cont;
	/*switch the pointer for the first cell*/
	cont=l.head;
	fore=cont->next;
	ffore=fore->next;

	cont->next=NULL;
	cont->prev=fore;
	fore->next=cont;
	l.tail=cont;
	/*switch the pointer for the cells in the middle*/
	cont=fore;
	fore=ffore;
	ffore=fore->next;

	while(ffore!=NULL)
	{
		cont->prev=fore;
		fore->next=cont;

		cont=fore;
		fore=ffore;
		ffore=fore->next;
	}
	/*switch the pointer for the last cell*/
	fore->next=cont;
	fore->prev=NULL;
	cont->prev=fore;
	l.head=fore;

	return l;
}

int main()
{
	/*Initialize the head and tail with NULL*/	
	List l;
	l.head=NULL;l.tail=NULL;
	
	printf("Initial the array and append a new word for it.\n");
	l=append("Hello world!",l);
	l=append("Ireland",l);
	print_list(l);
	
	printf("\n\nFind the word and insert new word before/after it.\n");
	l=insert_before("Ireland","Dublin",l);
	l=insert_after("Ireland","Trinity",l);
	print_list(l);

	printf("\n\nThe output when the word is not in the list.\n");
	l=insert_before("College","Dublin",l);
	l=insert_after("College","Dublin",l);
	print_list(l);

	printf("\n\nThe output of reversed l.\n");
	l=reverse(l);
	print_list(l);

	free_list(l);
	return 0;
}
