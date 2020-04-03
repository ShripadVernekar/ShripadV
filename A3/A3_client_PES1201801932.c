#include<stdio.h>
#include<stdlib.h>
#include "A3_header_PES1201801932.h"

int main()
{
	// freopen("output.txt","w",stdout);
    int count = 0;
    int A,B,C;
    int X,Y,Z;
    int P,Q,R;

    scanf("%d",&A);
    scanf("%d",&B);
    scanf("%d",&C);

    scanf("%d",&X);
    scanf("%d",&Y);
    scanf("%d",&Z);

    scanf("%d",&P);
    scanf("%d",&Q);
    scanf("%d",&R);

    state_t start_state;
    set_state(&start_state,X,Y,Z);
    // set_state(&start_state,8,0,0);
    state_t goal_state;
    set_state(&goal_state,P,Q,R);
    // set_state(&goal_state,3,5,0);
    list_t l;
    init_list(&l);
    state_t temp;
    int is_soln = 0;
    add_at_end(&l,&start_state);
    int index;
   
    void (*move[])(int A,int B,int C,const state_t *src,state_t *dest) = {
        jugAtojugB,
        jugAtojugC,
        jugBtojugA,
        jugBtojugC,
        jugCtojugA,
        jugCtojugB
    };
    int i = 0;
    while(l.tail)//check if there is a solution
    {
        index = l.tail -> st.fn_index;
        move[index](A,B,C,&l.tail->st,&temp);
        int a=X+Y+Z;    //to get total litres available
        if(is_valid(A,B,C,a,&temp) && !is_repeated(&l,&temp))//check if produced state valid or not
        {
            add_at_end(&l,&temp);       //list operation
            is_soln = are_same(&temp,&goal_state);
            if(is_soln)
            {
                disp_list(&l);
                remove_at_end(&l);  //remove the goal state 
                while(l.tail && ++l.tail->st.fn_index == 6) //update function index and if fn index == 6 remove the last node
                    remove_at_end(&l);
                count += 1;
                printf("\n");
            }
        }
        else
        {
            while(l.tail && ++l.tail->st.fn_index == 6) //updating function index and backtracking 
                remove_at_end(&l);
        }
    }
        printf("%d",count);
       
        return 1;
}
