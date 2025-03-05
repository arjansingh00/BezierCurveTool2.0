## Quickstart guide

### Instructions to run this application on Windows and to be able to compile with Microsoft Visual Studio 2022:

#### 1) Download GLUT (glut.h, glut32.lib, and glut32.dll) from (https://www.opengl.org/resources/libraries/glut/glut_downloads.php#windows).

#### 2) Extract the downloaded GLUT .zip file to a folder on your computer.

#### 3) Copy Files to the Appropriate Locations:

Copy glut.h to your Microsoft Visual Studio include directory and create the GL folder if it doesn't exist:

> *C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.40.33807\include\GL*

Copy glut32.lib to the library directory:

> *C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.40.33807\lib\x86*

Copy glut32.dll to the correct system-wide directory:

> *C:\Windows\System32 (for 64-bit systems)*

> *C:\Windows\SysWOW64 (for 32-bit systems, if applicable)*

#### 4) Visual Studio project configuration:

Open Project Properties by right-clicking on your project in the Solution Explorer and selecting Properties. 

   1. Under Configuration Properties > VC++ Directories : Add the path to your GLUT include directory in Include Directories.

   2. Under Configuration Properties > VC++ Directories : Add the path to your GLUT lib directory in Library Directories.

   3. Under Configuration Properties > Linker > Input: Add glut32.lib to the Additional Dependencies field.

   4. Copy glut32.dll to the output directory Make sure glut32.dll is either in the same folder as your .exe.

#### 5) Debug with the platform set as x86.
