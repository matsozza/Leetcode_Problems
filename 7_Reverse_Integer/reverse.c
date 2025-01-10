// Solution by Matheus Sozza
// Leetcode: https://leetcode.com/problems/reverse-integer/description/

int reverse(int x)
{
    int y = 0;
    
    while(x!=0)
    {

        if(((10*(long long)y + x%10) > 2147483647) && x>0)
        {
            return 0;
        }
        else if(((10*(long long)y + x%10) < -2147483648) && x<0)
        {
            return 0;
        }
        else
        {
            y = (y*10) + (x%10);      
            x /= 10;
        }
    }

    return y;
}