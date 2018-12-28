#include "types.h"
#include "stat.h"
#include "user.h"

#define abs(x)  ( (x<0) ? -x : x )

int main()
{
    printf(1, "Your uid: %d\n", abs(getuid()));
    ps();
    wait();
    exit();
    return 0;
}