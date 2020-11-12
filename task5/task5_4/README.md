k1:exp(-(x-1)^2);
k2:exp(-(x-1)^2);
k3:exp(-(x-3)^2);
k4:exp(-(x-3)^2);
k5:exp(-(x-2)^2);
K:[k1,k2,k3,k4,k5];

a1:1;
a2:2;
a3:2;
a4:1;
a5:2;
A:[a1,a2,a3,a4,a5];

plot2d(A.K,[x,0,7]);

import -window "Gnuplot (window id:0)" task5_4.jpg
