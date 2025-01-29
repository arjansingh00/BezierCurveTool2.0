Instructions to run this application on Windows and to be able to compile with Microsoft Visual Studio 2022:

1. Download GLUT
Download just (glut.h, glut32.lib, and glut32.dll) from (https://www.opengl.org/resources/libraries/glut/glut_downloads.php#windows).

2. Extract the Files
Extract the downloaded GLUT zip file to a folder on your computer.

3. Copy Files to the Appropriate Locations

Header File (glut.h)
Copy glut.h to your Visual Studio include directory:

C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.40.33807\include\GL

Create the GL folder inside the include directory if it doesn’t exist.

Library File (glut32.lib)
Copy glut32.lib (or freeglut.lib) to the library directory:

C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.40.33807\lib\x86

Dynamic Link Library (glut32.dll)
Copy glut32.dll to:
C:\Windows\System32 (for 64-bit systems).
C:\Windows\SysWOW64 (for 32-bit systems, if applicable).
Alternatively, place it in the same directory as your executable file for project-specific use.

4. Configure Visual Studio Project
Create a New Project
Open Visual Studio and create a new project (C++ Console Application or similar).
Include GLUT Header
Add #include <GL/glut.h> to your source code.
Set Project Properties
Open Project Properties by right-clicking on your project in the Solution Explorer and selecting Properties.
Under Configuration Properties > VC++ Directories:
Add the path to your GLUT include directory in Include Directories.
Add the path to your GLUT lib directory in Library Directories.
Under Configuration Properties > Linker > Input:
Add glut32.lib to the Additional Dependencies field.

5. Copy glut32.dll to the output directory
Make sure glut32.dll is either in the same folder as your .exe.

