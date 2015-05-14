#include <iostream>
void printSet (int array[],int size)
{
    int i;
    for (i=1;i<=size;i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
    return;
}
void printPowerset (int n)
{
    int stack[10],k;
    stack[0]=0; /* 0 is not considered as part of the set */
    k = 0;
    while(1){
        if (stack[k]<n){
            stack[k+1] = stack[k] + 1;
            k++;
        }
        else{
            stack[k-1]++;
            k--;
        }
        if (k==0)
            break;
        printSet(stack,k);
    }
    return;
}
int main(){
    printPowerset(4);
    return 0;
}
