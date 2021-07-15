# Intelligent-Driver-Model
This set of code is used to model a series of cars controlled by the Intelligent Driver Model (IDM) on a single-lane single-direction road with multiple traffic lights. 
A description of the IDM can be found at https://arxiv.org/pdf/0912.3613.pdf. Each traffic light has bounded randomized timing. 
The model has been converted to an enhanced IDM (EIDM) by the addition of a comparison with the Constant Acceleration Heuristic (CAH) for the setting of the command acceleration.
The EIDM is described in https://arxiv.org/pdf/0912.3613.pdf. The dynamics of the vehicles are controlled by a forward Euler integration using particle dynamics.

Don't forget to update the .json tasks file to include the IDM and IDM_TL .cpp files. If the plotting code has cars going through red lights, rebuild Sim_Space_3 and run the code again. If that doesn't work, close your coding application and reopen the code. There's some bug that causes this, but I haven't been able to find it. I suspect that the .csv is not properly written to sometimes, or MATLAB stores something in its memory that it shouldn't.

# IDM_def
This file contains the definitions for constants and constant expressions (constexpr) used throughout the simulation files.

# IDM
These files contain the IDM class as well as the GetCommand function (which returns the command acceleration based on the IDM model) and the Compare function 
(which returns the command acceleration after comparison between the IDM command acceleration and the CAH command acceleration)

# IDM_TL
These files contain the class for the traffic lights as well as functions to return the current state of each traffic light to the simulation.
The constructor for this class sets the timings of each traffic light.

# Sim_Space_3
This file contains the simulation of each vehicle as well as the Dynamics function which performs the forward Euler Integration.
The output data from this function is written to a .csv titled motion.csv, though the file name can be changed. The traffic signals' yellow and red states are also
printed to the .csv by printing the traffic lights position.

# Plotting_Code
This MATLAB file contains the code to read the data from motion.csv and plot it. The code provides plots for inter-vehicle gaps (excluding the first vehicle, which has an "infinite" gap in front of it), vehicle position (with traffic light yellow and red states), vehicle velocity, and command acceleration. 
