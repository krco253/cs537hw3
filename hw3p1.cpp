#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

typedef vector<vector<float> > matrix;

//----------------HELPER FUNCTIONS---------------
// Transpose
void transpose(matrix &arr, matrix &result, int size){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			result[j][i] = arr[i][j];
		}
	}

}
//Forward substitution
void forward_sub(matrix &A, vector<float> &b, vector<float> &y, int size){
	for (int i = 0; i < size; i++){
		float sum = 0;
		for (int j = 0; j < i; j++){
			sum = sum + A[i][j] * y[j];
		}
		y[i] = (b[i] - sum)/ A[i][i];
	}
}
//--------------CHOLESKY's METHOD----------------
//template<typename T, size_t size>
void CholeskysMethod(matrix &A, int n, matrix &lower_matrix){

	//--------------Initialize L 
	//float lower_matrix[n][n];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
		lower_matrix[i][j] = 0;
		}
	}
	//-------------
	for (int k = 0; k < n; k++){
		float sum = 0;
		for (int s = 0; s < k; s++){
			sum = sum + lower_matrix[k][s] * lower_matrix[k][s];
		}
		lower_matrix[k][k] = sqrt(A[k][k] + sum);

		//-----------
		for (int i = k+1; i < n; i++){
			float sum2 = 0;
			for (int s = 0; s < k; s++){
				sum2 = lower_matrix[i][s] * lower_matrix[k][s];
			}
			lower_matrix[i][k] = (A[i][k] - sum2)/ lower_matrix[k][k];
		}
	}
	return;
}	
//------------------MAIN-----------------------
int main(){

//-----------------------------Generate test matrices	
for (int size = 20; size < 120; size+=20){
	matrix array (size, vector<float>(size, 0));
	matrix lower (size, vector<float>(size, 0));
	for (int i = 0; i < size; i++){
		for (int k = 0; k < size; k++){
			if (i == k){
				array[i][k] = 4;
			}
			if (i+1 == k){	
				array[i][k] = 1;
			}
			if (i == k+1){
				array[i][k] = 1;
			}

		}
	}
//-------------------------------------apply cholesky's
	CholeskysMethod(array, size, lower);
//find the transpose
	matrix lower_transpose (size, vector<float>(size, 0));
	transpose(lower, lower_transpose, size);
//forward substitution
	vector<float> y (size, 0);
	vector<float> b (size, 6);
	b[0] = 5;
	b[size - 1] = 5;
	forward_sub(array, y, b, size);
	if (size == 20){	
	//cout << "Size: " << size << endl << endl;
	for (int i = 0; i < size; i++){
		//for (int j = 0; j < size; j++){
			cout << y[i] << " ";
		//}
		cout << endl;
	}
	}

}
	return 0;
}
