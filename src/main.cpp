#include <iostream>
#include "ImageMatrix.h"
#include "Convolution.h"
#include "ImageLoader.h"

using namespace std;


int main(){
    const string filePath = "../data/output.txt";

    // Create a matrix directly using direct initialization
    const double* directData1[3] = {
        new double[3]{1.0, 2.0, 3.0},
        new double[3]{4.0, 5.0, 6.0},
        new double[3]{7.0, 8.0, 9.0}
    };

    ImageMatrix matrix1(directData1, 3, 3);    

    //Print the matrix elements
    cout << "Matrix 1: " << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "[ ";
        for (int j = 0; j < 3; ++j) {
            cout << matrix1.get_data(i, j) << " ";
        }
        cout << "]" << endl;
    }

    ImageLoader imageLoader(filePath);

    ImageMatrix matrix2(filePath);

    cout << "Matrix 2: " << endl;
    for (int i = 0; i < imageLoader.getHeight(); ++i) {
        cout << "[ ";
        for (int j = 0; j < imageLoader.getWidth(); ++j) {
            cout << matrix2.get_data(i, j) << " ";
        }
        cout << "]" << endl;
    }


}
