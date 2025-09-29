# Hangman Game
Guess the word correctly before the man hangs

## Dependencies
This project uses 
- [SDL3](https://wiki.libsdl.org/SDL2/FrontPage)
- [SDL3_ttf](https://wiki.libsdl.org/SDL2_ttf/FrontPage)
- [SDL_image](https://wiki.libsdl.org/SDL3_image/FrontPage)
- [libcurl](https://curl.se/libcurl/)
- *Note*:
   - The fonts used in this project are found in the C:/Windows/Fonts folder
   - The dictionary file is included here; without it, one would be created and would require libcurl to pull from the thesaurus API


### Setup Instructions
#### SDL3
1. Download SDL3, SDL_Image, and SDL3_ttf development libraries.
2. Place the `include` and `lib` folders for both libraries in a known location.
3. Update your project settings in Visual Studio:
   - **VC++ Directories**:
     - **Include Directories**: `path/to/SDL3/include`; `path/to/SDL3_ttf/include`; `path/to/SDL3_image/include`
     - **Library Directories**: `path/to/SDL3/lib/64`; `path/to/SDL3_ttf/lib/64`; `path/to/SDL3_image/lib/64`
   - **Linker > Input**: Add `SDL3.lib`; `SDL3_image.lib`; `SDL3_ttf.lib`

#### libcurl
*VCPKG is used to install libcurl*
##### VCPKG
You can follow [this link here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell#1---set-up-vcpkg) for specific instructions.
1. clone the repository: 
---
    git clone https://github.com/microsoft/vcpkg.git
---
2. Navigate to the vcpkg directory and run the bat script
---
    cd vcpkg; .\bootstrap-vcpkg.bat
---
4. Now you have set the environment variables so that visual studio/your current terminal knows where to find it (you will have to set these for every new session, unless you update your system environment variables): 
> powershell
```
   	$env:VCPKG_ROOT = "C:\path\to\vcpkg" \
   	$env:PATH = "$env:VCPKG_ROOT;$env:PATH"
```
5. Now run the install command to add libcurl: 
> console/VS terminal
```
	vcpkg install curl:x64-windows
```
6. Update the build installation (For visual studio specifically): 
> console/vs terminal
```
	vcpkg integrate install
```
7. If in visual studio, you will need to restart it
<br/>
<br/>
