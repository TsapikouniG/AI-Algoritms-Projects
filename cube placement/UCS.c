/*KOTOFOLI CHRISTINA, AM:4087
TSAPIKOYNI GEWRGIA, AM:4304*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define K 2
#define N 3*K
#define L 4*K

/*the struct status contains the following elements for moving the cubes*/
struct status
{   int pos[N][2];/*The table pos contains two columns which are the coordinates(x,y) of each cube*/ 
    double cost; /*The cost g(n)*/
    struct status *now_parent;
    struct status *next_parent;
    struct status *route;
    struct status *closed;
};
  
int number_of_extensions=0;/*The extensions that are made (requested)*/
struct status *initial=NULL;/*Start of search*/
struct status *final=NULL;/*Ånd of search*/  
struct status *cl_set_in=NULL;/*Principle of closed set*/
struct status *cl_set_f=NULL;/*End of closed set*/ 


/*copy the elements of table pos to table pos1*/
void copy_table(int pos[N][2],int pos1[N][2])
{  
	int j;
	for(j=0;j<N;j++){ 
		pos1[j][0]=pos[j][0];
		pos1[j][1]=pos[j][1];
	}
}


/*check if position (x,y) is free*/
int free_position(int pos[N][2],int x,int y) 
{     
	int i;
	for (i=0;i<N;i++){   
		if (pos[i][0] == x && pos[i][1] == y)/*if there is a cube it is not free*/
            return 0; //not free
    }
    return 1; //free
}


/*check if any cube is free in position (y+1) there is no other cube*/
int free_square(int pos[N][2],int x,int y)
{     
	int i;
	if(y == 3){/*top line, sure free cube*/
		return 1;
	}
	/*y=1 or y=2 
	if position (y+1) is empty then it is a free cube*/
	if(free_position(pos,x,y+1) == 1){
		return 1;
	}
      
}


/*checks if condition (i) is valid*/
int valid_status(int pos1[N][2]) 
{     
	int i;
	for (i=0;i<N;i++){ 
		/*if cube (é) is in the above rows and there is none from any other cube then the condition is not valid*/  
		if (pos1[i][1] >= 2 && free_position(pos1,pos1[i][0],pos1[i][1]-1) == 1 ) 
            return 0; 
		}
	return 1;
}


void initial_state_on_search(void)
{   
    int i;
    int x=1;
    int y=1;
    
    /*I create a new status, bind malloc*/
    struct status *temp=NULL;
    temp=(struct status *)malloc(sizeof(struct status));
    if (temp==NULL){   
		printf("Error allocating memory!\n");
        exit(0);
    }
    
    /*initialization*/
    temp->cost=0.0; 
    temp->now_parent=NULL;
    temp->next_parent=NULL;
    temp->closed=NULL;
    temp->route=NULL;
    
    
	/*iteratively until the condition becomes valid
	the user defines the initial state*/
    while(1) 
	{   
		i=0;
        while (i < N){    
			printf("Give the coordinates (x,y) of cube number %d:\n",i+1);
			scanf("%d %d",&x, &y);
			if(x<=L && y == 1){
				temp->pos[i][0] =  x;
				temp->pos[i][1] =  y;
	        	i++;
			}
			else if(x<=K && y == 2){
				temp->pos[i][0] =  x;
				temp->pos[i][1] =  y;
	        	i++;
			}
			else if(x<=K && y == 3){
				temp->pos[i][0] =  x;
				temp->pos[i][1] =  y;
	        	i++;
			}
			else{
				printf("You gave wrong coordinates\n");
			}
			
	    }
	    
        if ( valid_status(temp->pos) == 1){
        	break; 
		}
        else{
        	printf("You have given an invalid status!\n");
		}
    }
	
    initial=temp; /*search front start*/
    final=temp; /*end of search front*/
}

/*I try to find the route with the lowest cost*/
struct status *smaller_state(void)
{   
	struct status *st,*before,*cur,*best_comb;
    double smaller_cost;
    
    before=NULL;
    
    st=initial; /*search front start*/
    smaller_cost=st->cost; /* smaller_cost --> initialization*/
    best_comb=st; /*the situation with the smallest cost --> initialization*/
    while(st->next_parent!=NULL){   
		cur=st;
        st=st->next_parent;
        if (st->cost < smaller_cost){   
			smaller_cost=st->cost; /* smaller_cost --> update, most min[g(n)+h(n)]*/
            best_comb=st; /*the situation with the smallest cost --> update*/
            before=cur;
        }
    }
    
    
   /*delete a status*/
    if (before!=NULL){   
		before->next_parent=best_comb->next_parent;
        if (best_comb->next_parent==NULL){
        	final=before;
		}  
        best_comb->next_parent=NULL;
    }
    else{   
		initial=best_comb->next_parent;
        if (best_comb->next_parent==NULL){
        	final=NULL;
		}  
        best_comb->next_parent=NULL;
    } 
    return(best_comb);/*return the state with the smallest cost*/ 
}


