vector<complex<double>> reverse(vector<complex<double>> a)
{
    int n = a.size();
    vector<complex<double>> b(n);
    int p = __builtin_ctz(n);

    for (int i = 0; i < n; i++)
    {
        int num = 0;
        for (int j = 0; j < p; j++)
        {
            if (i & (1 << j))
            {
                num *= 2;
                num += 1;
            }
            else
            {
                num *= 2;
            }
        }
        b[i] = a[num];
    }
    return b;
}
vector<complex<double>> fft(vector<complex<double>> a, bool invert)
{
    int n = a.size();
    a = reverse(a);
    for (int i = 2; i <= n; i *= 2)
    {
        for (int j = 0; j < n; j += i)
        {
            int p = i / 2;
            complex<double> w = {1, 0};
            complex<double> wn = {cos(2 * M_PI / i), sin(2 * M_PI / i)};
            if (invert)
            {
                wn = {cos(-2 * M_PI / i), sin(-2 * M_PI / i)};

            }
            for(int k=j;k<j+p;k++){
                auto t=a[k];
                a[k]=a[k]+w*a[k+p];
                a[k+p]=t-w*a[k+p];
                w=w*wn;
            }
        }
    }
    return a;
}
vector<double> multiple(vector<int> a1, vector<int> b1)
{
    vector<complex<double>> a;
    vector<complex<double>> b;
    int n = a1.size();
    for (int i = 0; i < n; i++)
    {
        a.push_back({(double)a1[i], 0});
        b.push_back({(double)b1[i], 0});
    }
    n *= 2;
    while (__builtin_popcount(n) != 1)
    {
        n++;
    }

    a.resize(n);
    b.resize(n);
    vector<complex<double>> w1 = fft(a, false);
    vector<complex<double>> w2 = fft(b, false);
    for (int i = 0; i < n; i++)
    {
        w1[i] *= w2[i];
    }
    vector<complex<double>> ans= fft(w1,true);
    vector<double> sol;
    for(complex<double>& e:ans){
        sol.push_back(e.real()/n);
    }
    return sol;
}