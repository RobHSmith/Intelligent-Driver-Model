#include <vector>
#include <string>
#include "IDM_def.h"

class IDM_TL{
    private:
    public:
        //Member Functions
        IDM_TL();
        ~IDM_TL();

        void TLColor(const int &step); //function to determine the current light color

        template <class T> //random number generator
        T Rand(const T &minT, const T &maxT);

        //Member Variables
        int tx = 0; //traffic light position (m)
        std::string lights[NUMSIMDelT]; //array of lights
        std::string color = ""; //traffic light color storage
        std::vector<int> mult; //cycle time multiples storage
        int cyct = 0; //traffic light cycle time (s)
        int cycstart = 0; //cycle start time relative to simulation start (s)
        int green_end = 0; //green light end in cycle (s)
        int yellow_end = 0; //yellow light end in cycle (s)
};