#include<stdio_ext.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
   char a[20];
}s;
int main ()
{
   char*k;
   s b[50];
   int i=0;
 
   int j;
   k=(char*)calloc(200,sizeof(char));
   printf("Enter a sentence u want :\n");
   __fpurge(stdin);
   fgets(k,200,stdin);
   FILE*ptr;
   ptr=fopen("hoanh1.txt","w");
   fprintf(ptr,"%s",k);
   fclose(ptr);
   ptr=fopen("hoanh1.txt","r");
   while(!feof(ptr))
   {
       fscanf(ptr,"%s",b[i].a);
       i++;
   }
   fclose(ptr);
   for(j=0;j < i-1;j++)
   {
       printf("%s\n",b[j].a);
   }
  
   free(k);
}
