#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* random record description - could be anything */
typedef struct REC rec;

struct REC
{
    int x,y,z;
};

/* writes and then reads 10 arbitrary records
   from the file "junk". */
int main()
{
    int i,j;
    FILE *f;
    rec* r = (rec*) malloc(sizeof(rec));

    /* create the file of 10 records */
    f = fopen("junk","w");
    if (!f) return 1;
    for (i=1;i<=10; i++)
    {
        r->x = i;
        fwrite(&r,sizeof(rec),1,f);
    }
    fclose(f);

    /* read the 10 records */
    f=fopen("junk","r");
    if (!f) return 1;
    for (i=1;i<=10; i++)
    {
        fread(&r,sizeof(rec),1,f);
        printf("%d\n",r->x);
    }
    fclose(f);
    printf("\n");

    /* use fseek to read the 10 records
       in reverse order */
    f=fopen("junk","r");
    if (!f) return 1;
    for (i=9; i>=0; i--)
    {
        fseek(f,sizeof(rec)*i,SEEK_SET);
        fread(&r,sizeof(rec),1,f);
        printf("%d\n",r->x);
    }
    fclose(f);
    printf("\n");

    /* use fseek to read every other record */
    f=fopen("junk","r");
    if (!f) return 1;
    fseek(f,0,SEEK_SET);
    for (i=0;i<5; i++)
    {
        fread(&r,sizeof(rec),1,f);
        printf("%d\n",r->x);
        fseek(f,sizeof(rec),SEEK_CUR);
    }
    fclose(f);
    printf("\n");

    /* use fseek to read 4th record,
       change it, and write it back */
    f=fopen("junk","r+");
    if (!f)
        return 1;
    fseek(f,sizeof(rec)*3,SEEK_SET);
    fread(&r,sizeof(rec),1,f);
    r->x=100;
    fseek(f,sizeof(rec)*3,SEEK_SET);
    fwrite(&r,sizeof(rec),1,f);
    fclose(f);
    printf("\n");

    /* read the 10 records to insure
       4th record was changed */
    f=fopen("junk","r");
    if (!f)
        return 1;
    for (i=1;i<=10; i++)
    {
        fread(&r,sizeof(rec),1,f);
        printf("%d\n",r->x);
    }
    fclose(f);
    return 0;
}
