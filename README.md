What is MESSUI?
===============

MESS (Multi Emulator Super System) is the sister project of MAME. MESS documents the hardware for a wide variety of (mostly vintage) computers, video game consoles, and calculators, as MAME does for arcade games. (see https://github.com/mamedev/mame)

MESSUI has an inbuilt front-end allowing you to choose a system from a list. MESSUI comes with NEWUI, which is a drop-down menu system, similar to what you get with any Windows program.


How to compile?
===============

You can only build MESSUI on a Windows computer. It won't compile on Unix.

```
make TARGET=mess OSD=winui
```


Where can I find out more?
=============

* [Official MAME Development Team Site](http://mamedev.org/) (includes binary downloads for MAME and MESS, wiki, forums, and more)
* [Official MESS Wiki](http://www.mess.org/)
* [MAME Testers](http://mametesters.org/) (official bug tracker for MAME and MESS). If you find a bug in MESSUI, you need to confirm it on an official MESS build from mamedev.org before you can log a bug.
* [MESSUI site] http://messui.1emulation.com
* [MESSUI forum] http://www.1emulation.com/forums/forum/125-messui/  (this is for bugs with the MESSUI front-end, or NEWUI. Not for things that are also in an official MESS build.)
