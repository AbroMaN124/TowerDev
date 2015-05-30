# TowerDev
Open-source tower defence game for developers

abrarfurqan@hotmail.com
or
zxac062@live.rhul.ac.uk

note: models not currently uploaded, game will not install sucessfuly.

CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Gameplay
 * Controls
 * Installation
 * Troubleshooting
 * Contact
 * Resources
 * Reports and Documentation


INTRODUCTION
---------------------

This is the readme for the Tower Defence Game in Linux project.
Please read it for gameplay instructions, game requirements, game installation, game configuration and troubleshooting.

GAMEPLAY
---------------------

Stop creeps reaching the finishing line on the left side of the map by placing towers! Remember towers cost money - so spend wisely!
Win 5 rounds to win the game! One creep gets to the finish line and you'll lose!
	

CONTROLS
---------------------

The controls for the game are as followed:

The controls for the game are as followed:
Exit Game: 		ESCAPE
Start Game: 		SPACE

Move up: 		W
Move down: 		D
Move left: 		A
Move right:		D
Place Type1 Tower: 	1
Place Type2 Tower:	2

Camera Controls:
Move forward:		I
Move backward:	K
Turn right:		L
Turn Left:		J
Rotate upward:		O
Rotate downward:	U


INSTALLATION
---------------------

Follow these installtion instructions.
Note: These intructions are tailored for Ubuntu 14.04,
	other distributions may vary.

1. Install utility dependencies
Use the following code in a terminal:
sudo apt-get install build-essential automake libtool cmake

2. Install Ogre3D dependencies
Use the following code in a terminal:
sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev 
	freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev libxt-dev libpng12-dev 
	libglew1.6-dev

3. Install Ogre3D 
Follow these installation instructions.
Note: These instructions are tailored for Ubuntu 14.04, other Linux distributions may vary.
for distribution specific prerequisites dependencies see:
http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Prerequisites&tikiversion=Linux

1. Install utility dependencies
Use the following commands in a terminal:
sudo apt-get install build-essential automake libtool cmake
sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
sudo apt-get install nvidia-cg-toolkit libois-dev libboost-thread-dev graphviz libcppunit-dev

2. Install Ogre3D 
 * Go to the OgreSDK directory and run the cmake (through the terminal)
	-- note: I prefer to create a Build subdirectory within the directory to build within
 * Make, use maximum cores to decrease make time:
	make -j`getconf _NPROCESSORS_ONLN`
	-- note: this will take a while, sorry!
 * Make install:
	sudo make install

3. Compile game using CMake
 * Go to the osratch directory and run the cmake (through the terminal)

4. Run the game
 * The executable is now ready to be run, it can be found in /osratch/dist/bin and is called ./OgreApp



TROUBLESHOOTING

---------------------
Solutions to common problems:

 * I do not have Linux Ubuntu and cant follow the instructions for my distribution
Solution: Linux Ubuntu is a free Linux/GNU distibution. Simply install it,
		if you do not wish to install Ubuntu on your system use a Virtual Machine
 		(e.g. VirtualBox) and install Linux Ubuntu on there.

 * The program does not run besides be following Installation and Configuration instructions
Solution: Please make sure you meet all the requirement. I would recommend ensuring your graphics drivers
		are up-to-date and following the Installation/Configuration instructions again. Make sure you


CONTACT
---------------------

If you wish to contact me, particularly if you are unable to run the program please contact me on:
zxac062@live.rhul.ac.uk or abrarfurqan@hotmail.com

RESOURCES
---------------------

Linux/GNU Ubuntu: http://www.ubuntu.com/
CMake: http://www.cmake.org/
Ogre3d: http://www.ogre3d.org/
Code::Blocks: http://www.codeblocks.org/
Doxygen: http://www.doxygen.org/
OIS: http://sourceforge.net/projects/wgois/
Boost: http://www.boost.org/

REPORTS AND DOCUMENTATION
----------------------

to be uploaded


Created by AbroMaN124
(Ahmad Abrar Furqan)
