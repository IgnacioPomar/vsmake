/*********************************************************************************************
 *	Name		: winutils.cpp
 *	Description	: Windows functions to replace instead of unix equivalents
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	- Taken from public domain
 ********************************************************************************************/


#include <stdlib.h> //Outside ifdef to avoid intellisense errors

#ifdef WIN32

#include <stdio.h>
#include <errno.h>

//The dirname() function may return a pointer to static storage that may then be overwritten by subsequent calls to dirname().
//Well... i dont like it but... here it comes
char dirname_buffer[_MAX_PATH];

//see http://pubs.opengroup.org/onlinepubs/009695399/functions/dirname.html
char *dirname(const char *path)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];


	_splitpath (path, drive, dir, NULL, NULL);
	_makepath (dirname_buffer, drive, dir, NULL, NULL );
	
	return dirname_buffer;
}





//see http://pubs.opengroup.org/onlinepubs/009695399/functions/realpath.html
//see https://sourceforge.net/p/mingw/patches/256/
char *realpath( const char *name, char *resolved )
{
  char *retname = NULL;  /* we will return this, if we fail */

  /* SUSv3 says we must set `errno = EINVAL', and return NULL,
   * if `name' is passed as a NULL pointer.
   */

  if( name == NULL )
    errno = EINVAL;

  /* Otherwise, `name' must refer to a readable filesystem object,
   * if we are going to resolve its absolute path name.
   */

  //else if( access( name, 4 ) == 0 )
  else if (1) //In Windows we will only test, so... we dont need to check access
  {
    /* If `name' didn't point to an existing entity,
     * then we don't get to here; we simply fall past this block,
     * returning NULL, with `errno' appropriately set by `access'.
     *
     * When we _do_ get to here, then we can use `_fullpath' to
     * resolve the full path for `name' into `resolved', but first,
     * check that we have a suitable buffer, in which to return it.
     */

    if( (retname = resolved) == NULL )
    {
      /* Caller didn't give us a buffer, so we'll exercise the
       * option granted by SUSv3, and allocate one.
       *
       * `_fullpath' would do this for us, but it uses `malloc', and
       * Microsoft's implementation doesn't set `errno' on failure.
       * If we don't do this explicitly ourselves, then we will not
       * know if `_fullpath' fails on `malloc' failure, or for some
       * other reason, and we want to set `errno = ENOMEM' for the
       * `malloc' failure case.
       */

      retname = (char*) malloc( _MAX_PATH );
    }

    /* By now, we should have a valid buffer.
     * If we don't, then we know that `malloc' failed,
     * so we can set `errno = ENOMEM' appropriately.
     */

    if( retname == NULL )
      errno = ENOMEM;

    /* Otherwise, when we do have a valid buffer,
     * `_fullpath' should only fail if the path name is too long.
     */

    else if( (retname = _fullpath( retname, name, _MAX_PATH )) == NULL )
      errno = ENAMETOOLONG;
  }

  /* By the time we get to here,
   * `retname' either points to the required resolved path name,
   * or it is NULL, with `errno' set appropriately, either of which
   * is our required return condition.
   */
  
  return retname;
}


#endif
