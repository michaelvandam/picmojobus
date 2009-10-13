/*********************************************
Reentrant version of strtok modified to function
on PIC18F microcontrollers
first param is from RAM
2nd param is from rom
char *contxt;
char *cmd;
cmd = strtok_r("testing=1","=",&contxt);  //cmd will  be equal to "testing"
param = strtok_r(0,"=",&contxt); //param will be equal to "1"
*********************************************/

#include "strtok_r.h"
#include <usart.h>
#include <string.h>


char * strtok_r(char *s1, const rom char *s2, char **lasts)
{
	char *ret;  //Value to be returned!
    
    if (s1==0) //If s1 is null use context from *lasts
		s1=*lasts; //Set s1 equal to context value
	while(*s1 && strchrpgm(s2, *s1))  //While s1 not null and s1 in s2
		++s1; //
	if(*s1=='\0')  //If we reached the end return null!
		return NULL;
	ret=s1;  //Or return value is now first char after match
	while(*s1 && !strchrpgm(s2,*s1)) //Loop till we find next char
		++s1;
	if(*s1)  //If not null but match!
		*s1++='\0';  //Set to null
	*lasts=s1; //Remember position
	return ret; //Return pointer
}


/*
char *strtok_r (char *s1, const rom char *s3, char **PreStr)
{
   char s2[50];
   char *Token;
   
   strcpypgm2ram(s2,s3);
   
   if (s1 == NULL)
      s1 = *PreStr;

   // Skip over leading delimiters
   s1 += strspn ((const char *)s1, s2);
   if (*s1 == '\0')
      return NULL;

   // Find the end of the Token.
   Token = s1;
   s1 = strpbrk ((const char *)Token, s2);
   if (s1 == NULL)
      // Point to null at end of string
      *PreStr = strchr ((const char *)Token, '\0');
   else
      {
      // Terminate Token. Set PreStr to next character
      *s1 = '\0';
      *PreStr = s1 + 1;
      }
   return Token;
}
*/
