#include <stdio.h>
#include "../TLSLibrary/vault.h"
int main(int argc, char const *argv[])
{
    char *vault;
    getVaultStr(vault, argv[1]);
    return 0;
}
