#include <stdio.h>
#include <stdlib.h>
#include <string.h>    
#include <Windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include "module/mac_address.h"

#ifndef SECRET_KEY  /*when this program is compiled, SECRET_KEY must be defiened. it is random seed of two-factor authentication*/
#error SECRET_KEY is not defiened
#endif
#ifndef MAC_ADDRESS /*when this program is compiled, MAC_ADDRESS must be defiened. it is used to prevent from abusing*/
#error MAC_ADRESS is not defiened
#endif
#define echo(x) q(x)
#define WIN32_LEAN_AND_MEAN
#define q(x) #x
#define CHAR_SIZE 100

int verify(char mac_adress[]);

int main(int argc,char* argv[]){
    char secret_key[] = echo(SECRET_KEY);
    int key;
    int slash_adress;
    char winauth[CHAR_SIZE] ="python -m oathtool ";
    char apoptosis[CHAR_SIZE];
    char mac_address[CHAR_MAX];
    get_mac(mac_address);
    if(verify(mac_address)){
        strcat(winauth,secret_key);
        key = system(winauth);   /*one-time password is goten*/
        printf("%d",key);
    }
    else{
        printf("This program is moved into other PC. So, this program invoke safe guard"); /*abusing is detected*/
        sprintf(apoptosis,"rm %s",argv[0]);
        system(apoptosis);    /*suicide*/
    }
    return 0;
}

int verify(char mac_address[]){
    if(mac_address == MAC_ADDRESS){
         return 0;
    }
    else {
        return 1;
    }
}
