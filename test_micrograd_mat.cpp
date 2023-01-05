#include "micrograd.h"
#include <iostream>
int main(){
    Matrix<double> X=read_from_file<double>("X_val.txt");
    Matrix<double> W=read_from_file<double>("W_val.txt");
    Matrix<double> Y=read_from_file<double>("Y_val.txt");
    Value<Matrix<double>> X_val(X);
    Value<Matrix<double>> W_val(W);
    Value<Matrix<double>> Y_val(Y);
    Value<Matrix<double>> out;
    out=W_val*X_val;
    out.grad=X;
    backpropagate(&out);
    std::cout<<W_val.grad;
    std::cout<<out.grad*transpose(X);
}