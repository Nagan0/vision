load(descriptive);
a:read_matrix("data_odd.txt");
b:read_matrix("data_even.txt");
v:cov(a);
w:cov(b);
g:(v+w)^^-1;
m_a:mean(a);
m_b:mean(b);
m_m:m_a - m_b;
m_m.g;
