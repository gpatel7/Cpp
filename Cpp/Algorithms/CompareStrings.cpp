#include <iostream>
using namespace std;

void check(char *a, char *b, int (*cmp) (const char*, const char*));
int numcmp(const char *a, const char *b);
int main()
{
       char s1[80], s2[80];
       gets (s1);
       gets (s2);
       if (isalpha(*s1))
                check(s1, s2, strcmp);
       else
                check(s1, s2, numcmp);
       return 0;
}
void check(char *a, char *b, int (*cmp) (const char*, const char*))
{
	cout << ” Testing for equality \n”;
	if(!(*cmp)(a,b)) 
		cout << “ Equal”;
	else
		cout << “ Not Equal”;
}
int numcmp(const char *a, const char *b)
{
	if(atoi(a) == atoi(b))
		return 0;
	else
		return 1; 
}
