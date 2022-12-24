clc
clear
close all

tint2 = 0;
tstep2 = 0.0005;
tfinal2 = 10;
t = tint2 : tstep2 : tfinal2;
unitstep = (6>t) ;
X = unitstep;
H = square(t) ;

%H = 400 * exp( (-400*t) ); 
subplot( 4, 1, 1);
 plot( t, X);
 title('signal x(t)'); xlabel('t'); ylabel('x(t)');
 subplot( 4, 1, 2);
 plot( t, H);
 title('signal h(t)'); xlabel('t'); ylabel('h(t)');

for i=1:length(t)
    Y(i)=0;
    for j=1:numel(t)
        if(i-j+1>0)
            Y(i)=Y(i)+X(j)*H(i-j+1);
        else
        end
    end
end
subplot( 4, 1, 3);
 plot( t, Y);
 title('y(t) = x(t)*h(t)'); xlabel('t'); ylabel('y(t)');
 y2=conv(X,H);
 subplot( 4, 1, 4);
 plot(y2);
