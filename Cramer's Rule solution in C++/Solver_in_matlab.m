a = input('Enter the size of the matrix:');
b = a;
for i=1:a
for j=1:b
m(i,j)=input(sprintf('Enter row %d, column %d element',i,j));
end
end
for i=1:a
c(i)=input(sprintf('Enter coef %d',i));
end
disp('The matrix you entered is: ')
m=reshape(m,a,b);
d=det(m);
fprintf('The determinent is: %d', d)
if d == 0
disp('The matrix is not invertible.')
else
disp('The matrix is invertible, and here is the inverse:')
i=inv(m);
end
disp('Thank you!')
disp(Cramers_Rule(m, c));
%disp(Cramers_Rule(mat, coefficients));
function[answer] = Cramers_Rule(A,b)
len = length(b);
result = zeros(len,1);
determinent = det(A);
if A==0
error('No Solution')
elseif determinent==0
error('No Solution')
end
for i=1:len
Aug=A;
Aug(:,i) = b;
result(i) = (det(Aug)/determinent);
end
answer = result;
end
