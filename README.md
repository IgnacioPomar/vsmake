# vsmake
**NOT WORKING**: The development is in its initial stages

tool to build Visual Studio C/C++ projects using gcc without conversions

## Motivation
When we work in visual studio and port to linux, it is a hassle maintain the 
Makefile, especially if the architecture is complex.

This tool is born with the desire to directly compile the solution.



## Requirements
This project has the following Dependencies:
- [TinyCppUnit](https://github.com/IgnacioPomar/TinyCppUnit) (only for unit-testing)


## Authors
- Ignacio Pomar Ballestero



## Building
Building using itself:
```
./vsmake vsmake.sln
```

Building using make:
```
make
make install
```

## pragmalib


## Roadmap
This is the roadmap for this project:
- **V 0.1.0** : The project will compile basic solutions and projects (using itself as test project)
- **V 0.2.0** : the project will compile only the changed cpp files
- **V 0.3.0** : The support of external XML with properties with changes (for example, versioning)
- **V 0.4.0** : The project will add a sqlite database with the includes used by a cpp, and so, making a better selection of files who must be recompiled
- **V 0.?.0** : To be defined...
- **V 1.0.0** : The project will include a second utility to "install" the results of the project




## License
There are some separated parts of the project wich comes from stackOverflow 
snnipets (or simmilar sources). They are listed in utils.h

### Parts and licenses
The files with diferent license are marked in the file itself.

Other parts snippets
License :  [CC BY-SA 3.0](http://creativecommons.org/licenses/by-sa/3.0/)
- [Snnipet one](http://stackoverflow.com/a/236803/74785) Author [Evan Teran](http://stackoverflow.com/users/13430/evan-teran)

License : [zlib License](https://en.wikipedia.org/wiki/Zlib_License)
- [TinyXML-2](https://github.com/leethomason/tinyxml2)

License :  public domain
- [realpath Win32 implementation](https://sourceforge.net/p/mingw/patches/_discuss/thread/3e5aad79/cda5/attachment/realpath.c) Author By Nach M. S.

### Main License

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>


