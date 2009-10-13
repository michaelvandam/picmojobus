#include <ctype.h>
    
int isNumeric(const char *p) {

    if (*p) { 
       char c;
       while ((c=*p++)) {
            if (!(isdigit(c))) return 0;
       }
       return 1;
    }
    return 0;
}
