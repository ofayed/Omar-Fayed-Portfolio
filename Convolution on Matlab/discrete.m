clc
clear
close all
 
n= -25:25;
 x= cos(2*pi*n/.3).*(n>=0);
 h= (cos(pi*n/.3)+(sin(pi*n/3)/sqrt(3))).*(n>=0);
 subplot(3,1,1)
 stem(n,x);
 subplot(3,1,2)
 stem(n,h);

for i=1:length(n)
    Y(i)=0;
    for j=1:numel(n)
        if(i-j+1>0)
            Y(i)=Y(i)+x(j)*h(i-j+1);
        else
        end
    end
end

 n1 = -25:length(Y)-1-25;
 subplot(3,1,3)
 stem(n1,Y);