#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "login_util.h"

#define BUFSIZE 128

int checkID(char* cardID, char* username)
{
    if (cardID[strlen(cardID) - 1] == '\n')
        cardID[strlen(cardID) - 1] = '\0';

    int fd;
    if ((fd = open("/passwd", O_RDONLY)) < 0) {
        printf(1, "[x] Login: open passwd file failed\n");
        close(fd);
        return 0;
    }

    int n;
    char buf[512], cid_tmp[BUFSIZE], pass_tmp[BUFSIZE], id_tmp[BUFSIZE];
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < n; ++i) {
            i = readPasswd(buf, cid_tmp, username, pass_tmp, id_tmp, n, i);
            if (i == -1) break;

            if (!strcmp(cardID, cid_tmp) ) {
                int now = 0, id = 0;
                for (int i = 0; id_tmp[i] != ';' && id_tmp[i] != '\0'; i++, now++) {
                    id *= 10;
                    id += id_tmp[i] - '0';
                }
                return id;
            }
        }
        close(fd);
    }
    return -1;
}

int check(char* username, char* password)
{
    if (username[strlen(username) - 1] == '\n')
        username[strlen(username) - 1] = '\0';
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
            if (!strcmp(username, user_tmp) && !strcmp(hash_pass, pass_tmp)) {
                int now = 0, id = 0;

                for (int i = 0; id_tmp[i] != ';' && id_tmp[i] != '\0'; i++, now++) {
                    id *= 10;
                    id += id_tmp[i] - '0';
                }
                return id;
            }
        }
        close(fd);
    }
    return -1;
}

