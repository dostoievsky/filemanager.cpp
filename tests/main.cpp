#include <cassert>

int square(int x){return x*x;}

void 
test1()
{
   assert(square(1)==1);
   assert(square(2)==4);
}

int 
main()
{
    test1();
    return 0;
}
