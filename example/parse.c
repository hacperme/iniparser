#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "iniparser.h"

int main(int argc, char * argv[])
{
    dictionary * ini ;
    char       * ini_name ;

    if (argc<2) {
        ini_name = "twisted.ini";
    } else {
        ini_name = argv[1] ;
    }
#if CONFIG_INIPARSER_USE_FS
    ini = iniparser_load(ini_name);
    iniparser_dump(ini, stdout);
#endif
    iniparser_freedict(ini);

    return 0 ;
}
