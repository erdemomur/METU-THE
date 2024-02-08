#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    
    int x,y,cikis;
    char *labyrent[33500];
    char a[33500];
    char q,u;
    int i,j,k,rownum,columnum;
    scanf("%d %d",&x,&y);

    
    getchar();
    while((u=getchar())!=EOF){
        a[0]=u;
        i=1;
        while((a[i]=getchar())!='\n'){
            i++;}
        
        labyrent[j]=(char*)malloc(sizeof(char)*i);
        
        for(k=0;k<i;k++){
            labyrent[j][k]=a[k];
        }
        j++;
    }
    
    rownum=j;
    columnum=i;
    
    
    cikis=0;
    
    islemler(x,y,labyrent,columnum,rownum);
    
    for (i=0;i<columnum;i++){
        if ( (labyrent[0][i] == '*') || (labyrent[rownum-1][i] == '*')){
            cikis=1;
        }
    }
    for (i=0;i<rownum;i++){
        if((labyrent[i][0] == '*' ) || (labyrent[i][columnum-1] == '*')){
            cikis=1;
        }
    }    
    
    if (cikis==0){
        for (i=0;i<rownum;i++){
            for (j=0;j<columnum;j++){
                if (labyrent[i][j] == '*'){
                    labyrent[i][j] = '.';
                }
            }
        }
        
    }
    
    for (i=0; i<rownum; i++){
        for (j=0; j<columnum; j++){
            q=labyrent[i][j];
            printf("%c",q);
            if (j==columnum-1){
                printf("\n");
            }
        }
    }
    
    return 0;
}

int islemler(int x,int y ,char* labyrent[33500],int columnum,int rownum){
    
    if ((x==0) || (x==rownum-1) || (y==0) || (y==columnum-1) ){
        return 0;
    }
    /* move left */
    if ( (labyrent[x-1][y] != 'X') && (labyrent[x-1][y] != '*') ){
        labyrent[x-1][y] = '*';
        islemler(x-1,y,labyrent,columnum,rownum);
    }
    /* move right */
    if ( (labyrent[x+1][y] != 'X') && (labyrent[x+1][y] != '*') ){
        labyrent[x+1][y] = '*';
        islemler(x+1,y,labyrent,columnum,rownum);
    }
    /* move up*/
    if ( (labyrent[x][y-1] != 'X') && (labyrent[x][y-1] != '*') ){
        labyrent[x][y-1] = '*';
        islemler(x,y-1,labyrent,columnum,rownum);
    }
   /* move down*/
    if ( (labyrent[x][y+1] != 'X') && (labyrent[x][y+1] != '*') ){
        labyrent[x][y+1] = '*';
        islemler(x,y+1,labyrent,columnum,rownum);
    }
    return 0;
}
