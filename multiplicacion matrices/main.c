
using namespace std;

int main( )
{
  int af, ac, bf, bc, i, j, k;
  
  int A[af][ac], B[bf][bc], C[af][bc]; 
   
 
  for(i=0;i<af;i++){
      for(j=0;j<bc;j++){
          C[i][j]=0;
          for(k=0;k<ac;k++){
              C[i][j]=(C[i][j]+(A[i][k]*B[k][j]));
          }
      }
  }
  
}
