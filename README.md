# Willow's Dream

An Action-RPG homebrew ROM game developed for the Sega Genesis built on the SGDK library.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

All prerequisites are included in the master repository and do not require additional configuration.

```
SGDK*
DGen
```
<sub>\* = Required</sub>

### Installing

Compile all project dependencies by running _build.bat_ located in the project's top level directory. This will temporarily set environment variables, compile _SGDK_ (if not already compiled), wipe the previous build of the project, compile _Willow's Dream_ and all of its resources, and ask if you would like to open the compiled rom in DGen to playtest the game on an emulated Sega Genesis environment. _DGen_ is included precompiled and doesn't require system configuration.

## Deployment

Physical distribution for commercial use (whether in cartridge or compact format) is not permitted whereas for personal use is strongly recommended as this game is intended to be used on the original Sega Genesis/Mega Drive hardware.

## Built With

* [SDGK](https://github.com/Stephane-D/SGDK/wiki) - The Sega Genesis/Mega Drive development kit used
* [DGEN/SDL](http://dgen.sourceforge.net/) - The Sega Genesis/Mega Drive emulator used for testing
* [DefleMask](http://deflemask.com/) - Multi-system chiptune tracker used to compose music and export music ROM files
* [Pyxel Edit](http://pyxeledit.com/) - Pixel art editor for sprites, animations, tilesets, and tilemaps

## Contributing

At this time in initial development, external contributions are not being considered, but they will be open for merging later in development.

## Versioning

For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **D Cooper Dalrymple** - *Lead Developer* - [Website](https://dcdalrymple.com/) - [GitHub](https://github.com/dcooperdalrymple/)
* **Malcolm Brooks** - *Storyboard Writer* - [GitHub](https://github.com/MalcolmBrooks2)
* **Hannibal Brooks** - *Storyboard Writer*

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under GNU LGPL V3.0 - see the [LICENSE.md](LICENSE.md) file for details.
