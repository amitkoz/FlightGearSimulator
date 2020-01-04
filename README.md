# FlightGearSimulator
FlightGearSimulator is an interpreter for a language, that invented by Dr. Eliahu Khalastchi.

Our project sends data to the FlightGear Simulator, as a server, while also receives data from it, as a client.
Our target was to write an interpreter (convert a text file into a running program), that will enable to control the FlightGear.

Before you can run FlightGear you will also need to download and install the following:
‫‪[Download](/‫‪http://home.flightgear.org)‬‬ FlightGear.

(click [here](https://www.flightgear.org/download/main-program/)  for installation instructions).


# How to run the program?
In order to run the project you need to clone it, and use the following command:

 g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread

 
 
In addition, you should provide a txt file for the program to interpret, and an xml file with values to the FlightGear simulator.

# Github link
[Our Project](https://github.com/amitkoz/FlightGearSimulator.git)
