# Willow's Dream

An Action-RPG homebrew ROM game developed for the Sega Genesis built on the SGDK library.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

```
SGDK
DGen/SDL - Multi-platform Genesis/Mega Drive Emulator (or similar emulation software)
```

### Installing

```
Full installation guide for SGDK found at the [SGDK GitHub](https://github.com/Stephane-D/SGDK/wiki/Setup-SGDK-basic).
```

Installation and use of SGDK from command line (Windows OS only).

1. Download the SGDK archive from the [Download page](https://github.com/Stephane-D/SGDK/wiki/Download) and unzip it where it suits to you (for instance D:/sgdk).
2. Define _GDK_ environment variable to your installation path in unix path format (example D:/sgdk).
3. Define _GDK_WIN_ which still point to your installation path but in windows format (example D:\sgdk).
4. Add the _bin_ directory of devkit (%GDK_WIN%\bin) to your PATH variable. Be careful, if you have another GCC installation you can have some conflicts when cc1 command will be called.
5. Now you can compile the library by using:

```
%GDK_WIN%\bin\make -f %GDK_WIN%\makelib.gen
```

When the library is compiled you should obtain the following files
```
%GDK%/lib/libmd.a
```

You can now compile the game, _Willow's Dream_, by using the build.bat file located in the project's top level directory.

## Deployment

Physical distribution for commercial use (whether in cartridge or compact format) is not permitted whereas for personal use is strongly recommended as this game is intended to be used on the original Sega Genesis/Mega Drive hardware.

## Built With

* [SDGK](https://github.com/Stephane-D/SGDK/wiki) - The Sega Genesis/Mega Drive development kit used
* [DGEN/SDL](http://dgen.sourceforge.net/) - The Sega Genesis/Mega Drive emulator used for testing

## Contributing

At this time in initial development, external contributions are not being considered, but they will be open for merging later in development.

## Versioning

For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **D Cooper Dalrymple** - *Lead Developer* - [Website](https://dcdalrymple.com/) - [GitHub](https://github.com/dcooperdalrymple/)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under GNU LGPL V3.0 - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

* Samantha Marie Johnna Earley
