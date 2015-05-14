#include <iostream>
using namespace std;
int a[1000001];
int main()
{
    int n,x,y,zz=1;
    while(cin >> n >> x >> y && n>=2)
    {
        a[0]=x; int k=1;
        bool valid=true;
        cout << "Case " << zz++ << ":";        
        if(y>n-1 || x>n-1) {cout << " No solution" << endl;continue;}
        if(x==0 && y==0) {cout << " " << 0 << endl;continue;}
        if(y<=0) {cout << " No solution" << endl;continue;}
        
        while(true)
        {
            // Detect a repeat.         
            if(k%2==0)
            {
                int kk=k/2;
                bool ok=false;
                for(int i=0;i<kk;i++)
                    if(a[i]!=a[kk+i]) {ok=true;break;}
                if(!ok) {valid=false; break;}
            }
            // mod n*y should cycle by now.
            if(k>n*y+5) {valid=false;break;}
            int carry=0;
            for(int i=0;i<k;i++)
            {
                int c=a[i]*y+carry;
                carry=c/n;
                a[i]=c%n;
            }
            if(carry==0 && a[k-1]==x && (k<2 || a[k-2]!=0)) break;
            for(int i=k;i>=1;i--) a[i]=a[i-1];
            a[0]=x;
            k++;
        }
        if(valid)
        {
            for(int i=k-2;i>=0;i--) cout << ' ' << a[i];
            cout << ' ' << a[k-1] << endl;
        }
        else 
        {
            cout << " No solution" << endl;
        }
    }
    return 0;
}
