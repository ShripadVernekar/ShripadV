#include "A3_header_PES1201801932.h"
#include <stdio.h>
#include <stdlib.h>

void disp_state(const state_t * ptr_state)	//function to display each state
{
	printf("%d %d %d\n",ptr_state -> jugA,ptr_state -> jugB,ptr_state -> jugC);
}

void set_state(state_t * ptr_state,int jugA,int jugB,int jugC)	//function to set state for given values
{
	ptr_state -> jugA = jugA;
	ptr_state -> jugB = jugB;
	ptr_state -> jugC = jugC;
	ptr_state -> fn_index = 0;
}

void jugAtojugB(int A,int B,int C,const state_t * src,state_t * dest)	//to mov from A to B
{
	int required = B - src -> jugB; //calculate amount of water required to fill jugB litre
	if(required && src->jugA)	//checking for !=0
	{
		if(src -> jugA >= required) //check if we have sufficient amount of water in jugA litre jug to fill jugB liter
		{
			dest -> jugA = src -> jugA - required;
			dest -> jugB = src -> jugB + required;
			dest -> jugC = src -> jugC;
		}
		else
		{
			dest -> jugA = 0;
			dest -> jugB = src -> jugB + src -> jugA;
			dest -> jugC = src -> jugC;
		}
	}
	else
		dest->jugB=src->jugB+1;
	
	dest -> fn_index = 0;
}

void jugAtojugC(int A,int B,int C,const state_t * src,state_t * dest) //mov from A to C
{
	int required = C - src -> jugC;		//calculate amount of water required to fill jugC litre
	if(required && src->jugA)
	{
		if(src -> jugA >= required)		//check if we have sufficient amount of water in jugA litre jug to fill jugC liter
		{
			dest -> jugA = src -> jugA - required;
			dest -> jugB = src -> jugB;
			dest -> jugC = src -> jugC + required;
		}
		else{
			dest -> jugA = 0;
			dest -> jugB = src -> jugB;
			dest -> jugC = src -> jugC + src -> jugA;
		}
	}
	else
		dest->jugC	=	src->jugC+1;
	
	dest -> fn_index = 0;
}

void jugBtojugA(int A,int B,int C,const state_t * src,state_t * dest)	//mov from B to A 
{
	int required = A - src -> jugA;//calculate amount of water required to fill jugA litre
	if (required && src->jugB)
	{
		if(src -> jugB >= required)//check if we have sufficient amount of water in jugB litre jug to fill jugA litre
		{
			dest -> jugA = src -> jugA + required;
			dest -> jugB = src -> jugB - required;
			dest -> jugC = src -> jugC;
		
		}
		else{
			
			dest -> jugA = src -> jugA + src -> jugB;
			dest -> jugB = 0;
			dest -> jugC = src -> jugC;
		}
	}
	else{
		 if (is_valid(src->jugA,src->jugB,src->jugC,1,dest))
			dest->jugA=src->jugA+1;
	}
	dest -> fn_index = 0;
}

void jugBtojugC(int A,int B,int C,const state_t * src,state_t * dest)	//mov from B to C
{
	int required = C - src -> jugC;//calculate amount of water required to fill jugC litre
	if(required && src->jugB)
	{
		if(src -> jugB >= required)//check if we have sufficient amount of water in jugB litre jug to fill jugC litre
		{
			dest -> jugA = src -> jugA;
			dest -> jugB = src -> jugB - required;
			dest -> jugC = src -> jugC + required;
		}
		else{
			dest -> jugA = src -> jugA;
			dest -> jugB = 0;
			dest -> jugC = src -> jugC + src -> jugB;
		}
	}
	else{
		if (is_valid(src->jugA,src->jugB,src->jugC,1,dest))
			dest->jugC=src->jugC+1;
	}
	dest -> fn_index = 0;
}

