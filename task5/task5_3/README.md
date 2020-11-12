k1:exp(-(x-1)^2);
k2:exp(-(x-2)^2);
k3:exp(-(x-3)^2);
k4:exp(-(x-4)^2);
k5:exp(-(x-5)^2);
k6:exp(-(x-6)^2);
K:[k1,k2,k3,k4,k5,k6];

a1:2;
a2:2;
a3:1;
a4:1;
a5:2;
a6:2;
A:[a1,a2,a3,a4,a5,a6];

plot2d(A.K,[x,0,7]);
import -window "Gnuplot (window id:0)" task5_3.jpg
