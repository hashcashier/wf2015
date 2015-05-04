/*
1. BASE >= alphabets, MOD = Prime
2. Don't use 'a' or 'A' with their 0 values; BAD: str[i] - 'A'
3. Better use 2 prime numbers for MOD
4. Some primes: 100003, 100021, 1000000007, 1000000009, 1000000000039, 2000000000003, 3000000000013, 4000000000039, 34027797218763967LL
*/

#define BASE 107
#define MOD 34027797218763967LL

string text, pattern;
long long hp = 0, ht = 0;
long long EXP = 1;

long long int_mod(long long a, long long b) {
    return (a % b + b) % b;
}

int main() {
    for(int i=0; i<pattern.size(); i++) {
        hp = int_mod(hp * BASE, MOD);
        hp = int_mod(hp + pattern[i], MOD);
        if(i != 0) {
            EXP = int_mod(EXP * BASE, MOD);
        }
        ht = int_mod(ht * BASE, MOD);
        ht = int_mod(ht + text[i], MOD);
    }
    if(ht == hp) {
        //MATCH!
    }
    for(int i=pattern.size(); i<text.size(); i++) {
        long long SUB = int_mod(text[i - pattern.size()] * EXP, MOD);
        ht = int_mod(ht - SUB, MOD);
        ht = int_mod(ht * BASE, MOD);
        ht = int_mod(ht + text[i], MOD);
        if(ht == hp) {
            //MATCH!
        }
    }
}
