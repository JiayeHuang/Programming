#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

struct cell{//each cell contains 2 values, the initial and the final one to enable ineration
	int initial;
	int new;
};

void print_grid(struct cell **p){
	int i=0;
	int j=0;
	for(i=0;i<40;i++){
		for(j=0;j<40;j++){
			if((*(p[i]+j)).initial==1) printf("*");
			else printf(" ");
	/*		printf("%d ",(*(p[i]+j)).initial);*/
		}
		printf("\n");
	}
}

int main(){
srand((unsigned int)time(NULL));
int i=0;
int j=0;
int l=0;
int m=0;
int n=0;
int u=0;
int v=0;

/*Create and initialize the 40*40 grid*/

struct cell **p=malloc(40*sizeof(struct cell *));
struct cell *p_val=malloc(40*40*sizeof(struct cell));

for(i=0;i<1600;i++) p_val[i].initial=(int)((float)rand()/(float)RAND_MAX+0.5); //initialize value of 0/1 randomly
for(i=0;i<40;i++) p[i]=&p_val[i*40];

print_grid(p);
printf("\033[40A\r"); //push the output point back for overlap display
fflush(stdout);

/*Judge the living situation of each cell, and overwrite the data*/
for(n=0;n<100;n++){//iterate 100 times

//check the neighbour value
for(i=0;i<40;i++){
	for(j=0;j<40;j++){//enumerate the cell in the grid
		int tmp=0;
		for(l=j-1;l<j+2;l++){
			for(m=i-1;m<i+2;m++){//check the neighbour values
				if(m<0) u=m+40; //rotate the position in the grid if the cell is in the boundary
				else if(m>39) u=m-40;
				else u=m;
				if(l<0) v=l+40;
				else if(l>39) v=l-40;
				else v=l;
				if(v!=j||u!=i) tmp+=(*(p[u]+v)).initial; //check if the neighbout is dead or live
			}
		}
		if((*(p[i]+j)).initial==1&&(tmp==2||tmp==3))//make the replacement per neighbour's status
			(*(p[i]+j)).new=1;
		else if((*(p[i]+j)).initial==0&&tmp==3)
			(*(p[i]+j)).new=1;
		else 
			(*(p[i]+j)).new=0;
	}
}

for(i=0;i<40;i++){
	for(j=0;j<40;j++){
		(*(p[i]+j)).initial=(*(p[i]+j)).new;//update the value in the struct
	}
}

//print the output according to the updated value
print_grid(p);
Sleep(100);
printf("\033[40A\r");
fflush(stdout);//overlap output for 100 times
}

print_grid(p);//final out put

free(p_val);
free(p);

return 0;
}