/*checks if the state is final*/
int final_state(struct status *st) 
{   
	int i;

	/*the numbered cubes 1-K*/
    for(i=0;i<K;i++) { 
       if (st->pos[i][0] != (i+1) || st->pos[i][1] != 1){/*if for y=1 the cubes 1-K is not in the positions 1-K*/
           return 0; 
       }
    }

	/*the numbered cubes (K+1)-2K*/
    for(i=K;i<2*K;i++){ 
       if (st->pos[i][0] != (i-K+1) || st->pos[i][1] != 2){/*if for y=2 the cubes (K+1)-2K is not in the positions (K+1)-2K*/
           return 0; 
       }
    }

	/*the numbered cubes (2K+1)-3K*/
    for(i=2*K;i<3*K;i++){ 
       if (st->pos[i][0] != (i-2*K+1) || st->pos[i][1] != 3){/*if for y=3 the cubes (2K+1)-3K is not in the positions (2K+1)-3K*/
           return 0;
    	}
    }

    return 1;
}


void print_top_route(struct status *st)
{    
	struct status *temp,*st1;
    int i;
	int z=1;
    temp=st;
    st1=st;
    while(temp->now_parent!=NULL){    
		temp->now_parent->route=temp;
        temp=temp->now_parent;
    }
    printf("-----------------------------------------------------------------------------------------\n");
    /*prints the paths of the cubes*/
    while(temp!=st1){   
		printf("The %d state with cost %f is:",z,temp->cost);
        for(i=0;i<N;i++){   
			printf("%d:(%d,%d) ",i+1,temp->pos[i][0],temp->pos[i][1]);
		}
        printf("\n");
        temp=temp->route;
        z++;
    }
    printf("The %d final state with cost %f is:",i,temp->cost);
    for(i=0;i<N;i++){   
		printf("%d:(%d,%d) ",i+1,temp->pos[i][0],temp->pos[i][1]);
    }
    printf("\n");
    printf("-----------------------------------------------------------------------------------------\n");
}


/*checks if the state is part of the closed set*/
int searching(int pos1[N][2])
{   
	int sear,i;
	int counter=0;
    struct status *st;
    
    /*Principle of closed set*/
    st=cl_set_in;
    while(st!=NULL){   
		sear=1;
        for(i=0;i<N;i++){   
			if (pos1[i][0] != st->pos[i][0] || pos1[i][1] != st->pos[i][1]){   
				sear=0;
                break;
            }
        }
        if (sear==1){   
			counter=1;
            break;
        }
        st=st->closed;
    }
    
    return(counter);
}


