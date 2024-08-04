#include <stdio.h>
#include <utmpx.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

#define __USE_GNU

int main(void)
{

struct utmpx * utmpx = {0};
char user[__UT_NAMESIZE+1] = {0};
char host[__UT_HOSTSIZE+1] = {0};
time_t epochtime = 0;

#ifndef POSIX
char v6host[INET6_ADDRSTRLEN+1] = {0};
const char * v6_string = NULL;
#endif

setutxent();

while((utmpx = getutxent())!=NULL)
    {
    (void) memset(user,0,__UT_NAMESIZE+1);
    (void) memset(host,0,__UT_HOSTSIZE+1);
    
    if ( utmpx->ut_user != NULL
         && utmpx->ut_type == USER_PROCESS
         && utmpx->ut_host[0] !=0 )
         {
         (void) memcpy(user,utmpx->ut_user,__UT_NAMESIZE);
         (void) memcpy(host,utmpx->ut_host,__UT_HOSTSIZE);
         
         epochtime = utmpx->ut_tv.tv_sec;

/* this code from utmpdump(1) */
#ifndef POSIX
    if (utmpx->ut_addr_v6[1]
        || utmpx->ut_addr_v6[2]
        || utmpx->ut_addr_v6[3]
        ) v6_string = inet_ntop(AF_INET6,
                                &(utmpx->ut_addr_v6),
                                v6host,
                                sizeof(v6host)
                                );
    else
        v6_string = inet_ntop(AF_INET,
                                &(utmpx->ut_addr_v6),
                                v6host,
                                sizeof(v6host)
                                );
#endif

#ifndef POSIX
         printf("%s\n\t%s\t%s\n\t%s\n", /* ctime() adds the newline */
                 user,
                 asctime(localtime(&epochtime)),
                 host,
                 v6_string
                 );
#else
         printf("%s\n\t%s\t%s\n",
                 user,
                 asctime(localtime(&epochtime)),
                 host
                 );
#endif

        }
    }

return 0;
}
