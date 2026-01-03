operator =(const int& val){
            data.clear();
            data.push_back(0);
            bool sign = (val<0)?true:false;
            long long absval = (sign)?-(long long)(val):(long long)(val);
            if(absval == 0){
                return *this;
            }
            while(absval > 0){
                data.push_back(absval % 10);
                absval /= 10;
            }
            data[0] = sign ? -(data.size()-1) : (data.size()-1);
            return *this;
        }