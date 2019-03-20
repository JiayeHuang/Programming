#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc,char *argv[]){
	int i;
	for(i=1;i<argc;i++){
		if(atoi(argv[i])<0){
			printf("Please input a positive integer.\n");
			exit(1);
		}
	}

	int c;
	int fir,incre,fin;
	int num;
	fir=1;
	incre=1;

	if(argc==2){
		num=fir;
		fin=atoi(argv[1]);
	}
	if(argc==3){
		fir=atoi(argv[1]);
		fin=atoi(argv[2]);
		num=fir;
	}
	if(argc==4){
		fir=atoi(argv[1]);
		incre=atoi(argv[2]);
		fin=atoi(argv[3]);
		num=fir;
	}

	while((c=getopt(argc,argv,"w"))!=-1)
		switch(c){
			case 'w':
				if(argc==3){
					fir=1;
                			num=fir;
                			fin=atoi(argv[2]);
        			}
        			if(argc==4){
                			fir=atoi(argv[2]);
                			fin=atoi(argv[3]);
                			num=fir;
        			}
        			if(argc==5){
                			fir=atoi(argv[2]);
                			incre=atoi(argv[3]);
                			fin=atoi(argv[4]);
                			num=fir;
        			}

				while(num<=fin){
					printf("%0*d\n",(int)log10(fin)+1,num);
					num=num+incre;
				}
		}

	while(num<=fin){
		printf("%d\n",num);
		num=num+incre;
	}

	return 0;
}
