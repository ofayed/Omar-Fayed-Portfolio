clc;clear all;close all;
% Part 3

% Filtering with the help of Convolution 
% Design of FIR highpass filter
w_c = input('Enter cut off frequency: ');
N = input('Enter tapsof filter: ');
a = (N-1)/2; % alpha
Tol = 0.001; % eps
n = 0:1:N-1; % samples
x = 0.42 - 0.5*cos((2*pi*n)/(N - 1)) + 0.08*cos((4*pi*n)/(N-1)); % Rectangular Window
h = sin(w_c*(n-a + Tol))./(pi*(n-a + Tol)); % Blackman Window
y = h.*x;    % convolution of  Rectangular Window and Blackman Window
figure; 
subplot(3,1,1)
stem(n,x)
xlabel('n')
ylabel('x[n]')
title('x[n]')
grid on

subplot(3,1,2)
stem(n,h)
xlabel('n')
ylabel('h[n]')
title('h[n]')
grid on

subplot(3,1,3)
stem(n,y)
xlabel('n')
ylabel('y[n]')
title('y[n]')
grid on

figure;
w = 0:0.01:pi;  % sampled frequncy 
freqz(y,1,w);   % frequency response