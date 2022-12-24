figure
hold on
y1=0;
y2=1;
xlabel('n');
ylabel('y(n)');
title('response');
stem(0,y1);stem(-1,y2);
for n=1:1:10
    y=((sqrt(2)/2)*y1)-(1/4*y2);
    stem(n,y);
    y2=y1;
    y1=y;
    
end