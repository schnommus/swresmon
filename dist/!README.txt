SwResMon - A resource monitoring app [CPU load, RAM, HDD etc] developed for/with Razer's Switchblade UI SDK.

RUNNING THE APP

	1. If your switchblade device is cooperating with the computer nicely, running SwResMon.exe should be all you need to do!

	2. However, I've compiled a version that emulates the screen (without dependency on razer drivers) if you don't have a device handy.
	This is a little experimental though, I haven't actually tested the emulator on a device without razor drivers (only with the thing unplugged)
	Technically it SHOULD work - the binary compiled without linking to the Razer SDK libraries.

CUSTOMIZING THE APP

	1. The file 'SwResMon.cfg' is read on startup, and if you open it in notepad++/etc you'll see it's just plain text with instructions like this:	

		FontName=neuropolitical.ttf


		UpdateInterval=0.25


		ForcedSleep=0.0

		
SelectedHDD=C:\

		Text2_Red=255

		Text2_Green=255

		Text2_Blue=255

		Text2_Alpha=120  etc etc..

	2. So just go ahead and edit these values. There are some sample themes in 'alternate_themes', so you can look at those for inspiration, or use
	them directly by copying the config contents back into 'SwResMon.cfg' and sticking their corresponding font in the same directory as the
	executable. (Note the fonts used in alternate_themes aren't allowed for commercial use, but the default one is)

	3. These values are case/formatting sensitive! Imitate what's there and it'll work.

TROUBLESHOOTING

	1. Any meaningful error messages are sent to 'SwitchbladeSFMLAppLog.txt' when the application is run


[more details + ask questions + get C++ source] in the Razer Developer Forum post :D

(C) Seb Holzapfel 2013
