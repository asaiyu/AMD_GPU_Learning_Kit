#include <cfloat>
#include <iostream>
#include <limits>
#include <omp.h>

#define EPSILON (0.001)

#define HEIGHT 900
#define WIDTH 700

// C = AB
void matrixMultiply(float* C, float* A, unsigned int hA, unsigned int wA, float*B, unsigned int wB) {
    #pragma omp target data map(to: A[0:hA*wA], B[0:wA*wB]) map(from: C[0:hA*wB])
    #pragma omp target teams distribute parallel for collapse(2) schedule(static)
    for(unsigned int i=0;i < hA;i++) {
        for(unsigned int j=0;j < wB;j++) {
            float sum = 0;
            for(unsigned int k=0;k < wA;k++) {
                sum += A[i * wA + k]*B[k * wB + j];
            }
            C[i * wB + j] = sum;
        }
    }
}

int main(int, char**) {
    const unsigned int wA = 4;
    const unsigned int hA = 3;
    float a_test[hA*wA] = {
        29.3, 53.6, 31.3, 4.5,
        65.7, 29.2, 35.9, 22.1,
        79.3, 88.8, 23.7, 11.2
    };
    const unsigned int wB = 5;
    const unsigned int hB = 4;
    float b_test[hB*wB] = {
        23.5, 11.0, 44.4, 99.9, 13.3,
        12.1, 99.9, 69.9, 12.2, 0.0,
        86.3, 99.0, 10.0, 88.8, 33.0,
         1.2,  0.0, 34.4, 32.1,  0.0
    };
    float c_test[hA*wB];
    float c_check[hA*wB] = {
        4043.7 ,  8775.64,  5515.36,  6504.88,  1422.59,
        5021.96,  7193.88,  6077.4 , 10817.00,  2058.51,
        4996.78, 12089.72, 10350.32, 11469.51,  1836.79
    };

    // Run the test input
    matrixMultiply(c_test, a_test, hA, wA, b_test, wB);
    
    // Verify result
    for(int i=0;i<hA*wB;i++) {
        if(std::abs(c_test[i]-c_check[i]) > EPSILON) {
            std::cerr << "Testcase failed" << std::endl;
            std::cerr << "c[" << i << "] = " << c_test[i] << " != "
                << c_check[i] << std::endl;
        }
    }

    // Setup large inputs
    float A[HEIGHT*WIDTH];
    float B[WIDTH*HEIGHT];
    float C[HEIGHT*HEIGHT];

    for(int i=0;i<HEIGHT*WIDTH;i++) {
        A[i] = i;
        B[i] = i;
    }

    matrixMultiply(C, A, HEIGHT, WIDTH, B, HEIGHT);
}