vector<int> z_function(string s) {
    int sz = s.size();
    vector<int> z_val(sz);
    int L = 0, R = 0;
    for(int i=1; i<sz; i++) {
        if(i <= R) {
            z_val[i] = min(R - i + 1, z_val[i - L]);
        }
        while(i + z_val[i] < sz && s[z_val[i]] == s[i + z_val[i]]) {
            z_val[i] ++;
        }
        if(i + z_val[i] - 1 > R) {
            L = i;
            R = i + z_val[i] - 1;
        }
    }
    z_val[0] = z_val.size();
    return z_val;
}
