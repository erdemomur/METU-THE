#include <stdio.h>

double calculate_pressure_on_block(int row, int column, double block_weight);

double calculate_pressure_on_block(int row, int column, double block_weight){
    if (row==0 && column==0){
        return 0;
        }
    if (row==1){
        return block_weight/2;
        }
    if (row>1 && (column==0 || column==row)){
        return block_weight/2 + (0.15)*calculate_pressure_on_block(row-1, column=0,block_weight);
    }
    if (row>1 && (column!=0 || column!=row)){
        return block_weight + (0.15)*calculate_pressure_on_block(row-1,column-1,block_weight) + (0.15)*calculate_pressure_on_block(row-1,column,block_weight);
    }
}
void print_func(int time,int weight,int row_2,int column_2){
    if(time==row_2){
        }
    else {
        printf("(%d,%d) %.8lf\n",row_2,column_2,calculate_pressure_on_block(row_2,column_2,weight));
        
        if(row_2==column_2){
            column_2=0;
            print_func(time,weight,row_2+1,column_2);
        }
        else{
            print_func(time,weight,row_2,column_2+1);
        }
    }
}

int main() {
    int N;
    int W;
    scanf("%d %d",&N,&W);
    print_func(N,W,0,0);
    return 0;
}