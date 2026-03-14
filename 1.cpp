#include <iostream>
#include <string>
#include <vector>
#include "NCint.hpp"

std::string getPermutationAfterN(NCint<> n,std::string chatset) {
    static std::vector<NCint<>> jiecheng;
    static bool initialized = false;
    if(!initialized) {
        jiecheng.push_back(NCint<>(1)); // 0!
        for (int i = 1; i <= 300; i++) {
            jiecheng.push_back(jiecheng.back() * NCint<>(i));
        }
        initialized = true;
    }
    int sizen=chatset.size();
    NCint<> jiecheng_sizen(1);
    for(int i=1;i<=sizen;i++){
        jiecheng_sizen=jiecheng_sizen*(NCint<>)(i);
    }
    n=n%jiecheng_sizen;
    std::string result="";
    std::vector<char> chars;
    int max_jiecheng_id=1;
    std::string ret="";
    for(;jiecheng[max_jiecheng_id]<=n;max_jiecheng_id++);
    max_jiecheng_id--;
    for(int i=max_jiecheng_id;i>0;i--){
        NCint<> index=n/jiecheng[i];
        ret.push_back(chatset[(int)(index)]);
        chatset.erase(chatset.begin()+(int)(index));
        n-=index*jiecheng[i];
    }
    return ret;
}

using namespace std;
int main() {
    NCint<> n;
    string charset;
    cin >> n >> charset;
    cout << getPermutationAfterN(n, charset) << endl;
    return 0;
}