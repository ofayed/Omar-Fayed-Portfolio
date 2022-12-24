
clc;
close all;
clear all;
x= input('Enter the signal sequence x[n]: ');
N=input('Enter the length of the DFT:  ');
f=input('Choose filter 1.high pass 2. lowpass 3.bandpass');

if(f== 3)
     c=input('Enter two limits (enter high cut off first )');
else
    if (f ==2 )
        c=input('Enter cutoff');
    else
        c=input('Enter cutoff');
    end
end


len=length(x);
if N>len
    x=[x zeros(1,N-len)];
elseif N<len
    x=x(1:N);
end
i=sqrt(-1);
w=exp(-i*2*pi/N);
n=0:(N-1);
k=0:(N-1);
nk=n'*k;
W=w.^nk;
X=x*W;

if(f==3)
    for i=1:length(X)
        if (abs(X(i)) < c(1))
            X(i)= 0;
        else
            if(abs(X(i))> c(2));
                X(i)= 0;
          
            end
        end
    end
end
    
if (f ==1 )
    for i=1:length(X)
        if(abs(X(i))< c);
            X(i)= 0;
        
        end
    end
end
if (f ==2 )
    for i=1:length(X)
        if(abs(X(i))> c);
            X(i)= 0;
        
        end
    end
end   
disp(X);

subplot(211);
stem(k,abs(X));
title('Magnitude Spectrum');
xlabel('Discrete frequency');
ylabel('Amplitude');
grid on;
subplot(212);
stem(k,angle(X));
title('Phase Spectrum');
xlabel('Discrete frequency');
ylabel('Phase Angle');
grid on;