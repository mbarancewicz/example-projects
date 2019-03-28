#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct bites
{
    unsigned char a: 1;
    unsigned char b: 1;
    unsigned char c: 1;
    unsigned char d: 1;
    unsigned char e: 1;
    unsigned char f: 1;
    unsigned char g: 1;
    unsigned char h: 1;
};
union bit_set
{
    int c;
    struct bites bit;
};
int encode(const char *input, char *txt, const char *output)
{
    if(input==NULL || txt==NULL || output==NULL) return 4;
    FILE *src;
    if((src=fopen(input,"r"))==NULL) return 1;
    FILE *out;
    if((out=fopen(output,"w"))==NULL)
    {
        fclose(src);
        return 2;
    }

    union bit_set read;
    union bit_set txt_lett;

    int i,j=0,k=0;
    char width[5000];
    fgets(width,5000,src);
    for(i=0;i<(int)strlen(width);i++)
    {
        if(*(width+i)==' ') j++;
    }

    for(i=0;i<(int)strlen(txt);i++)
    {

        if(fgetc(src)==EOF) { fclose(src); fclose(out); return 3;}
        else fseek(src,-1,SEEK_CUR);

        txt_lett.c = *(txt+i);

        if(fscanf(src,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(src); fclose(out); return 3;}
        read.bit.a =  txt_lett.bit.h;
        fprintf(out,"%d ",read.c);
        k++;
        if(k%j==0) { fprintf(out,"\n"); k=0;}

        if(fscanf(src,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(src); fclose(out); return 3;}
        read.bit.a =  txt_lett.bit.g;
        fprintf(out,"%d ",read.c);
        k++;
        if(k%j==0) { fprintf(out,"\n"); k=0;}

        if(fscanf(src,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(src); fclose(out); return 3;}
        read.bit.a =  txt_lett.bit.f;
        fprintf(out,"%d ",read.c);
        k++;
        if(k%j==0) { fprintf(out,"\n"); k=0;}

        if(fscanf(src,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(src); fclose(out); return 3;}
        read.bit.a =  txt_lett.bit.e;
        fprintf(out,"%d ",read.c);
        k++;
        if(k%j==0) { fprintf(out,"\n"); k=0;}

        if(fscanf(src,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(src); fclose(out); return 3;}
        read.bit.a =  txt_lett.bit.d;
        fprintf(out,"%d ",read.c);
        k++;
        if(k%j==0) { fprintf(out,"\n"); k=0;}

        if(fscanf(src,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(src); fclose(out); return 3;}
        read.bit.a =  txt_lett.bit.c;
        fprintf(out,"%d ",read.c);
        k++;
        if(k%j==0) { fprintf(out,"\n"); k=0;}

        if(fscanf(src,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(src); fclose(out); return 3;}
        read.bit.a =  txt_lett.bit.b;
        fprintf(out,"%d ",read.c);
        k++;
        if(k%j==0) { fprintf(out,"\n"); k=0;}

        if(fscanf(src,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(src); fclose(out); return 3;}
        read.bit.a =  txt_lett.bit.a;
        fprintf(out,"%d ",read.c);
        k++;
        if(k%j==0) { fprintf(out,"\n"); k=0;}
    }

    while(fgetc(src)!=EOF)
    {
        fseek(src,-1,SEEK_CUR);
        if(fscanf(src,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(src); fclose(out); return 3;}
        read.bit.a=0;
        fprintf(out,"%d ",read.c);
        k++;
        if(k%j==0) { fprintf(out,"\n"); k=0;}
        i++;
    }
    fclose(src);
    fclose(out);
    return 0;
}
int decode(const char * filename, char *txt, int size)
{
    if(filename==NULL || txt==NULL || size<=0) return 2;
    FILE *fp;
    if((fp=fopen(filename,"r"))==NULL) return 1;

    fseek(fp,0,SEEK_END);
    int flen = (int)ftell(fp);
    fseek(fp,0,SEEK_SET);
    if(size>flen)
    {
        fclose(fp);
        return 2;
    }

    union bit_set read;
    union bit_set letter;

    int i;
    for(i=0;i<size;i++)
    {
        if(fgetc(fp)==EOF) { fclose(fp);   return 0; }
        else fseek(fp,-1,SEEK_CUR);

        if(fgetc(fp)!='\n') fseek(fp,-1,SEEK_CUR);

        if(fscanf(fp,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(fp);   return 3; }
        letter.bit.h=read.bit.a;

        if(fscanf(fp,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(fp);   return 3; }
        letter.bit.g=read.bit.a;

        if(fscanf(fp,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(fp);   return 3; }
        letter.bit.f=read.bit.a;

        if(fscanf(fp,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(fp);   return 3; }
        letter.bit.e=read.bit.a;

        if(fscanf(fp,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(fp);   return 3; }
        letter.bit.d=read.bit.a;

        if(fscanf(fp,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(fp);   return 3; }
        letter.bit.c=read.bit.a;

        if(fscanf(fp,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(fp);   return 3; }
        letter.bit.b=read.bit.a;

        if(fscanf(fp,"%d ",&read.c)!=1 || read.c<0 || read.c>255)
        { fclose(fp);   return 3; }
        letter.bit.a=read.bit.a;

        *(txt+i)=letter.c;
    }
    fclose(fp);
    return 0;
}
int main()
{
    char path[31],path2[31], txt[5011];
    printf("Podaj litere (d - decode, e - encode): ");
    switch(getchar())
    {
        case 'e':
            printf("Podaj tekst do ukrycia: ");
            fseek(stdin,0,SEEK_END);
            fgets(txt,1011,stdin);
            printf("Podaj plik wejsciowy: ");
            fseek(stdin,0,SEEK_END);
            scanf("%30[./ A-Za-z0-9]",path);
            printf("Podaj plik wyjsciowy: ");
            fseek(stdin,0,SEEK_END);
            scanf("%30[./ A-Za-z0-9]",path2);
            switch(encode(path,txt,path2))
            {
                case 0:
                    printf("File saved");
                    return 0;
                case 1:
                    printf("File not found");
                    return 1;
                case 2:
                    printf("Couldn't create file");
                    return 2;
                case 3:
                    printf("File corrupted");
                    return 3;
            }
            break;
        case 'd':
            printf("Podaj plik: ");
            fseek(stdin,0,SEEK_END);
            scanf("%30[./ A-Za-z0-9]",path);
            switch(decode(path,txt,5010))
            {
                case 0:
                    puts(txt);
                    return 0;
                case 1:
                    printf("File not found");
                    return 1;
                case 2:
                    printf("Couldn't create file");
                    return 2;
                case 3:
                    printf("File corrupted");
                    return 3;
            }
            break;
        default:
            printf("Incorrect input");
            return 0;
    }
    return 0;
}