void jugCtojugA(int A,int B,int C,const state_t * src,state_t * dest)	//mov from C to A
{
	int required = A - src -> jugA;//calculate amount of water required to fill jugA litre
	if (required && src->jugC)
	{
		if(src -> jugC >= required)//check if we have sufficient amount of water in jugC litre jug to fill jugA litre
		{
			dest -> jugC = src -> jugC - required;
			dest -> jugB = src -> jugB;
			dest -> jugA = src -> jugA + required;
		}
		else{
			dest -> jugC = 0;
			dest -> jugA = src -> jugC + src -> jugA;
			dest -> jugB = src -> jugB;
		}
	}
	else
		dest->jugA=src->jugA+1;
	
	dest -> fn_index = 0;
}

void jugCtojugB(int A,int B,int C,const state_t * src,state_t * dest)	//mov from C to B
{
	int required = B - src -> jugB;//calculate amount of water required to fill jugB litre
	if (required && src->jugC)
	{
		if(src -> jugC >= required)//check if we have sufficient amount of water in jugC litre jug to fill jugB litre
		{
			dest -> jugC = src -> jugC - required;
			dest -> jugB = src -> jugB + required;
			dest -> jugA = src -> jugA;
		}
		else{
			dest -> jugC = 0;
			dest -> jugB = src -> jugB + src -> jugC;
			dest -> jugA = src -> jugA;
		}
	}
	else
		dest->jugB=src->jugB+1;
	
	dest -> fn_index = 0;
}

int are_same(const state_t *lhs, const state_t *rhs)	//check if given two states are same or not
{
	return lhs -> jugA == rhs -> jugA && lhs -> jugB == rhs -> jugB && lhs -> jugC == rhs -> jugC;
}


//list operations
void init_list(list_t *ptr_list)
{
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}

void add_at_end(list_t *ptr_list, const state_t* ptr_state)		//adding node

{
	node_t* temp = (node_t*) malloc(sizeof(node_t));
	temp->st = *ptr_state; 
	temp->next = temp->prev = NULL;

	// empty list
	if(ptr_list->head == NULL)
	{
		temp->next = NULL;
		temp->prev = ptr_list->tail;
		ptr_list->head = temp;
		ptr_list->tail = temp;
	}
	else
	{
		temp->prev = ptr_list->tail;
		temp->next = NULL;
		ptr_list->tail = ptr_list->tail->next = temp;
	}
}

void remove_at_end(list_t *ptr_list)	//deleting node
{
	// empty list
	if(ptr_list->head == NULL)
	{
		printf("empty list\n");
	}
	// one node list
	else if(ptr_list->head == ptr_list->tail)
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = temp->prev;
		ptr_list->head = NULL;
		free(temp);
	}
	// multi node list
	else
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = temp->prev;
		ptr_list->tail->next = NULL;
		free(temp);
	}
}

void disp_list(const list_t *ptr_list)
{
	node_t* temp = ptr_list->head;
	while(temp)
	{
		disp_state(&temp->st);
		temp = temp->next;
	}
}

int is_repeated(const list_t* ptr_list, const state_t* ptr_state)//function to check if our state is already present in the list
{
	node_t* temp = ptr_list->head;
	while(temp)
	{
		if(are_same(&temp->st, ptr_state))
            return 1;
        temp = temp->next;
	}
	return 0;
}

int is_valid(int X,int Y,int Z,int a,const state_t* ptr_state)//function to check if a state is valid or not 
{
	// printf("A:%d B:%d C:%d X:%d\n",ptr_state -> jugA,ptr_state -> jugB,ptr_state -> jugC,X);
	int res1 = ((ptr_state -> jugA >= 0 && ptr_state -> jugA <= X) && 
		    (ptr_state -> jugB >= 0 && ptr_state -> jugB <= Y) &&
		    (ptr_state -> jugC >= 0 && ptr_state -> jugC <= Z) &&
			(ptr_state -> jugA) + (ptr_state -> jugB) + (ptr_state -> jugC) == a);
}
