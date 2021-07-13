class IDM {
    private:
        const double d = 4.; // unitless parameter
        const double s0 = 3.; // 3 meter minimum gap
    
    public:
        // Member functions
        IDM();
        ~IDM();

        template <class F> //random number generator
        F Rand(const F &minT, const F &maxT);

        void GetCommand(const double &s_in, const double &Deltav); //function to get next IDM acceleration command

        void Compare(double ucah, double br, double u); //function to get next acceleration command based on IDM/CAH acceleration comparison

        // Member variables
        double s = 0.; // gap between ego vehicle and preceding vehicle (m)
        double x = 0.; // position (m)
        double x0 = 0.; // initial position (m)

        double v = 1.; // velocity (m/s)
        double v0 = 25.; // desired velocity (m/s)

        double a = 2.5; // acceleration default (m/s^2)
        double br = 3.; // comfortable braking capacity default (m/s^2)
        double T = 1.; // time headway default (s)
        
        double u = 0.; // command acceleration (m/s^2)
        double ucah = 0.; //CAH acceleration (m/s^2)

        const double sens = 250.; // Sensor view (m)
};