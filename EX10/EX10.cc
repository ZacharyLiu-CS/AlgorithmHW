#include <bits/stdc++.h>
using namespace std;
int uniform(int start ,int end ,int time = 0){
    if(time == 1)
        return 1;
    else
        return rand()%(end -start);
}
struct modElement{
    int param_a;
    int param_b;
    int square_root;
};
modElement mod_multiplicate(modElement ele1,modElement ele2,int mod){
    modElement res_element;
    assert(ele1.square_root == ele2.square_root);
    res_element.param_a = (ele1.param_a*ele2.param_a + ele1.param_b*ele2.param_b*ele1.square_root) % mod;
    res_element.param_b = (ele1.param_a* ele2.param_b + ele1.param_b*ele2.param_a) % mod;
    res_element.square_root = ele1.square_root;
    return res_element;
}
modElement mod_pow(modElement element,int mod, int power){
    modElement res_element(element);
    for(int i = 2; i <= power; i++){
        res_element = mod_multiplicate(res_element,element,mod);
    }
    return res_element;
}
void ext_gcd(int a,int b,int &d,int &x,int &y) {
    if(b == 0) {
        d = a; x = 1; y = 0;
        return;
    }
    ext_gcd(b,a % b,d,y,x);
    y -= a / b * x;
    return;
}
int rootLV(int x , int p){
    int a = uniform(1,p-1);
    if( a*a%p == x)
        return a;
    else{
        modElement element{param_a:a,param_b:1,square_root:x};
        auto res_mod = mod_pow(element,p,(p-1)/2);
        if(res_mod.param_b == 0){
            return false;
        }else{
            int x,y,d;
            ext_gcd(res_mod.param_b,p,d,x,y);
            if(d != 1)return false;
            else return (x+p)%p;
        }
    }
}
int main(){
    srand((unsigned)time(NULL));
    for(int i = 0; i < 10;i++)
        cout << rootLV(7,53) << endl;
    return 0;

}