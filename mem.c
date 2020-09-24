#include <stdio.h>
#include <stdlib.h>
 

extern char *p;
extern int size;

void allocate(int n); //function to allocate memory for the global array p, n number of bytes long.

void* mymalloc(int size); //function to allocate a block of size "size" from p

void myfree(void *b); //free the block pointed to by the parameter

void print_book(); // prints bytes used by the bookkeeping structure

void display_mem_map(); // print the memory array p in the following format
// start_addr   block_in_bytes  status

// sample output based on sanity_client
// allocate(200);

// mymalloc(30 * sizeof(char));
// display_mem_map();
// 0       16      book
// 16      30      allocated
// 46      16      book
// 62      138     free

typedef struct book{
     int marked;          // tells memory has been allocated or not i.e 0 is for not allocated, 1 is for allocated
 	int fsize;            // size of memoryblock after  book-keeping
 	struct book *next;    // pointer to point to next memory block
 }Book;


char *p;
int count,s;

void allocate(int n) //function to allocate memory for the global array p, n number of bytes long.
{
    Book *someptr;
    s=n;
    // char *p;
     p            = (char*)malloc(sizeof(char)*n);      //allocating dynamic memory
    someptr       = (Book*)p;                           // typecasting and storing address
    someptr->fsize =  n-sizeof(Book);                    //subtracting the bookkeepingsize from the given n  bytes size
    // printf("some : %d\n",someptr->size );
    // printf("%d\n",ptr->size );
    someptr->marked = 0;                                //initially making zero
    someptr->next   = NULL;                             //initially making next as null
    //printf("HI\n");
}

void* mymalloc(int size)                      //function to allocate a block of size "size" from p using first fit
{
        Book *cur = (Book*)p;                 //pointer to start
        // printf("cur: %d\n",cur->size );
    	Book *alloc = NULL;                   //another point to keep track from where the block should be allocated
    	int diff = 99999999;                  //likely max value is used initially to store diff
    	int temp_diff;
    	while(cur)
        {
            // printf("%d\n",cur->size );
    		temp_diff = cur->fsize - size;
            // printf("1temp diff :%d\n",temp_diff );
    		if((temp_diff < diff) && (temp_diff >= 0) && (cur->marked == 0))    //conditions
            {
    			diff  = temp_diff;
    			alloc = cur;
                // printf("diff :%d\n",diff );
                // printf("temp diff :%d\n",temp_diff );
                if (temp_diff>=0 && cur->fsize >=size)    //if found early or in between as of first fit policy and it splits memroy after allocating
                        break;
            }
    		cur = cur->next;
    	}
    	if(alloc)
        {
    		if((alloc->fsize-size) <= sizeof(Book))   //if diff of size is less than book ,just allocate
    		{
                	alloc->marked = 1;
                    count++;
            }
            else         //else allocating and then making next block ready
            {
    			Book *temp       = alloc->next;
    			int mem_size     = alloc->fsize;
    			alloc->marked    = 1;
    			alloc->fsize     = size;
    			alloc->next      = (Book*)((char*)(alloc + 1)+size);  //making it to point to next block
    			alloc->next->marked = 0;                              //marking as 0 to indicate not allocated
    			alloc->next->fsize  = mem_size - size -(sizeof(Book));//storing free size to next
    			alloc->next->next   = temp;
                count++;
    		}
    		return (void*)(alloc+1);       //returning as void pointer so as it can be typecasted to desired one in sanity_clientfile
    	}
        else
    	   return NULL;                         //if memoryblock is not present return NULL
}

void myfree(void *b) //free the block pointed to by the parameter
{
    Book *prev = NULL;                    //prev is used to manage links (previous one and next)
	Book *cur = (Book*)p;             //cur pointer points to which it is has o be freed
	while(cur && (cur + 1) != b)      //checking for conditions
    {
		prev = cur;
		cur = cur->next;
	}
	if(!cur)                          //if cur is NULL
        	return;
    else
    {
		if(prev == NULL)              //first block to be freed
        {
			if(cur->next != NULL)   //if it has adjacents blocks
            {
				if(cur->next->marked == 1)
                {
                	cur->marked = 0;
                    count--;
                }
                else
                {
					cur->marked = 0;
					cur->fsize += cur->next->fsize;  //to merge two free blocks
					cur->next   = cur->next->next;
                    count--;
                    if(count==0)
                        cur->fsize += sizeof(Book);
				}
			}
			else{
                count--;
                cur->marked = 0;
                // if(count==0)
                //     cur->fsize += sizeof(Book);
            }
		 }
		else if(cur->next == NULL)              //if it doesnt have adjacent blocks
        {
			if(prev->marked == 0)
            {
				prev->fsize += (cur->fsize + sizeof(Book));     //to merge two free blocks
				prev->next   = NULL;
                count--;
			}
			else
				{
                    count--;
                    cur->marked = 0;
                }
        }
		else if(prev->marked == 1 && cur->next->marked == 1)     //inbetween allocated blocks
			{
                cur->marked = 0;
                count--;
            }
		else if(prev->marked == 1 && cur->next->marked == 0)     //if previous block is marked and next one is not
        {
			cur->marked = 0;
			cur->fsize += (cur->next->fsize + sizeof(Book)); //to merge two free blocks
			cur->next   = cur->next->next;                   //managing pointer links
            count--;
        }
		else if(prev->marked == 0 && cur->next->marked == 1)    //if previous block is not marked and next one is
        {
			prev->fsize += (cur->fsize + sizeof(Book));
			prev->next   = cur->next;
            count--;
		}
		else if(prev->marked == 0 && cur->next->marked == 0)     //if previous block and next one is also not marked
        {
			prev->next  = cur->next->next;
			prev->fsize += (cur->fsize + cur->next->fsize + 2*sizeof(Book));
            count--;
            if (count==0 )
            {
                if((prev->fsize+=sizeof(Book))==s)
                    prev->fsize-=sizeof(Book);
            }
		}
	}
}

void print_book() // prints bytes used by the bookkeeping structure
{
    //printf("HI\n");
    printf("Memory used by bookkeeping => %ld\n", sizeof(Book));
}

void display_mem_map()
{
    // printf("HI\n");
    Book *temp = (Book*)p;
	int begin=0;                                 //begin is 0 since start addr is from 0
    printf("\n");
    for( ; temp != NULL; temp = temp->next )         //loop to starting from 1st to end
    {
        printf("%d\t%ld\t Book\n",begin,sizeof(Book));
		begin+=sizeof(Book);

		if(temp->marked== 0)
			printf("%d\t%d   \t free\n", begin, temp->fsize);                 //for free ones
		else
			printf("%d\t%d   \t allocated\n", begin, temp->fsize);            //for allocated ones

        begin+=temp->fsize;
    }
	printf("\n");
}
