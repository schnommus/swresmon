SwResMon - A resource monitoring app [CPU load, RAM, HDD etc] developed for/with Razer's Switchblade UI SDK.

This is the project directory+source of SwResMon, which is basically just a specialised, renamed SwitchbladeSFML binary

SwitchbladeSFML is a library (if you could consider it that) that I wrote for rendering to Switchblade devices using SFML.
SFML is an OpenGL-based simplified graphics library with routines for fonts, image loading, sprites etc.


DISTRIBUTION FOLDER

	1. If you only want to USE the thing, read the README in the \dist folder

DEPENDENCIES

	1. SwitchbladeSFML depends on SFML 2.0, Switchblade SDK 2.0, and Sigar (A resource monitoring library)

BUILDING
	
	1. In VS2010, Open the solution and change the include/lib directories to point to your SFML2, Switchblade and Sigar binaries, then, compile
	in release mode. (Debug mode doesn't seem to agree SFML very much so I don't recommend that).

	2. Emulating the switchblade screen is a compiler macro (Check the top of CApp.h). After enabling it, you can remove the RzSDK.lib dependencies.

	3. I haven't tried compiling the the program in an environment other than VS2010, but it shouldn't be too hard to get that working.


Legally, I'll say that the source is under the zlib license. Still, I'd enjoy some form of credit if you re-use my code :)

(C) Seb Holzapfel 2013
