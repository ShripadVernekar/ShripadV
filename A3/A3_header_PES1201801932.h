#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <stdlib.h>
// structure for jugs
typedef struct state{
	int jugA;	 //A Litre jug
	int jugB;	 //B Litre jug
	int jugC;	 //C Litre jug
	int fn_index;//function index to keep track which transition function was used previous time
}state_t;

// structure for states
typedef struct node{
	state_t st;	//our state
	struct node * prev;
	struct node * next;
}node_t;

// structure for nodes of list
typedef struct list{
	node_t * head;//points to the head of list
	node_t * tail;//points to the tail of list
}list_t;

//All state function declaration
void init_state(state_t * ptr_state);
void display_state(const state_t * ptr_state);
void set_state(state_t * ptr_state,int jugA,int jugB,int jugC);
int are_same(const state_t *lhs, const state_t *rhs);
// move functions
void jugAtojugB(int A,int B,int C,const state_t * src,state_t * dest);
void jugAtojugC(int A,int B,int C,const state_t * src,state_t * dest);
void jugBtojugA(int A,int B,int C,const state_t * src,state_t * dest);
void jugBtojugC(int A,int B,int C,const state_t * src,state_t * dest);
void jugCtojugA(int A,int B,int C,const state_t * src,state_t * dest);
void jugCtojugB(int A,int B,int C,const state_t * src,state_t * dest);

//list operations
void init_list(list_t *ptr_list);
void add_at_end(list_t *ptr_list, const state_t* ptr_state);
void remove_at_end(list_t *ptr_list);
void disp_list(const list_t *ptr_list);
int is_repeated(const list_t* ptr_list, const state_t* ptr_state);
int is_valid(int A,int B,int C,int a,const state_t* ptr_state);

#endif
