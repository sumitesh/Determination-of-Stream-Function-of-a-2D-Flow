
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
   
   //Defining grid size
   int M = 19, N = 19;              //M = Rows & N = Columns
   int count = 0;
   
   //Defining variables
   float phi[M][N], phi_dummy[M][N];
   float dx = 1;
   float dy = 1;
   float beta = dx/dy;
   float error = 0;
   
   //Boundary Conditions
   
   //Left wall
   for(int i=0; i<M; i++){
      
      phi[i][0] = 0;
   }
   
   //Top wall
   for(int i=0; i<N; i++){
      
      phi[M-1][i] = 0;
   }
   
   //Bottom wall before hole
   for(int i=0; i<5; i++){
      
      phi[0][i] = 0;
   }
   
   //Bottom wall after hole
   for(int i=5; i<N; i++){
      
      phi[0][i] = 100;
   }
   
   
   //Initial Conditions
   
   for(int i=0+1; i<M-1; i++){
      for(int j=0+1; j<N-1; j++){
         
         phi[i][j] = 0;
         //printf("\t%.2f", phi[i][j]);
      }
      //printf("\n");
   }
   
   //Right wall
   for(int i=0; i<M; i++){
      
      phi[i][N-1] = phi[i][N-2];
   }
   
   do{
     
     error = 0;
     
     for(int i=0+1; i<M-1; i++){
      for(int j=0+1; j<N-1; j++){
         
         phi_dummy[i][j] = phi[i][j];
         phi[i][j] = (1/(2*(1+pow(beta,2))))*((pow(beta,2)*phi[i][j-1]) + phi[i-1][j] + phi[i+1][j] + (pow(beta,2)*phi[i][j]));
         
         //Updating Right wall
         phi[j][N-1] = phi[j][N-2];
         
         //Calculating error
         error += pow(fabs((phi[i][j] - phi_dummy[i][j])/((M-2)*(N-2))), 0.5);
      }
     }
     
   }while(error > pow(10,-3));  //error > pow(10,-3)    //count < pow(10,3)
   
      
   FILE* file;
   file = fopen("Stream_Lines.txt", "w");
   
   for(int i=M-1; i>=0; i--){
      for(int j=0; j<N; j++){
         
         fprintf(file,"%.2f\t",phi[i][j]);
      }
      fprintf(file,"\n");
   }
   
   
   

   fclose(file);
   return 0;
}






