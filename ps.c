#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    printf(1, "Your uid: %d\n", getuid());
    ps();
    wait();
    exit();
    return 0;
}