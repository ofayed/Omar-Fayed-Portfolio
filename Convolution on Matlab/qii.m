figure
hold on
y1=0;
y2=1;
xlabel('n');
ylabel('y(n)');
title('response');
stem(1,y1);stem(0,y2);
for n=2:1:10
    y=(2*y1)-(1*y2);
    stem(n,y);
    y2=y1;
    y1=y;
    
end