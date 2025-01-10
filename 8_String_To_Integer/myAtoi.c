// Solution by Matheus Sozza
// Leetcode: https://leetcode.com/problems/string-to-integer-atoi/description/
// Tried to solve with minimum memory usage, avoiding to create auxiliary variables or counters.
int myAtoi(char* s)
{
    #define MAX 2147483647
    #define MIN -2147483648
    
    int y = 0;

    // Discard trailing spaces
    while(s[0]==' ') s=&s[1]; 

    // Skip number signal
    if(s[0]=='-') 
    {
        s=&s[1];

        // Create number from string
        for(; s[0]>47 && s[0]<58; s=&s[1])
        {
            if (y < (MIN + (s[0]-48))/10) return MIN; // Min overflow
            y = (y*10) - (s[0]-48);
        } 
    } 
    else
    {
        if(s[0]=='+') s=&s[1];

        // Create number from string
        for(; s[0]>47 && s[0]<58; s=&s[1])
        {
            if(y > (MAX - (s[0]-48))/10) return MAX; // Max overflow
            y = (y*10) + (s[0]-48);
        } 
    }

    // Return considering the signal
    return y;
}