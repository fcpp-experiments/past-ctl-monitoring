# Past-CTL Monitoring in Field Calculus

This repository contains the implementation of a monitoring system for past-CTL logic formulas based on Field Calculus (submitted to Journal of Systems and Software). It also contains three graphical demo scenarios where past-CTL formulas are monitored during the simulation of distributed systems.

## Installation

### Windows

Pre-requisites:
- [MinGW-w64 8.1.0](http://mingw-w64.org)
- [CMake 3.9](https://cmake.org) (or higher)
- [Asymptote](http://asymptote.sourceforge.io) (for building the plots)

We assume that commands are issued through [Git Bash](https://gitforwindows.org) or analogous tool.
Clone this repository, then go into its main directory to launch the `make.sh` script:
```
> git clone https://github.com/Harniver/past-ctl-monitoring.git
> cd past-ctl-monitoring
> ./make.sh windows [scenario]
```
where `[scenario]` is one of the three described below. You should see output about building the executables, then the graphical simulation should pop up. When the simulation closes, the resulting data will be plotted in folder `plot/`.

### Linux

Pre-requisites:
- xorg-dev package (X11)
- CMake 3.9 (or higher)
- Asymptote (for building the plots)

To install these packages in Ubuntu, type the following command:
```
sudo apt-get install xorg-dev cmake asymptote
```

Clone this repository, then go into its main directory to launch the `make.sh` script:
```
> git clone https://github.com/Harniver/past-ctl-monitoring.git
> cd past-ctl-monitoring
> ./make.sh unix [scenario]
```
where `[scenario]` is one of the three described below. You should see output about building the executables, then the graphical simulation should pop up. When the simulation closes, the resulting data will be plotted in folder `plot/`.

### MacOS

Pre-requisites:
- Xcode Command Line Tools
- CMake 3.9 (or higher)
- [Asymptote](http://asymptote.sourceforge.io) (for building the plots)

To install the first two tools, assuming you have [brew](https://brew.sh) installed, type the following commands:
```
xcode-select --install
brew install cmake
```

Clone this repository, then go into its main directory to launch the `make.sh` script:
```
> git clone https://github.com/Harniver/past-ctl-monitoring.git
> cd past-ctl-monitoring
> ./make.sh unix [scenario]
```
where `[scenario]` is one of the three described below. You should see output about building the executables, then the graphical simulation should pop up. When the simulation closes, the resulting data will be plotted in folder `plot/`.

## Demo Scenarios

The installation instructions above build three demo scenarios in the `build/` directory:
- Crowd Safety (executable `crowd_safety`)
- Drones Recognition (executable `drones_recognition`)
- Smart Home (executable `smart_home`)

To launch a scenario manually, go to the `build` directory and run its executable.

The scenario will open a window displaying the simulation. You can interact with the following keys:
- ```P``` to stop/resume
- ```O```/```I``` to speed-up/slow-down simulation time
- ```Esc``` to exit the simulation
- ```Q```,```W```,```E```,```A```,```S```,```D``` to move the simulation area along orthogonal axes
- ```right-click```+```mouse drag``` to rotate the camera
-```left-shift``` for precision camera movements
