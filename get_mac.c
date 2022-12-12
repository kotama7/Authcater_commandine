#include <stdio.h>
#include <limits.h>
#include "module/mac_address.h"

int main(void){
    char mac_address[CHAR_MAX];
    get_mac(mac_address);
    printf("%s",mac_address);
    return 0;
}