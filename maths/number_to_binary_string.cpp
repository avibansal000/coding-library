string to_bin(long long x)
{
    if(x == 0)
        return "";
    else
    {
        string s = to_bin(x / 2);
        s.push_back(char('0' + x % 2));
        return s;
    }
}
ll to_num(string s){
    int n=s.length();
    ll k=1,i;
    ll sum=0;
    fi(i,0,n){
        sum+=(s[n-1-i]-'0')*k;
        k*=2;
    }

    return sum;
}