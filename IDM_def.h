#pragma once //single evaluation of file

//*_____Simulation_____*//
#define NUMVEHS 5
#define NUMSIMSTEPS 3000
#define NUMTLIGHT 6 // number of traffic lights
#define Deltat 0.1 // time step (s)
#define L1 5. // 5 meter car length
#define BUFSIZE 2000 // Lines in buffer if printing to terminal
constexpr int NUMSIMDelT = NUMSIMSTEPS*Deltat; // pre-code calculation

//*_____IDM Constraints_____*//
#define AGGROMAX 3
#define AGGROMIN 1

#define AGGMAXACCEL 2.5
#define AGGMINACCEL 1.75

#define AGGMAXBRAKE 3.5
#define AGGMINBRAKE 2.6

#define AGGMAXT 1.25
#define AGGMINT 0.8

#define SAFEMAXACCEL 1.5
#define SAFEMINACCEL 0.8

#define SAFEMAXBRAKE 2.5
#define SAFEMINBRAKE 1.5

#define SAFEMAXT 2.
#define SAFEMINT 1.5

#define CFACTOR 0.99

//*_____Traffic Lights_____*//
#define CYCTMAX 180
#define CYCTMIN 60

#define GMAXRATIO 1/2
#define GMINRATIO 3/8

#define YMAXRATIO 11/16
#define YMINRATIO 5/8

#define CYCSTARTMAX 10
#define CYCSTARTMIN 0

#define FPOSMAX 650
#define FPOSMIN 450

#define POSMAX 700
#define POSMIN 100
