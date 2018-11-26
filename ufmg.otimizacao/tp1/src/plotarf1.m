clear
clc
close

x=linspace(-2,2,250); 
y=linspace(-2,2,250);

[X,Y]=meshgrid(x,y);

for i=1:length(x)
    for j=1:length(y)
        Z(i,j) = objfun1([x(i) y(j)]);
    end
end

x0 = [-1.2 1.0]

%[vx, y, vncf] = gradmethod(x0, @objfun1);
[vx, y, vncf] = newtonmethod(x0, @objfun1);
%[vx, y, vncf] = quasenewtonmethod(x0, @objfun1);
%[vx, y, vncf] = conjgradmethod(x0, @objfun1);

contour(X,Y,Z,20);

hold on

plot(vx(:,1), vx(:,2), 'k-o');



