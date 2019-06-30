# vsmake
**NOT WORKING**: The development is in its initial stages

tool to build Visual Studio C/C++ projects using gcc without conversions

## Motivation
When we work in visual studio and port to linux, it is a hassle maintain the 
Makefile, especially if the architecture is complex.

This tool is born with the desire to directly compile the solution.



## Requirements
This project has the following Dependencies:
- Boost Test Library
- libxml2  library


It is necessary to keep the libbrary in the following structure:
```
$(SolutionDir)../vc/$(PlatformShortName)/include/
$(SolutionDir)../vc/$(PlatformShortName)/lib/
$(SolutionDir)../vc/$(PlatformShortName)/dll/
```

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



## License
There are some separated parts of the project wich comes from stackOverflow 
snnipets (or simmilar sources). They are listed in utils.h

### Parts and licenses
The files with diferent license are marked in the file itself.

Other parts snippets
License :  [CC BY-SA 3.0](http://creativecommons.org/licenses/by-sa/3.0/)
- [Snnipet one](http://stackoverflow.com/a/236803/74785) Author [Evan Teran](http://stackoverflow.com/users/13430/evan-teran)

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


