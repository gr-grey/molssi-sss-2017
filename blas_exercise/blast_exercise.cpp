#include <fstream>
#include <iostream>
#include <vector>
#include <lawrap/blas.h>
#include <iomanip>

int main(){
    
	std::ifstream input("C.data");   
	
	std::vector<double> C(49);
    
    for(int i=0; i < 49; i++){

        input >> C[i];
    }


    std::vector<double> H(49);

	/* D(marked H here for complicated reasons) =  2 * C * C_transpose, but the data was arranged listed row by row, but gemm goes downwards, so we flip the two who's taking the transpose.
	parameters: 't' means take the transpose of matrix A (which is stored as a list of numbers, or a vector), 'n' means not transpose. then the 3 integers m n k, respresents the dimension of A B and C, A is m by k, B is k by n, c is m by n. Then float alpha is the constant term, then it's the pointer that points to the first element of (list) A, here, C.data is a function from including <vector>, it gives back the pointer of C and will be auto-released after C vanishes, then the Leading Demension of A, which is usually m but can be more (in the same way, ld_B is usually k but can be more, which is what happened in this case)
	Then the pointer of B, ld_B, then float beta, Pointer to C and ld_C.
	The function does C =  alpha* A * B + beta * C it doesn't return a value, the result is stored in matrix C!

	*/
    LAWrap::gemm('t', 'n', 7, 7, 5, 2.0, C.data(), 7, C.data(), 7, 0.0, H.data(), 7);


// /Users/Grey/Documents/SoftwareSummerSchool_2017/c++/blas_exercise 
	
	//Print the density matrix

	std::cout << "\n\nThe density matrix.\n";

	for(int i = 0; i < 49; i++ ) {

	std::cout << std::setw(11) << std::setprecision(4)  << H[i] << "    ";

	if ( (i+1) % 7 == 0 ) {std::cout << "\n";}

	}
	
	std::cout << "\n\n\n\n\n";




	//Read S.data
	std::ifstream input_2("S.data");    
        
    std::vector<double> S(49);
    
    for(int i=0; i < 49; i++){
       input_2 >> S[i];
	}   
	

	std::vector<double> T(49);
	LAWrap::gemm('n', 'n', 7, 7, 7, 1.0, H.data(), 7, S.data(), 7, 0.0, T.data(), 7);

	std::vector<int> tr_ls(7);
	double tr = 0;	

	// The indexes of the elements on the diagonal.
	for (int i = 0; i < 7; i++){
	tr_ls[i] = i*8;
	tr += T[tr_ls[i]];
	}	

	std::cout << "The trace of T is " << tr << std::endl;


    return 0;

}

