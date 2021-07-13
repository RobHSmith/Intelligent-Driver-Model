#include <math.h>
#include "IDM_TL.h"
#include "IDM_def.h"

//*_____Constructor_____*//
IDM_TL::IDM_TL(){
    IDM_TL::cyct = Rand(CYCTMIN,CYCTMAX); // set the cycle time range
    IDM_TL::green_end = Rand(static_cast<int> (IDM_TL::cyct*GMINRATIO),static_cast<int> (IDM_TL::cyct*GMAXRATIO)); //set the integer time that the green light ends
    IDM_TL::yellow_end = Rand(static_cast<int> (IDM_TL::cyct*YMINRATIO),static_cast<int> (IDM_TL::cyct*YMAXRATIO)); //set the interger time that the yellow light ends
    IDM_TL::cycstart = Rand(CYCSTARTMIN,CYCSTARTMAX); // set cycle start time from start of simulation

    // create array of multiples of cycle time within the simulation time
    for(int n = 0; n <= floor(NUMSIMDelT/IDM_TL::cyct); n++){ 
        IDM_TL::mult.push_back(IDM_TL::cyct*n); 
    }

    const int lmult = IDM_TL::mult.size();

    // compare time to light timings to determine light color
    for(int g = 0; g <= NUMSIMDelT; g++){
        for(int h = 0; h <= lmult - 1; h++){ 
            if(g > IDM_TL::mult[h] && g <= IDM_TL::mult[h] + IDM_TL::green_end){
                IDM_TL::lights[g] = "Green";
            }
            else if(g > IDM_TL::mult[h] && g <= IDM_TL::mult[h] + IDM_TL::yellow_end){
                IDM_TL::lights[g] = "Yellow";
            }
            else if(g > IDM_TL::mult[h] + IDM_TL::yellow_end && g <= IDM_TL::mult[h] + IDM_TL::cyct){
                IDM_TL::lights[g] = "Red";
            }
        }
    }
}

IDM_TL::~IDM_TL(){}

//*_____Member Functions_____*//
//Random number generator
template <class T>
T IDM_TL::Rand(const T &minT, const T &maxT){
    return minT + static_cast<int> (rand())/(static_cast<int>(RAND_MAX/(maxT-minT)));
}

//Function to get current color of light from timestep
void IDM_TL::TLColor(const int &step){
    color = lights[static_cast<int> (step*Deltat)];
}