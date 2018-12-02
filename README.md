# awm

## Alec's Window Manager

A super lightweight, yet functional window manager.

## Features

Awm is designed to be as tiny as possible while still offering a practical set
of features. This makes it an ideal choice for applications where code size and
efficiency is paramount. As such, awm has:
* A tiny executable size (less than 15KB on my system)
* A tiny memory footprint (less than 3KB on my system)
* Complete facilities for:
   * Launching applications
   * Closing applications
   * Moving windows
   * Resizing windows

Some planned features include:
* Command key rebinding
* Key command rebinding
* Support for alternative application launchers
* Support for alternative terminals

Some far-off future want-to-have features include:
* Multiple workspaces
* Custom keybinds (for launching custom applications and the like)

## Usage

Awm is operated through key commands. All of these commands consist of the
"Command Key" combined with another key to form the command. Currently, the
command key is Alt, and cannot be rebound. The key commands themselves also
cannot be rebound without editing the source and rebuilding.

### Key Commands
| Command            | Meaning           |
|--------------------|-------------------|
| Alt+X              | Open rofi         |
| Alt+Enter          | Open termite      |
| Alt+Click          | Raise Window      |
| Alt+Click and drag | Move Window       |
| Alt+R              | Enter resize mode |
| Alt+Q              | Close Window      |
| Alt+E              | Close awm         |

## Installation

### Prerequisites

Currently. awm requires a X server (obviously), as well as rofi (as a program
launcher) and termite (for a terminal).

### Build and install

After cloning the repo, simply run
```
make clean
make
sudo make install
```
to install or update awm.

### Uninstalling
If you decide that you don't want awm anymore, you can uninstall it with
```
sudo make remove
```
