#include "sha256.h"
#include "user.h"

char* hashPasswd(char* pass)
{
    SHA256_CTX ctx;
    BYTE sha256buf[SHA256_BLOCK_SIZE];
    sha256_init(&ctx);
    sha256_update(&ctx, (BYTE*)pass, (size_t)strlen(pass));
    sha256_final(&ctx, sha256buf);

    static char hashed[SHA256_BLOCK_SIZE * 2 + 1] = { 0 };
    char hexMap[] = "0123456789ABCDEF";
    for (int i = 0; i < SHA256_BLOCK_SIZE; ++i) {
        hashed[i * 2] = hexMap[(int)(sha256buf[i] / 16)];
        hashed[i * 2 + 1] = hexMap[sha256buf[i] % 16];
    }
    return hashed;
}

int readPasswd(char* buf, char* cid_tmp, char* user_tmp, char* pass_tmp, char* uid_tmp, int n, int i)
{
    int now = 0;
    for (; buf[i] != ';' || i == n; i++, now++) {
        cid_tmp[now] = buf[i];
    }
    i++;
    cid_tmp[now] = '\0';
    if (i >= n) {
        printf(1, "Login: Parse passwd error\n");
        return -1;
    }

    now = 0;
    for (; buf[i] != ';' || i == n; i++, now++) {
        user_tmp[now] = buf[i];
    }
    i++;
    user_tmp[now] = '\0';
    if (i >= n) {
        printf(1, "Login: Parse passwd error\n");
        return -1;
    }

    now = 0;
    for (; buf[i] != ';' || i == n; i++, now++) {
        pass_tmp[now] = buf[i];
    }
    i++;
    pass_tmp[now] = '\0';
    if (i >= n) {
        printf(1, "Login: Parse passwd error\n");
        return -1;
    }

    now = 0;
    for (; buf[i] != '\n' && buf[i] != '\0'; i++, now++) {
        uid_tmp[now] = buf[i];
    }
    uid_tmp[now] = '\0';

    return i;
}