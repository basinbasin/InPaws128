# InPaws128
A fork of [Mastadon's](https://github.com/Mastodon-/inpaws) original 80's Gilsoft PAW compiler for PC, with additional features.

Additional functionality:

1) For ZX Spectrum output, applying a z value will move z percent of the messages and locations in a game to ram page 1 in the Spectrum.
This should allow conversions from The Quill for example, to run in the 128K version of PAW without having to truncate any data.

Example command:

*inpaws128 c "C:\output_pawmac.paw" -o "C:\output_paw.tap" -z 35*

will create a tap file with 35% of the location and message text moved to ram page 1.


2) Compiling with the CF command will create a DSF file output that can then be used in DAADReady to create a DAAD version of the game.

Example command:

*inpaws128 cf "C:\test.paw" -o "C:\test.dsf"*


3) Change to output filename
The filename(s) output into the final tap file has been changed to be *just* the filename before the filename suffix, rather than the file path, mainly because it was easier to
type this into a Spectrum emulator than having to type, for example, c:\my_location and needing to go into extended mode etc. on the Speccy keyboard.

Example:

*c:\my_adventure\myoutputa.tap* will appear in the final tap file (what you'll need to enter as a filename to load into PAW) as
*c:\my_adv in InPaws*
*myoutputa in InPaws128*

The original version of InPaws is written in c++ and Spanish. I am unfamiliar with either language, so my changes are almost certainly going to be badly-written hacks. 

I'm making the source available because people are, quite rightly, wary of downloading unsigned exe files, so those of you with the ability can compile your own version.
