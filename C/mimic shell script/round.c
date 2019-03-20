#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc,char *argv[])
{
	int c;
	double input;
	double output;

	while((c=getopt(argc,argv,"K:M:G:E:h:"))!=-1)
		switch(c){
			case 'K':
				input=atof(optarg);
				output=input/1024;
				printf("%.0f = %.1fK\n",input,output);
				break;
			case 'M':
				input=atof(optarg);
				output=input/pow(1024,2);
				printf("%.0f = %.1fM\n",input,output);
				break;
			case 'G':
				input=atof(optarg);
				output=input/pow(1024,3);
				printf("%.0f = %.1fG\n",input,output);
				break;
			case 'E':
				input=atof(optarg);
				output=input/pow(1024,6);
				printf("%.0f = %.1fE\n",input,output);
				break;
			case 'h':
				input=atof(optarg);
				output=input/1024;
				int ind=0;
				char s[]="KMGTPE";
				while(output>=1024){
					output=output/1024;
					ind+=1;
				}
				printf("%.0f = %.1f%c\n",input,output,s[ind]);
				break;
		}
	if(atof(argv[1])>0){
		input=atof(argv[1]);
		output=input/1024;
		printf("%.0f = %.1fK\n",input,output);
	}

	return 0;
}
