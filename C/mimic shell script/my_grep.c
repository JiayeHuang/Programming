#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define maxr 500
#define maxl 500

#define red "\x1b[31m"
#define reset "\x1b[0m"

int main(int argc,char *argv[])
{	
	int c;
	int nflag,vflag,cflag;
	char *text;
	char *filename;
	nflag=0;vflag=0;cflag=0;

	char input[maxr];
	char w_text[maxr][maxl];
	int line=0;
	char *word;

	int i;

//Take the arguments input
	while(optind<argc){
		if((c=getopt(argc,argv,"nvc"))!=-1){
			switch(c){
				case 'n':
					nflag=1;
					break;
				case 'v':
					vflag=1;
					break;
				case 'c':
					cflag=1;
					break;
			}
		}
		else{
			text=argv[optind];
			filename=argv[optind+1];
			break;
		}
	}

//Read the text from the specified file
	FILE *fp=fopen(filename,"r");
	while(fgets(input,maxr,fp)!=NULL){
		strcpy(w_text[line],input);
		line+=1;
	}
	fclose(fp);

//Print the line according to the input flag

	for(i=0;i<=line;i++){
		if(vflag==0){
			if(nflag==0){
				if(cflag==0){
	//No line number,no invert,no color highlight
					if(strstr(w_text[i],text)!=NULL){printf("%s\n",w_text[i]);}
				}
				else{
	//No line number,no invert,with color highlight
					if(strstr(w_text[i],text)!=NULL){
						word=strtok(w_text[i]," ");
						while(word!=NULL){
							if(strstr(word,text)!=NULL){printf(red);printf("%s ",word);printf(reset);}
							else{printf("%s ",word);}
							word=strtok(NULL," ");
						}
						printf("\n");
					}
				}
			}
			else{
				if(cflag==0){
	//Have line number,no invert,no color highlight
					if(strstr(w_text[i],text)!=NULL){printf("%d\t%s\n",i+1,w_text[i]);}
				}
				else{
	//Have line number,no invert,with color highlight
					if(strstr(w_text[i],text)!=NULL){
						printf("%d\t",i+1);
						word=strtok(w_text[i]," ");
						while(word!=NULL){
							if(strstr(word,text)!=NULL){printf(red);printf("%s ",word);printf(reset);}
							else{printf("%s ",word);}
							word=strtok(NULL," ");
						}
						printf("\n");
					}
				}
			}
		}
		else{
			if(nflag==0){
	//No line number,invert,no color highlight
				if(strstr(w_text[i],text)==NULL){printf("%s\n",w_text[i]);}
			}
			else{
	//Have line number,invert,no color highlight
				if(strstr(w_text[i],text)==NULL){printf("%d\t%s\n",i+1,w_text[i]);}
			}
		}
	}

	return 0;
}
