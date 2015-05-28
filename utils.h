#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gc.h>

/*
 * Search and replace a string with another string , in a string
 * */
static inline char *
str_replace (char const *search, char const *replace, char *subject)
{
  char *p = NULL, *old = NULL, *new_subject = NULL;
  int c = 0, search_size;

  if (search == NULL || replace == NULL)
    return subject;

  search_size = strlen (search);

  //Count how many occurences
  for (p = strstr (subject, search); p != NULL;
       p = strstr (p + search_size, search))
    {
      c++;
    }

  //Final size
  c = (strlen (replace) - search_size) * c + strlen (subject);

  //New subject with new size
  new_subject = malloc (c);

  //Set it to blank
  strcpy (new_subject, "");

  //The start position
  old = subject;

  for (p = strstr (subject, search); p != NULL;
       p = strstr (p + search_size, search))
    {
      //move ahead and copy some text from original subject , from a certain position
      strncpy (new_subject + strlen (new_subject), old, p - old);

      //move ahead and copy the replacement text
      strcpy (new_subject + strlen (new_subject), replace);

      //The new start position after this search match
      old = p + search_size;
    }

  //Copy the part after the last search match
  strcpy (new_subject + strlen (new_subject), old);

  return new_subject;
}

#define BUFLEN 256

/* Resolve aliases in current HOSTALIASES file, returns NULL in case of failure
  the char* returned need to be freed
  */
static inline char *
resolveAlias (const char *name)
{
  const char *eHostAliases =
    str_replace ("~", getenv ("HOME"), getenv ("HOSTALIASES"));
  if (eHostAliases != NULL && access (eHostAliases, R_OK) != -1)
    {
      FILE *f = fopen (eHostAliases, "r");
      char *buf = GC_MALLOC_ATOMIC(BUFLEN * sizeof(char));
      buf[BUFLEN - 1] = '\0';
      size_t len = strlen (name);
      while (fgets (buf, BUFLEN - 1, f))
	{
	  if (strncmp (buf, name, len < BUFLEN ? len : BUFLEN) == 0)
	    {
	      char *token = strtok (buf, " ");
	      while (token != NULL)
		{
		  token = strtok (NULL, " ");
		  if (token != NULL)
		    {
		      fclose (f);
		      return token;
		    }
		}
	    }
	}
      fclose (f);
    }
  return NULL;
}

#endif
