#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxr 500
#define maxn 10000

int main(int argc,char *argv[])
{
	if(argc!=2){
		printf("Please input one filename.\n");
		exit(1);
	}

	char* filename;
	char input[maxr];
	char text[maxn];
	filename=argv[1];

	int i=0;int j=0;

//Read the input file to text
	FILE *fp=fopen(filename,"r");
	while(fgets(input,maxr,fp)!=NULL){
		strcat(text,input);
		i+=1;
	}
	fclose(fp);

//Replace the non-printable characters with period '.'
	char non_p[8]={'\0','\a','\b','\f','\n','\r','\t','\v'};

	for(i=0;i<strlen(text);i++){
		for(j=0;j<sizeof(non_p);j++){
			if(text[i]==non_p[j]){text[i]='.';break;}
		}
	}

	int nrow,row,col;
	nrow=(int)(strlen(text)/16)+1;
	
	for(row=0;row<nrow;row++){
	//Print the index number in hexadecimal
		printf("%07x0\t",row);

	//Print the 16 space-seperated,two-column hexadecimal bytes
		for(col=0;col<16;col++){
			if(text[row*16+col]==0){
				if(col==7){printf("    ");}
				else{printf("   ");}
			}
			else{
				if(col==7){printf("%02x  ",text[row*16+col]);}
				else{printf("%02x ",text[row*16+col]);}
			}
		}
		printf("\t");

	//Print the 16 bytes in %_p format enclosed in '|' characters
		printf("|");
		for(col=0;col<16;col++){
			if(text[row*16+col]==0){break;}
			printf("%c",text[row*16+col]);
		}
		printf("|\n");
	}
	printf("%07x%x\n",nrow-1,col);

	return 0;
}
