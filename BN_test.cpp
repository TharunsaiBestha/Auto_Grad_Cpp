#include "NN_fun.h"
int main(){
    Matrix<double> X=read_from_file<double>("X.txt");
    Matrix<double> grad=read_from_file<double>("grad.txt");
    auto N_X=normalization(X);
    auto derv=BN_back_prop(grad,X,N_X.second);
    std::cout<<X;
    std::cout<<N_X.first;
    std::cout<<N_X.second;
    std::cout<<derv;
}