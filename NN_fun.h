#include "Matrix.h"
template<typename T>
void back_propagation_row(typename std::vector<T>::iterator start_in,typename std::vector<T>::iterator end_in,typename std::vector<T>::iterator start_out,
    typename std::vector<T>::iterator end_out){
        std::size_t n=std::distance(start_in,end_in);
        Matrix<T> res(n,n);
        Matrix<T> out(n,1);
        Matrix<T> in(n,1);
        std::vector<T>& v_out=out.get_vector();
        std::vector<T>& v_in=in.get_vector();
        std::size_t a=0;
        for(auto i=start_out;i!=end_out;++i){
            v_out[a]=*i;
            a++;
        }
        a=0;
        for(auto i=start_in;i!=end_in;++i){
            v_in[a]=*i;
            a++;
        }
        for(std::size_t i=0;i<n;i++){
            for(std::size_t j=0;j<n;j++){
                res(i,j)=(i==j)?out(i,0)*(1-out(i,0)):-out(i,0)*out(j,0);
            }
        }
        a=0;
        out=res*in;
        for(auto i=start_out;i!=end_out;++i){
            *i=v_out[a];
            a++;
        }
    }
template<typename T>
auto Softmax(Matrix<T>& in){
        Matrix<T> output;
        std::size_t n=in.dim().second;
        std::vector<T> temp_vec(in.dim().first);
        std::size_t j=0;
        auto fun=[](T& a,T& b){return a+std::exp(b);};
        auto fun2=[&](T x){return std::exp(x)/temp_vec[j];};
        auto start=in.get_vector().begin();
        auto end=in.get_vector().begin();
        for(std::size_t i=0;i<in.dim().first;i++){
            std::advance(end,n);
            temp_vec[i]=std::accumulate(start,end,T{},fun);
            std::advance(start,n);
        }
        start=in.get_vector().begin();
        end=in.get_vector().begin();
        for(j=0;j<in.dim().first;j++){
            std::advance(end,n);
            std::transform(start,end,start,fun2);
            std::advance(start,n);
        }
        output=in;
        return output;
}
template<typename T>
auto Softmax_backpropagation(Matrix<T>& in,Matrix<T>& output){
Matrix<T> out;
        out=output;
        auto start_out=out.get_vector().begin();
        auto end_out=out.get_vector().begin();
        auto start_in=in.get_vector().begin();
        auto end_in=in.get_vector().begin();
        std::size_t n=out.dim().second;
        for(std::size_t i=0;i<in.dim().first;i++){
            std::advance(end_in,n);
            std::advance(end_out,n);
            back_propagation_row<T>(start_in,end_in,start_out,end_out);
            std::advance(start_in,n);
            std::advance(start_out,n);
        }
        return out;
}
template<typename T>
Matrix<T> mean_back_prop(Matrix<T>& grad,Matrix<T>& para){
    Matrix<T> res(1,grad.dim().first);
    T temp;
    for(int i=0;i<grad.dim().first;i++){
        temp=0;
        for(int j=0;j<grad.dim().second;j++){
            temp+=grad(i,j);
        }
        res(0,i)=-temp/std::sqrt(para(1,i));
    }
    return res;
}
template<typename T>
Matrix<T> input_back_prop(Matrix<T>& grad,Matrix<T>& para){
    Matrix<T> res(grad.dim().first,grad.dim().second);
    for(int i=0;i<grad.dim().first;i++){
        for(int j=0;j<grad.dim().second;j++){
            res(i,j)=grad(i,j)/std::sqrt(para(1,i));
        }
    }
    return res;
}
template<typename T>
Matrix<T> var_back_prop(Matrix<T>& grad,Matrix<T>& input,Matrix<T>& para){
    Matrix<T> temp_m(grad.dim().first,grad.dim().second);
    Matrix<T> diff(grad.dim().first,grad.dim().second);
    Matrix<T> res(grad.dim().first,grad.dim().second);
    Matrix<T> temp_mean;
    T temp;
    for(int i=0;i<grad.dim().first;i++){
       temp=(-2*std::pow(std::sqrt(para(1,i)),3));
       temp=1/temp; 
        for(int j=0;j<grad.dim().second;j++){
            temp_m(i,j)=temp*(input(i,j)-para(0,i))*grad(i,j);
            diff(i,j)=input(i,j)-para(0,i);
        }
    }
    temp_mean=mean(temp_m,true);
     for(int i=0;i<grad.dim().first;i++){
        for(int j=0;j<grad.dim().second;j++){
            res(i,j)=2*temp_mean(0,i)*diff(i,j);
        }
     }
     return res;
}
template<typename T>
Matrix<T> BN_back_prop(Matrix<T>& grad,Matrix<T>& input,Matrix<T>& para){
    bool flag=para(2,3)<=0;
    T m,var,temp;
    T wrt_mean;
    Matrix<T> wrt_var,wrt_x,diff;
    Matrix<T> temp_m,temp_v,temp_x,dummy,temp_row;
    Matrix<T> temp_res(grad.dim().first,grad.dim().second);
    if(!flag){
        m=para(0,0);
        var=para(1,0);
        dummy=mean(grad);
        wrt_mean=(-1/std::sqrt(var))*dummy(0,0);
        wrt_x=(1/std::sqrt(var))*grad;
        temp=(-2*std::pow(std::sqrt(var),3));
        temp=1/temp;
        diff=input-m;
        temp_m=temp*dot_prod(diff,grad);
        dummy=mean(temp_m);
        wrt_var=2*dummy(0,0)*diff;
        return wrt_x+wrt_var+wrt_mean;
    }
    else{                                               //Requires testing when flag is true;
        temp_x=input_back_prop(grad,para);
        temp_m=mean_back_prop(grad,para);
        temp_v=var_back_prop(grad,input,para);
        temp_row.set_dim(grad.dim().first,grad.dim().second);
        for(int i=0;i<grad.dim().first;i++){
            for(int j=0;j<grad.dim().second;j++){
                temp_row(i,j)=temp_x(i,j)+temp_m(0,i)+temp_v(i,j);
            }
        }
        return temp_row;
    }
}
template<typename T>
auto SE(Matrix<T>& in,Matrix<T> real_output){
    auto Square_Error=[](T out,T real_out){
        return (out-real_out)*(out-real_out)/2.0;
    };
    Matrix<T> res(in.dim().first,in.dim().second);
        Transform(in,real_output,res,Square_Error);
        return res;
}
template<typename T>
auto SE_backpropagation(Matrix<T>& in,Matrix<T>& real_output){
    auto Square_Error_backpropagation=[](T out,T real_out){
        return (out-real_out);
    };
    Transform(in,real_output,in,Square_Error_backpropagation);
    return in;}
