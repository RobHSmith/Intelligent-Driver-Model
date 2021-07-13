// Rob Smith, Tyler Ard
// May 2021
// Code simulates a set of vehicles following the IDM model on a road with traffic lights that have fixed timings

//*_____ Libraries _____*//
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <limits>
#include "IDM_def.h"
#include "IDM.h"
#include "IDM_TL.h"

//*_____ Functions _____*//

//Control Dynamics of Vehicles
void Dynamics(IDM &VehObject){ 
    // Discrete integration equations
    VehObject.x += VehObject.v*Deltat + 0.5*VehObject.u*pow((Deltat),2);
    VehObject.v += VehObject.u*Deltat;

    // Prevent vehicle from moving in reverse
    if(VehObject.v < 0){
        VehObject.v = 0.;
        VehObject.u = 0.;
    }
}

//Random Number Generator
template <class T>
T Rand(const T &minT, const T &maxT){
    return minT + static_cast<int> (rand())/(static_cast<int>(RAND_MAX/(maxT-minT)));
}

//Heaviside Function
inline int heaviside(const double &xval){
    return (xval >= 0) ? 1 : 0;
}


//*_____ Main _____*//

int main() {
    // Initialize .csv file
    std::ofstream motion("motion.csv");
    
    // Initialize random seed
    srand(static_cast<unsigned> (time(0)));
    
    // Initialize array of vehicles
    IDM Vehicles[NUMVEHS];

    // Assign initial vehicle attributes inaccessible by constructor
    for(int m = 0; m < NUMVEHS; m++){
        if(m == 0){
            Vehicles[m].s = std::numeric_limits<double>::max(); // "infinite" gap in front of first vehicle
            Vehicles[m].x = 0.; // "starting line" at 0 m
            Vehicles[m].v0 = 20.; // lead vehicle goal speed (m/s): if within ~2 m/s of other vehicles' goal speed, gaps will diverge
        }
        else{
            Vehicles[m].s = 10.; // 10 meter gap
            Vehicles[m].x = -m*(L1 + Vehicles[m].s); // position determined by length of car in front plus initial gap
        }
    }

    // Initialize traffic light and set up array
    IDM_TL TL[NUMTLIGHT];

    // Assign traffic light positions
    for(int b = 0; b < NUMTLIGHT; b++){
        if(b == 0){
            TL[b].tx = Rand(FPOSMIN,FPOSMAX);
        }
        else{
            TL[b].tx = TL[b-1].tx + Rand(POSMIN,POSMAX);
        }
    }

    // Run simulation
    for (int j = 0; j <= NUMSIMSTEPS; j++) {
        // Get command of all vehicles for next timestep
        for (int i = 0; i < NUMVEHS; i++) {
            if(i == 0){
                double Deltav = 0.;
                Vehicles[i].s = pow(10,9);
                Vehicles[i].GetCommand(Vehicles[i].s,Deltav);
            }
            else{
                double Deltav = Vehicles[i].v - Vehicles[i-1].v;
                Vehicles[i].s = Vehicles[i-1].x - L1 - Vehicles[i].x;
                Vehicles[i].GetCommand(Vehicles[i].s,Deltav);

                //Compute CAH acceleration
                if(Vehicles[i-1].v*(Vehicles[i].v-Vehicles[i-1].v) <= -2*Vehicles[i].s*fmin(Vehicles[i-1].u,Vehicles[i].a)){
                    Vehicles[i].ucah = pow(Vehicles[i].v,2)*fmin(Vehicles[i-1].u,Vehicles[i].a)/(pow(Vehicles[i-1].v,2)-2*Vehicles[i].s*fmin(Vehicles[i-1].u,Vehicles[i].a));
                }
                else{
                    Vehicles[i].ucah = fmin(Vehicles[i-1].u,Vehicles[i].a) - (pow(Vehicles[i].v-Vehicles[i-1].v,2)*heaviside(Vehicles[i].v - Vehicles[i-1].v))/2*Vehicles[i].s; 
                }

                //Compare CAH to IDM acceleration
                Vehicles[i].Compare(Vehicles[i].ucah,Vehicles[i].br,Vehicles[i].u);
            }
        }

        // Get traffic light color for the next timestep
        for(int c = 0; c < NUMTLIGHT; c++){
            TL[c].TLColor(j);
        }

        // Select acceleration based on traffic light color (if in range)
        for(int k = 0; k < NUMVEHS; k++){
            const double sdist = pow(Vehicles[k].v,2)/Vehicles[k].br; // calculate stopping distance (m)

            for(int y = 0; y < NUMTLIGHT; y++){
                double tdist = TL[y].tx - Vehicles[k].x;
                if(Vehicles[k].sens >= tdist && tdist >= 0){
                    if((TL[y].color == "Yellow" || TL[y].color == "Red") && tdist > sdist){ // begin stopping if light is yellow or red and vehicle can stop comfortably
                        double a_c = -pow(Vehicles[k].v,2)/(2*tdist); //comfortable deceleration based on particle kinematics (m/s^2)

                        Vehicles[k].u = fmin(a_c,Vehicles[k].u);
                    }
                    else if(TL[y].color == "Red" && sdist == tdist){ // stop if light is red and vehicle can stop comfortably
                        Vehicles[k].u = fmin(-Vehicles[k].br,Vehicles[k].u);
                    }
                    else{
                        //Vehicles[k].u = Vehicles[k].u;
                    }
                }
                else{
                    //Vehicles[k].u = Vehicles[k].u;
                }
            }
            
            // Run dynamics for all vehicles
            Dynamics(Vehicles[k]);
        }
        // Print to console to monitor
        //if (j % 10 == 0) {
            //char buffer[BUFSIZE];
            //snprintf(
                //buffer, sizeof(buffer),
                //"%0.2f, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f \n", 
                //j*Deltat, Vehicles[0].s, Vehicles[0].v, Vehicles[0].u, Vehicles[0].x-L1-Vehicles[1].x, Vehicles[1].v, Vehicles[1].u, Vehicles[1].x-L1-Vehicles[2].x, Vehicles[2].v, Vehicles[2].u 
            //);

        //std::cout << buffer;
        //}

        // Print to "motion.csv"
        motion << j*Deltat << ","; // List simulation time
        for(int n = 0; n < NUMVEHS; n++){ // List vehicle parameters
            motion << Vehicles[n].u << ",";
            motion << Vehicles[n].v << ",";
            motion << Vehicles[n].s << ",";
            motion << Vehicles[n].x << ",";
        }
        for(int r = 0; r < NUMTLIGHT; r++){ // List traffic light color as "on/off" data with "on" given as the light position
            if(TL[r].color == "Yellow"){
                motion << TL[r].tx << ",";
                motion << 0 << ",";
            }
            else if(TL[r].color == "Red"){
                motion << 0 << ",";
                motion << TL[r].tx << ",";
            }
            else{
                motion << 0 << ",";
                motion << 0 << ",";
            }
        }
        motion << "\n";
    }
}