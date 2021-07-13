#include <math.h>
#include "IDM.h"
#include "IDM_def.h"

//*_____Constructor_____*//
IDM::IDM(){
    IDM::v = 0.;

    int aggr = Rand(AGGROMIN,AGGROMAX); // pick from aggressive (1) or non-aggressive (2, 3) driver
    if(aggr == 1){
        IDM::a = Rand(AGGMINACCEL,AGGMAXACCEL);
        IDM::br = Rand(AGGMINBRAKE,AGGMAXBRAKE);
        IDM::T = Rand(AGGMINT,AGGMAXT);
    }
    else{
        IDM::a = Rand(SAFEMINACCEL,SAFEMAXACCEL);
        IDM::br = Rand(SAFEMINBRAKE,SAFEMAXBRAKE);
        IDM::T = Rand(SAFEMINT,SAFEMAXT);
    }
}

//*_____Member Functions_____*//
template <class F>
F IDM::Rand(const F &minT, const F &maxT){
    return minT + static_cast<int> (rand())/(static_cast<int>(RAND_MAX/(maxT-minT)));
}

//Get next IDM-based acceleration command
void IDM::GetCommand(const double &s_in, const double &Deltav) {
    double sstar = s0 + fmax(0,v*T + ((v*Deltav)/(2*sqrt(a*br))));
    u = a*(1-pow((v/v0),d)-pow((sstar/s_in),2)); // IDM equations for dv/dt
}

//Get next acceleration command based on comparison btw CAH and IDM model accelerations
void IDM::Compare(double ucah, double br, double u){
    if(u < ucah){
        u = (1 - CFACTOR) * u + CFACTOR * (ucah + br * tanh((u - ucah) / br));
    }
}