#include <stdio.h>
#include <stdlib.h>

FILE *f1;
FILE *f2;
int mat[10][10];
int visited[100];

typedef struct Queue{
    int x;
    struct Queue *next;
}queue;


queue *left=NULL;
queue *right=NULL;

/*void **allocMat(int dimension){
  int **mat=calloc(sizeof(int*),dimension);
   for(int i=0;i<dimension;i++)
        mat[i]=calloc(sizeof(int),dimension);
return mat;*/


void enqueue(int x){
    queue *q=(queue *)malloc(sizeof(queue));
    q->x=x;
    if(left==NULL && right==NULL){
        left=right=q;
        q->next=NULL;
    }
    else{
        right->next=q;
        q->next=NULL;
        right=q;
    }

}

void dequeue(){
    if(left!=NULL){
        if(right==left){
            left=NULL;
            free(right);
            right=NULL;

        }
        else{
            queue *q=left;
            left=left->next;
            free(q);
        }
    }
}

void BFS(int mat[10][10],int start,int n){
    for(int i=0;i<n;i++)
       visited[i]=0;
    int ok=0;
    int count=1;
    visited[start]=1;
    enqueue(start);

    while(left!=NULL){
        int v=left->x;
        dequeue();
        for(int i=0;i<n;i++){
            if((mat[v][i]==0 ||mat[v][i]==3) && visited[i]==0){
                visited[i]=1;
                count++;
                enqueue(i);
                if(mat[v][i]==3){
                    fprintf(f2,"%d  ",count);
                    ok=1;
                }
            }
        }
    }
    if(ok==0)
        fprintf(f2,"%d",-1);

}

int find2(int mat[10][10],int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<=n;j++)
        if(mat[i][j]==2)
        return i;
}

int main(int argc,char **argv)
{
    if(argv[1]!=NULL&&argv[2]!=NULL){

        f1=fopen(argv[1],"r");
        f2=fopen(argv[2],"w");
        int n;
        enqueue(0);
        fscanf(f1,"%d",&n);
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            fscanf(f1,"%d",&mat[i][j]);

        /*for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        printf("%d ",mat[i][j]);
        printf("\n");
        }*/

        int poz=find2(mat,n);
        //printf("\n%d",poz);
        BFS(mat,poz,n);

    }
}
