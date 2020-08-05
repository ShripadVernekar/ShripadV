#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "assignment_2.h"

typedef struct node{
	int num;
	struct node * link;
}node;

int count(node* temp);
void display(node *);

void display(node *root)  //to display the list of competitors competed
{
	node* cur = root;
	while(cur)
	{
		printf("%d ",cur -> num);
		cur = cur->link;
	}
}

int count(node* temp)		//computes and return the number of nodes
{
	int cnt = 0;
	while(temp)
    {
 		cnt  = cnt+1;
 		temp = temp->link;
    }
	return cnt;
}

void find_second_greatest(int *numbers, int n)
{
    int first = 0;
    int second;
	int result;
	int size = (int)ceil(log2(n)) + 1;		//compute and store the required size for array of lists

	node* root = NULL;
	node* cur  = NULL;
	node* ptr1 = NULL;
	node* ptr2 = NULL;
    node* ptr3 = NULL;
	node* arr[size];					//creating an array of lists of computed size

	for(int i = 0; i < size; i++)
		arr[i] = NULL;					//initialising the array to null st starting

	for(int i = 0;i < n;i++)
	{
		node* nw   = (node *)malloc(sizeof(node));		//create each node every time for numbers of an array
		nw -> num  = numbers[i];
		nw -> link = NULL;
		root  = nw;					//make root to point to new node
		int j = 0;
		while(arr[j])
		{
			if(arr[j]->num > root->num) 	//competetion between two list
			{
				display(arr[j]);			//display the   
			    printf("x ");				// *numbers
			    display(root);				// *that are
			    printf(" = ");				// *competing
				cur = arr[j]->link;			//maintaing the required links
			    arr[j]->link = root;
			    root->link   = cur;
			    root = arr[j];
			    display(root);				//display after playing match or competing, same follows for below code also
			    printf("\n");
			}
			else
			{
				display(arr[j]);
			    printf("x ");
			    display(root);
			    printf(" = ");
				cur = root->link;				//maintaing the required links
				root->link   = arr[j];
				arr[j]->link = cur;
			    display(root);
			    printf("\n");
			}
			arr[j] = NULL;		// after linking make that space as null to allow for others to store 
			j += 1;
		}
		arr[j] = root;			//atlast store the root in the array of lists
	}


	if((n & (n - 1)))		//if the length of array is not exact power of two 
	{
		while(!arr[first])	//using two pointer method to find the two lists for competetion
			first += 1;

		ptr1 = arr[first];	//storing the address of first index i.e first non null value of an array
		first += 1;
		while(!arr[first])  //increment till u find the next non null value
			first += 1;

		ptr2 = arr[first];	//store the next non null value 
		if(ptr1->num > ptr2->num)	//compare between these 2 lists 
		{
			display(ptr1);
			printf("x ");
			display(ptr2);
			printf(" = ");
			cur = ptr1->link;			//maintaing the required links
			ptr1->link = ptr2;
			ptr2->link = cur;
			display(ptr1);
			printf("\n");
		}
		else
		{
			display(ptr1);
			printf("x ");
			display(ptr2);
			printf(" = ");
			cur = ptr2->link;			//maintaing the required links
			ptr2->link = ptr1;
			ptr1->link = cur;
			ptr1 = ptr2;
			display(ptr2);
			printf("\n");
		}
        second = first + 1; 	    // here ptr1 will be having the winner(largest)

        while(second <= size - 3)   //updating ptr1 by checking it with rest of the numbers (i.e competing with rest of competitors)
        {
        	while(!arr[second])
        		second += 1;

        	ptr3 = arr[second];
        	if((ptr1->num > ptr3->num ))
			{
        	    display(ptr3);
			    printf("x ");
			    display(ptr1);
			    printf(" = ");
        		cur = ptr1->link;			//maintaing the required links
        		ptr1->link = ptr3;
        		ptr3->link = cur;
        		display(ptr1);
        		printf("\n");
        		second += 1;
        	}
        	else
			{
        		display(ptr3);
			    printf("x ");
			    display(ptr1);
			    printf(" = ");
        		cur = ptr3->link;			//maintaing the required links
        		ptr3->link = ptr1;
        		ptr1->link = cur;
        		ptr1 = ptr3;
        		display(ptr1);
        		printf("\n");
        		second += 1;
        	}
        }
        node* ptr4 = arr[size - 2]; //to find winner for the last list
       	int c = count(ptr1);
        if (c < 2)				//only if the number of nodes <2 execute else no need to execute below code
		{
			if((ptr1 -> num > ptr4 -> num ))
			{
				printf("in");
				display(ptr4);
				printf("x ");
				display(ptr1);
				printf(" = ");
				cur = ptr1->link;			//maintaing the required links
				ptr1->link = ptr4;
				ptr4->link = cur;
				display(ptr1);
				printf("\n");
			}

			else
			{
				display(ptr4);
				printf("x ");
				display(ptr1);
				printf(" = ");
				cur = ptr4->link;			//maintaing the required links
				ptr4->link = ptr1;
				ptr1->link = cur;
				ptr1 = ptr4;
				display(ptr1);
				printf("\n");
			}
        }
        arr[size - 1] = ptr1;
    }

	result = arr[size - 1]->link->num;			//to figure out the 2nd largest element
	cur    = arr[size - 1]->link->link;
	while(cur)
	{
		if(cur->num > result)
			result = cur->num;
		cur = cur->link;
	}
	printf("\n%d",result);				//result will be having the 2nd largest element
}