/*the function for the extensions that is done*/
void new_situations(struct status *st)
{   struct status *temp=NULL;
    int i,j,q;
    int x,y,y_tonos;
    int pos1[N][2];
    
    for(i=0;i<N;i++){ /*I run every cube*/   
		if ( free_square(st->pos,st->pos[i][0],st->pos[i][1]) == 1 ){ /*if I find a free cube*/ 
		    for (j=1;j<=L;j++){ /*I am looking for a free position on the table (y=1)*/ 
				if ( free_position(st->pos,j,1) == 1){ /*if I find a free position*/     
			        copy_table(st->pos,pos1); /*copy the elements of table pos to table pos1*/
                    pos1[i][0] = j; /*temporarily place cube i in column j*/
                    pos1[i][1] = 1; /*temporarily place cube i in line 1*/
                    if ( valid_status(pos1) == 1 ){ /*if new temporary position valid*/   
					    temp=(struct status *)malloc(1*sizeof(struct status));  /*I create a new status, bind malloc*/
                        if (temp==NULL){  
							printf("Error allocating memory!\n");
                            exit(0);
                        }
                        
                        /*copying positions*/
                        copy_table(st->pos,temp->pos);
                        temp->pos[i][0] = j;
                        temp->pos[i][1] = 1;

						y_tonos = 1;
                        y = st->pos[i][1];
                        
                        /*when the cube is raised*/
                        if ( y_tonos > y ){
                        	temp->cost= st->cost+ y_tonos - y;
						}
						
						/*when the cube is brought down*/
                        else if ( y_tonos < y ){
                        	temp->cost= st->cost+ 0.5*(y-y_tonos);
						}
                        
						/*move moves the cube to the same row*/    
                        else{
                        	temp->cost= st->cost+ 0.75;
						}

                        temp->now_parent=st; 
                        temp->next_parent=NULL;
                        temp->closed=NULL;

                        /*the new status is entered at the end of the metspo search*/
                        if (initial==NULL){
                            initial=temp;
                            final=temp;
                        }
                        else{   
                            final->next_parent=temp;
                            final=temp;
                        }
                        /*in the bottom(y=1) row of a free cube it is enough to enter 
						one of the available positions (K+1)-L*/
                        if(j>=K){
                        	break;
						}
                    }
               }
            }

            
            for (j=1;j<K;j++){ /*Looking for a free position in the middle row (y=2)*/
				if ( free_position(st->pos,j,2) == 1 ){ /*if I find a free position*/     
			        copy_table(st->pos,pos1);/*copy the elements of table pos to table pos1*/
                    pos1[i][0] = j;/*temporarily place cube i in column j*/
                    pos1[i][1] = 2; /*temporarily place cube i in line 2*/
                    if ( valid_status(pos1) == 1 ) { /*if new temporary position valid*/   
						temp=(struct status *)malloc(1*sizeof(struct status)); /*I create a new status, bind malloc*/
                        if (temp==NULL){  
							printf("Error allocating memory!\n");
                            exit(0);
                        }
                        
                        /*copying positions*/
                        copy_table(st->pos,temp->pos);
                        temp->pos[i][0] = j;
                        temp->pos[i][1] = 2;

						y_tonos = 2;
                        y = st->pos[i][1];
                        
                        /*when the cube is raised*/
                        if ( y_tonos > y ){
                        	temp->cost= st->cost+ y_tonos - y;
						}
						
						/*when the cube is brought down*/
                        else if ( y_tonos < y ){
                        	temp->cost= st->cost+ 0.5*(y-y_tonos);
						}
                         
						/*move moves the cube to the same row*/    
                        else{
                        	temp->cost= st->cost+ 0.75;
						}
                              
                        temp->now_parent=st;
                        temp->next_parent=NULL;
                        temp->closed=NULL;


						/*the new status is entered at the end of the metspo search*/
                        if (initial==NULL){
                            initial=temp;
                            final=temp;
                        }
                        else{   
                            final->next_parent=temp;
                            final=temp;
                        }
                    }
               }
            }

            
            for (j=1;j<=K;j++){ /*Looking for a free position in the top row (y=3)*/
				if ( free_position(st->pos,j,3) == 1 ){ /*if I find a free position*/   
			        copy_table(st->pos,pos1);/*copy the elements of table pos to table pos1*/
                    pos1[i][0] = j;/*temporarily place cube i in column j*/
                    pos1[i][1] = 3;/*temporarily place cube i in line 2*/
                    if ( valid_status(pos1) == 1 ){ /*if new temporary position valid*/  
						temp=(struct status *)malloc(sizeof(struct status)); /*I create a new status, bind malloc*/
						if (temp==NULL){  
							printf("Error allocating memory!\n");
                            exit(0);
                        }
                        
                        /*copying positions*/
                        copy_table(st->pos,temp->pos);
                        temp->pos[i][0] = j;
                        temp->pos[i][1] = 3;
                        
                        y_tonos = 3;
                        y = st->pos[i][1];
                        
                        /*when the cube is raised*/
                        if ( y_tonos > y ){
                        	temp->cost= st->cost+ y_tonos - y;
						}
						
						/*when the cube is brought down*/
                        else if ( y_tonos < y ){
                        	temp->cost= st->cost+ 0.5*(y-y_tonos);
						}
                         
						/*move moves the cube to the same row*/    
                        else{
                        	temp->cost= st->cost+ 0.75;
						}

                        temp->now_parent=st;
                        temp->next_parent=NULL;
                        temp->closed=NULL;

						/*the new status is entered at the end of the metspo search*/
                        if (initial==NULL){
                            initial=temp;
                            final=temp;
                        }
                        else{   
                            final->next_parent=temp;
                            final=temp;
                        }
                    }
               }
            }
        }
    }

    /*every time a state is extended it is immediately deleted and entered into the closed set*/
    if (cl_set_in==NULL)
    {   
        cl_set_in=st;
        cl_set_f=st;
    }
    else
    {   
        cl_set_f->closed=st;
        cl_set_f=st;
    }
    
}
 
void UCS(void)
{  
	struct status *st1;
    int flag=0;
	int w,i;
	int secur,check;
	
    /*creation of an initial state by the user*/
    initial_state_on_search(); 
    
    /*display on the screen*/
    printf("AK is:");
    for(i=0;i<N;i++){   
		printf("%d:(%d,%d) ",i+1,initial->pos[i][0],initial->pos[i][1]);
    }
    printf("\n");
    printf("Enter:\n");
    scanf("%d",&w);

	/*iteratively until the final state is found*/
    while(flag==0){
	     
        st1=smaller_state(); /*I check which situation has the lowest cost*/
        secur=searching(st1->pos); /*I check which state is part of the closed set*/
        
        if (secur==0){     
            check=final_state(st1);/*I check if any status is final*/
            /*if it is a final state, 
			the route appears on the screen*/
            if (check==1) {        
                flag=1;
                print_top_route(st1); 
            }
            /*if I haven't reached the final state yet, 
			I continue and run the extensions*/
            else{ 
                number_of_extensions++; 
                if (number_of_extensions % 3000 == 0){ 
                    printf("P %d C %f\n",number_of_extensions,st1->cost); 
				}
                new_situations(st1); 
                
         	}
    	}
    	
    }
}
main()
{   UCS(); 
	printf("Were %d expanded!\n",number_of_extensions);
}













