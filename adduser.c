#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "login_util.h"

#define BUFSIZE 128

int main()
{
    
    char cardID[BUFSIZE], username[BUFSIZE], password[BUFSIZE];
    printf(1, "[SCANNING ID CARD...]");
    gets_hidden(cardID, BUFSIZE);
    trim(cardID);

    printf(1, "Username:");
    gets(username, BUFSIZE);
    trim(username);

    printf(1, "Password:");
    gets(password, BUFSIZE);
    trim(password);

    int fd;
    if ((fd = open("/passwd", O_RDWR)) < 0) {
        printf(1, "[x] open passwd file failed\n");
        exit();
    }

    int n, id = 0;
    char buf_L[512];
    while ((n = read(fd, buf_L, sizeof(buf_L))) > 0) {
        for (int i = 0; i < n; ++i) {
            if (buf_L[i] == ';') {
                id = atoi(buf_L + i + 1);
                int tmp = id;
                while((tmp/=10) > 0 && ++i);
            }
        }
    }

    char* hash_pass = hashPasswd(password);
    printf(fd, "%s;%s;%s;%d;%d\n", cardID, username, hash_pass, id + 1, id + 1);

    close(fd);
    exit();
}