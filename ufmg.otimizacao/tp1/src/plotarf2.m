clear
clc
close

x0 = [5 5 5 5 5 5 5 5 5 5];

[vx1, y1, vncf1] = gradmethod(x0, @objfun2);
[vx2, y2, vncf2] = newtonmethod(x0, @objfun2);
[vx3, y3, vncf3] = quasenewtonmethod(x0, @objfun2);
[vx4, y4, vncf4] = conjgradmethod(x0, @objfun2);

plot(vncf1, y1)
hold on
plot(vncf2, y2)
hold on
plot(vncf3, y3)
hold on
plot(vncf4, y4)
hold on

legend('gradmethod', 'newtonmethod', 'quasenewtonmethod', 'conjgradmethod')
xlabel('ncf')
ylabel('f(x)')