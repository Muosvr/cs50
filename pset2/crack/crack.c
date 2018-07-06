#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#define _XOPEN_SOURCE

int
main(void){
  /* Hashed form of "GNU libc manual". */
//   const char *const pass = "$1$/iSaq7rB$EoUw5jJPPvAPECNaaWzMK/";
    const char *const pass = "50JGnXUgaafgc"; //the salt is 50

  char *result;
  int ok;

//   do{

//   }while()

  /* Read in the user’s password and encrypt it,
     passing the expected password in as the salt. */
  result = crypt(get_string("Password:"), pass);

  /* Test the result. */
  ok = strcmp (result, pass) == 0;

//   puts(ok ? "Access granted." : "Access denied.");
//   return ok ? 0 : 1;
     printf("%i\n",ok) ;
}