clear;clc
Filter_type=input('The filter type ( =1 for low pass, =2 for bandpass, =3 for high pass, =4 for stop band) = ');
n=input('The FIR filter order = ');
fc=input('Cut off frequency = ');
fs=input('Sampling frequency = ');
x_n=input('The input samples = ');
L=max(n+1,length(x_n));     % required length of the DTFT
if Filter_type==1
    h_n = fir1(n,2*fc/fs,'low');       % The impulse responce of the LPF
elseif Filter_type==2
    h_n = fir1(n,2*fc/fs,'bandpass');       % The impulse responce of the BPF
elseif Filter_type==3
    h_n = fir1(n,2*fc/fs,'high');       % The impulse responce of the HPF
elseif Filter_type==4
    h_n = fir1(n,2*fc/fs,'stop');       % The impulse responce of the SPF
end
X_k=My_DTFT(x_n,L);
H_k=My_DTFT(h_n,L);
Y_k=X_k.*H_k;
y_n=My_IDTFT(Y_k);

figure
f=(0:(1/L):(1-1/L))*fs;
subplot(3,1,1);plot(f,abs(H_k));grid on;xlim([0 fs/2])
title('Magnitude of the frequency responce')
subplot(3,1,2);plot(f,20*log10(abs(H_k)));grid on;xlim([0 fs/2])
title('Magnitude of the frequency responce in dB')
subplot(3,1,3);plot(f,angle(H_k)*180/pi);grid on;xlim([0 fs/2])
title('Angle of the frequency responce in degree')
xlabel('f in Hz')

figure;
n_x=(1:length(x_n))-1;
subplot(3,1,1);stem(n_x,x_n);xlabel('t');ylabel('x(n)');grid on
n_h=(1:length(h_n))-1;
subplot(3,1,2);stem(n_h,h_n);xlabel('t');ylabel('h(n)');grid on
n_y=(1:length(y_n))-1;
subplot(3,1,3);stem(n_y,real(y_n));xlabel('t');ylabel('y(n)');grid on

