#include <iostream>
#include "BigDecimalInt.h"
#include "algorithm"
int main() {
    while (true) {
        int v3 = -(rand()+10000000000000000);
        string s= to_string(v3);
        BigDecimalInt obj (s);
        int v4 = - (rand()+99999999999);
        s= to_string(v4);
        BigDecimalInt obj1 (s);
        if((obj1+obj ) .numbers !=  to_string((v4 +v3)) && (obj1-obj ) .numbers !=  to_string((v4 -v3)) )
        {
            cout<<v3<<" "<<v4 ;
            break;
        } else
        {
            cout<<v3<<" "<<v4<<" ok!"<<endl;
        }

    }

}
