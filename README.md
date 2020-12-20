# Past-CTL Monitoring in Field Calculus

This repository contains the implementation of a monitoring system for past-CTL logic formulas based on Field Calculus. It also contains three graphical demo scenarios where past-CTL formulas are monitored during the simulation of distributed systems.

## Installation

### Windows

Pre-requisites:
- MinGW-w64 8.1.0
- CMake 3.9 (or higher)

Clone this repository and go into its main directory. Type the following commands:
```
- cmake -S ./ -B ./build -G "MinGW Makefiles"
- cmake --build ./build/
```

### Linux

Pre-requisites:
- xorg-dev package (X11)
- CMake 3.9 (or higher)

To install the X11 package in Ubuntu, type the following command:
```
sudo apt-get  install xorg-dev
```

Clone this repository and go into its main directory. Type the following commands:
```
- cmake -S ./ -B ./build -G "Unix Makefiles"
- cmake --build ./build/
```

## Demo Scenarios

The installation instructions above build three demo scenarios in the ```build``` directory:
- Crowd Safety (executable ```crowd_safety```)
- Smart Home (executable ```smart_home```)
- Drones Recognition (executable ```drones_recognition```)

To launch a scenario, go to the ```build``` directory and run its executable.

The scenario will open a window displaying the simulation. You can interact with the folowwing keys:
- ```P``` to stop/resume
- ```O```/```I``` to speed-up/slow-down simulation time
- ```Esc``` to exit the simulation
- ```shift```+```Q```,```W```,```E```,```A```,```S```,```D``` to move the simulation area along orthogonal axes
- ```right-click```+```mouse drag``` to rotate the camera