int main(void)
{
    printf(1, "[*] Meow! Time to login!\n");

    while (1) {
        char *cardID;
        char *username = {0};
        // char *password;
    
        char buf1[BUFSIZE] = {0};
        printf(1,"         -------------------------------------------------------------------------------- \n");
        printf(1,"        |+mmmNNNmmmmmmmmmmmmmmmmmmdddddddddddddddddmddmmmmmmN+                           |\n");
        printf(1,"        |yNmh+o+hNhysymhymmysddhhddhdddhhmdymdyhdmmmmmmmmmdmM+     o+-h//h/:-`   -+      |\n");
        printf(1,"        |hMo +y+`yo/-+dsysd::oh/-ssosyys+my/dh//yNmNNdhmN: -M+    `--`.``.`-.`   ``      |\n");
        printf(1,"        |dNN/`:`+NdhddddddmdhddhddddddddhhdmhmddNmN:   `oh. ss     /+.o:/d:+y`.`.+/      |\n");
        printf(1,"        |dNmNNmNNmNNNNmmNNNNmmmmmmmmmmmNNdNh/- `sNMh` .` `` .:                           |\n");
        printf(1,"        |mNmNNNNNNNNNNNNNNNNNNNNmmNNdmMy` Ny ``  .hMo .do`   `          .--::-.          |\n");
        printf(1,"        |mNmNNNNmNNNNNNNNNNNNNmydMo  `dy  Ns `d:   :m/ -NNyymo      .oyhdddddddhs.       |\n");
        printf(1,"        |mNmNNNNNNNNNNNNNhs/h+  `dy   `:  N+ `mMy../oNNNNNNNM+     -hddddhhdddddhdo`     |\n");
        printf(1,"        |mmmmNNNNNNhshMMm-  `Nh` `- :/   `m:`/NNNNNNNNNNNNNNM+    `hdho/-::---/yddds     |\n");
        printf(1,"        |NNNNd++Ms    -dMh   :Mm-   .Ms-+ymhhMMNNNNNNNMNNNNNM+    :mh-     `  ``.ymh`    |\n");
        printf(1,"        |/:. -oyM/ :/   +My   sMMo+sddshM/   hMNNNMNNNNMNNNNM+    `hy.```    ``.`:hs     |\n");
        printf(1,"        |o   :NMM- /My`  .y+:oddso+o:  `dd   .NMMMMMMMMMMMNNM+     ++.-:::---:::/-o+     |\n");
        printf(1,"        |M/   sMN` /MMmoydmMm+`.+ydNm`   /+   /MMMMMMMMMMMNNMo     --:-..-/-/.--:-:-     |\n");
        printf(1,"        |NN-  `Nm+smdy+:`-sN.  dMMMMMs   sM+ `:mMMMMMMMMMMMNMo     `.   ``` ``` ``.`     |\n");
        printf(1,"        |NMdohmyo:/-   hMysd`  -mMMd+s/ -+MMNMMMMMMMMMMMMMMNMo      ```  ```.` ``.`      |\n");
        printf(1,"        |h+/.   +mMd`   -+sMh.   ``:omMMMMMNhyNMMddMMMdhmMMNMo       ```.----.````       |\n");
        printf(1,"        |dodm.  `mMM+   os+.-NNmmNMMMMMMMMMMhyNMMdhNMMhydMMNMo        ````  `````        |\n");
        printf(1,"        |NNMMh   /MMN- -+ohNMMMMMMMMMMMMMMMmhdmdddddhmNddMMMMo        ``````````         |\n");
        printf(1,"        |NMmyh:   shyhhhhhhhhhhhhhhhhhhhhhhhhhhhhhddddddmMMNMo          ``````           |\n");
        printf(1,"        |NM:    nn nnn nnnn nnn  n nnn  nn n  nnnn      `NMMMo                           |\n");
        printf(1,"        |MM-    NN NNN NNNN NNN  N NNN  NN N  NNNN      `NMMMo     `:::`  -/-  `-:-      |\n");
        printf(1,"        |MN.    NN NNN NNNN NNN  N NNN  NN N  NNNN      `NMMMo     `/oo- `o+o. .yyh.     |\n");
        printf(1,"        |MN`    NN NNN NNNN NNN  N NNN  NN N  NNNN      `NMMMo  :-.--```..`.-``...-.```  |\n");
        printf(1,"        |MN+::::::::::::::::::::::::::-:::--------------/MMMMs  sy-yo ``o+/+++:+o++/+o/  |\n");
        printf(1,"        |hmmmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNMMNMMMMMMMMMMMs                           |\n");
        printf(1,"         `------------------------------------------------------------------------------ \n\n");
        printf(1, "[SCANNING ID CARD...]");

        cardID = gets_hidden(buf1, BUFSIZE);

        // char buf2[BUFSIZE] = {0};
        // printf(1, "[+] Password: ");
        // password = gets(buf2, BUFSIZE);

        dup(0); // stdout
        dup(0); // stderr

        int uid = -1;
        if ((uid = checkID(cardID, username)) >= 0) {
            printf(1, "[+] Login suceesfully.\n");
            printf(1, "\n\n\n");
            printf(1, "　　　　　　 ／ﾌﾌ 　　　　　　 　ム｀ヽ\n");
            printf(1, "　　　　　　/ ノ)　　 ∧∧　　　　　）　ヽ\n");
            printf(1, "　　　　　ﾞ/ ｜　　(´・ω・`）ノ⌒（ゝ._,ノ\n");
            printf(1, "　　　　　/　ﾉ⌒7⌒ヽーく　 ＼　／\n");
            printf(1, "　　　　　丶＿ ノ ｡　　 ノ､　　｡|/\n");
            printf(1, "　　　　　　　 `ヽ `ー-'_人`ーﾉ\n");
            printf(1, "　　　　　　　　 丶 ￣ _人'彡ﾉ\n");
            printf(1, "　　　　　　　　　ﾉ　　r'十ヽ/\n\n\n");

            int pid = fork();
            if(pid < 0) {
                printf(1, "login: fork failed.\n");
                exit();
            }
            if(pid == 0) {
                printf(1, "Hello, "); printf(1, username); printf(1, "\n");
                char* argv[] = { "sh", 0 };
                setuid(uid);
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