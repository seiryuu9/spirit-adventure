How to run Spirit adventure on Windows
(requires installed MinGW)

1. unzip the game on your desired path

2. download MinGW-w64 
for example here https://winlibs.com/ - download the zip file, make a new folder C:\mingw64 and extract the zip file in it

3. We need to add MinGW64 to PATH 
right-click: This PC → Properties → Advanced system settings → Environment Variables → Path → Edit → New
Paste C:\mingw64\bin (or whatever your path)

4. Now open Windows Powershell 
if you want to check if your GCC works now, run gcc --version
otherwise, change your directory to where you extracted the game 

	run cd C:/path/to/game/spirit_adventure

 	then run gcc main.c src/*.c -I include -o adv.exe


5. now you should have an exe file of my game, so now to start the game you run

\.adv -n <username> (to create a new game) 
or \.adv -l <username> (to load your save)


enjoy !! <3




