#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "login_util.h"

#define BUFSIZE 128

int check(char* username, char* password)
{
    if (username[strlen(username) - 1] == '\n')
        username[strlen(username) - 1] = '\0';
    if (password[strlen(password) - 1] == '\n')
        password[strlen(password) - 1] = '\0';


    int fd;
    if ((fd = open("/passwd", O_RDONLY)) < 0) {
        // printf(1, "fd = %d\n", fd);
        printf(1, "[x] Login: open passwd file failed\n");
        close(fd);
        return 0;
    }

    int n;
    char buf[512], user_tmp[BUFSIZE], pass_tmp[BUFSIZE], id_tmp[BUFSIZE];
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < n; ++i) {
            i = readPasswd(buf, user_tmp, pass_tmp, id_tmp, n, i);
            if (i == -1) break;

            char* hash_pass = hashPasswd(password);
            if (!strcmp(username, user_tmp) && !strcmp(hash_pass, pass_tmp)) {
                // if (write(writefd, id_tmp, sizeof(AID)) <= 0)
                //     printf(1, "error\n");
                int now = 0, id = 0;
                // int mod = 0;

                for (int i = 0; id_tmp[i] != ';' && id_tmp[i] != '\0'; i++, now++) {
                    id *= 10;
                    id += id_tmp[i] - '0';
                }
                return id;
            }
        }
        close(fd);
    }
    return 0;
}

int main(void)
{
    printf(1, "\n\n\n");
    printf(1, "　　　　　　 ／ﾌﾌ 　　　　　　 　ム｀ヽ\n");
    printf(1, "　　　　　　/ ノ)　　 ∧∧　　　　　）　ヽ\n");
    printf(1, "　　　　　ﾞ/ ｜　　(´・ω・`）ノ⌒（ゝ._,ノ\n");
    printf(1, "　　　　　/　ﾉ⌒7⌒ヽーく　 ＼　／\n");
    printf(1, "　　　　　丶＿ ノ ｡　　 ノ､　　｡|/\n");
    printf(1, "　　　　　　　 `ヽ `ー-'_人`ーﾉ\n");
    printf(1, "　　　　　　　　 丶 ￣ _人'彡ﾉ\n");
    printf(1, "　　　　　　　　　ﾉ　　r'十ヽ/\n\n\n");
    printf(1, "[*] Meow! Time to login!\n");
    char* argv[] = { "sh", 0 };

    while (1) {
        char *username, *password;
    
        char buf1[BUFSIZE] = {0};
        printf(1, "[+] Username: ");
        username = gets(buf1, BUFSIZE);

        char buf2[BUFSIZE] = {0};
        printf(1, "[+] Password: ");
        password = gets(buf2, BUFSIZE);

        dup(0); // stdout
        dup(0); // stderr

        int uid = -1;
        if ((uid = check(username, password))) {
            printf(1, "[+] Login suceesfully.\n");

            int pid = fork();
            if(pid < 0){
                printf(1, "login: fork failed.\n");
                exit();
            }
            if(pid == 0){
                setuid(uid);
                printf(1, "Hello, %s.\n", username);
                exec("sh", argv);
                printf(1, "login: exec sh failed\n");
                exit();
            }
            wait();
            
            printf(1, "Goodbye %s.\n", username); 
        } else {
            printf(1, "[x] Login failed.\n");
        }
    }

    exit();
}