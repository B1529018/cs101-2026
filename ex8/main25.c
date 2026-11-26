#include <stdio.h>

int main()
{
   int var=20;
   int* ip;
   
   ip=&var;
   
   printf("Addres of var:%p\n",&var);
   printf("Value of ip:%p\n",ip);
   printf("Addres of ip:%p\n",&ip);
   printf("Value of ip*:%d\n",*ip);

    return 0;
}
