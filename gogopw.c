#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "login_util.h"

#define BUFSIZE 128

#define abs(x)  ( (x<0) ? -x : x )

int check(char* password)
{
    if (password[strlen(password) - 1] == '\n')
        password[strlen(password) - 1] = '\0';

    int fd;
    if ((fd = open("/passwd", O_RDONLY)) < 0) {
        printf(1, "[x] Login: open passwd file failed\n");
        close(fd);
        return 0;
    }

    int n;
    char buf[512], cid_tmp[BUFSIZE], user_tmp[BUFSIZE], pass_tmp[BUFSIZE], id_tmp[BUFSIZE];
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < n; ++i) {
            i = readPasswd(buf, cid_tmp, user_tmp, pass_tmp, id_tmp, n, i);
            if (i == -1) break;
            
            char* hash_pass = hashPasswd(password);
            int now = 0, id = 0;

            for (int i = 0; id_tmp[i] != ';' && id_tmp[i] != '\0'; i++, now++) {
                id *= 10;
                id += id_tmp[i] - '0';
            }

            if (!strcmp(hash_pass, pass_tmp) && abs(getuid()) == id) {
                return 1;
            }
        }
        close(fd);
    }
    return 0;
}

int main(void)
{
    printf(1, "[*] Go go power ranger!\n");
    
    char *password;

    char buf[BUFSIZE] = {0};
    printf(1, "[+] Password: ");
    password = gets(buf, BUFSIZE);

    if (check(password)) {
        int pid = fork();
        if(pid < 0) {
            printf(1, "gogopw: fork failed.\n");
            exit();
        }
        if(pid == 0) {
            printf(1, "You are a power ranger!\n");
            int uid = getuid();
            setuid(abs(uid));
            char* argv[] = { "sh", 0 };
            exec("sh", argv);
            printf(1, "gogopw: exec sh failed\n");
            exit();
        }
        wait();
        printf(1, "Power down :3 \n"); 

    } else {
        printf(1, "You can't be a power ranger :(\n");
    }
    
    exit();
}