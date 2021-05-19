# Past-CTL Monitoring in Field Calculus

This repository contains the implementation of a monitoring system for past-CTL logic formulas based on Field Calculus (submitted to Journal of Systems and Software). It also contains three graphical demo scenarios where past-CTL formulas are monitored during the simulation of distributed systems.

## Installation

### Virtual Machines

The simulations in this repository have an OpenGL-based graphical interface. Common Virtual Machine software (e.g., VirtualBox) has faulty support for OpenGL, hence running the experiments in a VM is not supported. Based on preliminary testing, the simulations may not start on some VMs, while starting on others with graphical distortions (e.g., limited colors).

### Windows

Pre-requisites:
- [Git Bash](https://gitforwindows.org) (for issuing unix-style commands)
- [MinGW-w64 builds 8.1.0](http://mingw-w64.org/doku.php/download/mingw-builds)
- [CMake 3.9](https://cmake.org) (or higher)
- [Asymptote](http://asymptote.sourceforge.io) (for building the plots)

During CMake installation, make sure you select to add `cmake` to the `PATH` (at least for the current user).
During MinGW installation, make sure you select "posix" threads (should be the default) and not "win32" threads. After installing MinGW, you need to add its path to the environment variable `PATH`. The default path should be:
```
C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin
```
but the actual path may vary depending on your installation.

Clone this repository, then go into its main directory to launch the `make.sh` script:
```
> git clone https://github.com/Harniver/past-ctl-monitoring.git
> cd past-ctl-monitoring
> ./make.sh windows [scenario]
```
where `[scenario]` is one of the three described in the next section (or `all` to launch them all). You should see output about building the executables, then the graphical simulation should pop up. When the simulation closes, the resulting data will be plotted in folder `plot/`.

### Linux

Pre-requisites:
- Xorg-dev package (X11)
- G++ 9 (or higher)
- CMake 3.9 (or higher)
- Asymptote (for building the plots)

To install these packages in Ubuntu, type the following command:
```
sudo apt-get install xorg-dev g++ cmake asymptote
```

Clone this repository, then go into its main directory to launch the `make.sh` script:
```
> git clone https://github.com/Harniver/past-ctl-monitoring.git
> cd past-ctl-monitoring
> ./make.sh unix [scenario]
```
where `[scenario]` is one of the three described in the next section (or `all` to launch them all). You should see output about building the executables, then the graphical simulation should pop up. When the simulation closes, the resulting data will be plotted in folder `plot/`.

### MacOS

Pre-requisites:
- Xcode Command Line Tools
- CMake 3.9 (or higher)
- [Asymptote](http://asymptote.sourceforge.io) (for building the plots)

To install them, assuming you have the [brew](https://brew.sh) package manager, type the following commands:
```
xcode-select --install
brew install cmake asymptote
```

Clone this repository, then go into its main directory to launch the `make.sh` script:
```
> git clone https://github.com/Harniver/past-ctl-monitoring.git
> cd past-ctl-monitoring
> ./make.sh unix [scenario]
```
where `[scenario]` is one of the three described in the next section (or `all` to launch them all). You should see output about building the executables, then the graphical simulation should pop up. When the simulation closes, the resulting data will be plotted in folder `plot/`.

## Demo Scenarios

The installation instructions above build three demo scenarios in the `bin/` directory:
- Crowd Safety (executable `crowd_safety`)
- Drones Recognition (executable `drones_recognition`)
- Smart Home (executable `smart_home`)

To launch a scenario manually, move to the `bin` directory and run its executable. This will open a window displaying the simulation scenario, initially still: you can start running the simulation by pressing `P` (current simulated time is displayed in the bottom-left corner). While the simulation is running, network statistics will be periodically printed in the console, and aggregated in form of an Asymptote plot at simulation end. You can interact with the simulation through the following keys:
- `Esc` to end the simulation
- `P` to stop/resume
- `O`/`I` to speed-up/slow-down simulated time
- `L` to show/hide connection links between nodes
- `G` to show/hide the grid on the reference plane and node pins
- `Q`,`W`,`E`,`A`,`S`,`D` to move the simulation area along orthogonal axes
- `C` resets the camera to the starting position
- `M` enables/disables the marker for selecting nodes
- `left-click` on a selected node to open a window with node details
- `right-click`+`mouse drag` to rotate the camera
- `mouse scroll` for zooming in and out
- `left-shift` added to the commands above for precision control
