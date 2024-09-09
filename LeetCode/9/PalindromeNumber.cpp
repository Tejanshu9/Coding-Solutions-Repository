class Solution {
public:
    bool isPalindrome(int x) {
        std::string str = std::to_string(x);
        std::string str1="";
        size_t len=str.size();
        int i=len-1;
        while(i<len)
        {
            char ch=str[i];
            str1+=ch;
            i--;

        }
        return (str1==str);
            //return true;
        //else
            //return false;
        
    }
};