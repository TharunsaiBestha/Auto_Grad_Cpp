import torch
import numpy as np
X=torch.rand(4,requires_grad=True)
Y_real=torch.rand(4)
mean=torch.mean(X)
var=torch.var(X)
y=(X-mean)/(var**0.5)
t=((y-Y_real)**2)/2
out=t.sum()
mean.retain_grad()
var.retain_grad()
y.retain_grad()
t.retain_grad()
out.backward()
grad=y.cpu().detach().numpy()-Y_real.cpu().detach().numpy()
def back_prop(x,j,i,mean,var,B):
    temp=(-1/(B*var**0.5))+(-(x[i]-mean)**2/(B*var**1.5))
    if(i==j):
        return (var**-0.5)+temp
    else:
        return temp
def grad_gen(in_put,size):
    res=np.random.rand(size,size)
    for i in range(0,size):
        for j in range(0,size):
            res[j,i]=back_prop(in_put,j,i,in_put.mean(),in_put.var(),size)
    return res
            