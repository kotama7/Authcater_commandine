#include <windows.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
    
#pragma comment(lib, "WS2_32")
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi")
    
#define IP_LOCALHOST    0x0100007F

    
 void get_mac(char* mac_address)
 {
   ULONG nSize = 0;
   MIB_IPADDRTABLE * ip_table = NULL;
   if (GetIpAddrTable(ip_table, &nSize, 0) == ERROR_INSUFFICIENT_BUFFER)
   {
       ip_table = (MIB_IPADDRTABLE *) malloc(nSize);
       if (GetIpAddrTable(ip_table, &nSize, 0) == NO_ERROR)
       {
           for (int i = 0; i < ip_table->dwNumEntries; ++i)
           {

               if (IP_LOCALHOST != ip_table->table[i].dwAddr)
               {
                   MIB_IFROW iInfo;
                   BYTE byMAC[6] = { 0, 0, 0, 0, 0, 0 };
                   memset(&iInfo, 0, sizeof(MIB_IFROW));
                   iInfo.dwIndex = ip_table->table[i].dwIndex;
                   GetIfEntry(&iInfo);
                   if (MIB_IF_TYPE_ETHERNET == iInfo.dwType)
                   {
                        memcpy(&byMAC, iInfo.bPhysAddr, iInfo.dwPhysAddrLen);
                        sprintf(mac_address,"%02x%02x%02x%02x%02x%02x",byMAC[0],byMAC[1],byMAC[2], byMAC[3],byMAC[4],byMAC[5]);
                   }
               }
           }
       }
       else
           printf("unable to read IP table from system\n");
       free(ip_table);
   }
   else
       printf("unable to determine number of entries in IP table\n");
 }