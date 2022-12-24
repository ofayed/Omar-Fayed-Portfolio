clear all;
close all;
clc;
%x1 = input('Enter Input Sequence for Signal x1(n): '); n1=length(x1);
%x2 = input('Enter Input Sequence for Signal x2(n): '); n2=length(x2);
tint2 = 0;
tstep2 = 1;
tfinal2 = 10;
t = tint2 : tstep2 : tfinal2;
unitstep = t<=1 ;
x = unitstep ;n1=length(x);

h = exp(t+2) ;n2=length(h);
N = 2*tfinal2 -1; %Length of Convolved Sequence
T = -4:N-5; % Create Time Index
%Zero adding to make sequences of length N
x=[x zeros(1,N-n1)];
h=[h zeros(1,N-n2)];
%Initializing Output sequence of zeros.
y = zeros(1,N);
%Performing Linear Convolution:
for n = 1:N
 y(n) = 0;
for k = 1:n
 y(n)=y(n)+x(k)*h(n-k+1);
end
end
% Plot Input and Output Sequences:
subplot(3,1,1);
stem(T,x);
title('signal x[n]'); xlabel('n'); ylabel('x(n)');
subplot(3,1,2);
stem(T,h);
title('signal h[n]'); xlabel('n'); ylabel('h(n)');
subplot(3,1,3);
stem(T,y);
title('y(n) = x(n)*h(n)'); xlabel('n'); ylabel('y(n)');
% Display the convolved Sequence in Command Window
disp('Convolved sequence:');
disp(y);
