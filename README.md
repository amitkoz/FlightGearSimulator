# FlightGearSimulator
FlightGearSimulator is an interpreter for a language, that invented by Dr. Eliahu Khalastchi.
Link:  http://www.flightgear.org
Our project sends data to the FlightGear Simulator, as a server, while also receives data from it, as a client.
The code was built to convert a text file into a running program, ehile the target is to cause an airplane to fly.  

# How to run the program?
In order to run the project you need to clone it, and use the following command:

 g++ -std=c++14 */*.cpp */*/*.cpp  *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
 
 
In addition, you should provide a txt file for the program to interpret, and an xml file with values to the FlightGear simulator.

# Github link
[Our Project]https://github.com/amitkoz/FlightGearSimulator.git

