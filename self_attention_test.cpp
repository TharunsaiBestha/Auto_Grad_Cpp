#include "micrograd.h"
int main(){
    Matrix<double> Wv=read_from_file<double>("Wv.txt");
    Matrix<double> Wq=read_from_file<double>("Wq.txt");
    Matrix<double> Wk=read_from_file<double>("Wk.txt");
    Matrix<double> X=read_from_file<double>("X.txt");
    Matrix<double> Y_real=read_from_file<double>("Y_real.txt");
    Value<Matrix<double>> WV(Wv);WV.label="WV";
    Value<Matrix<double>> WQ(Wq);WQ.label="WQ";
    Value<Matrix<double>> WK(Wk);WK.label="WK";
    Value<Matrix<double>> X_IN(X);X_IN.label="X_IN";
    Value<Matrix<double>> Y_REAL(Y_real);Y_REAL.label="Y_REAL";
    Value<Matrix<double>> Q,K,V,T0,T1,T2,T3,T4,T5,out;
    Q=WQ*X_IN;
    K=WK*X_IN;
    V=WV*X_IN;
    T0=K.T();
    T1=T0*Q;
    T2=T1.T();
    T3=T2.softmax();
    T4=T3.T();
    T5=V*T4;
    out=T5.Square_Error(Y_REAL);
    Q.label="Q";K.label="K";V.label="K";T0.label="T0";T1.label="T1";T2.label="T2";T3.label="T3";T4.label="T4";out.label="out";
    backpropagate(&out);
    std::cout<<"WQ_gradients"<<"\n"<<WQ.grad;
    std::cout<<"WK_gradients"<<"\n"<<WK.grad;
    std::cout<<"WV_gradients"<<"\n"<<WV.grad;
}