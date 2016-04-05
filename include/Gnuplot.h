#include <fstream>
#include <vector>
#include <Plot.h>

#ifndef GNUPLOT_H
#define GNUPLOT_H

using namespace std;

 class Gnuplot
{
    public:
        Gnuplot(const char*);
        virtual ~Gnuplot();

        void printDataToFile(vector<double>, vector<double>, const char*);
        void createScript(vector<const char*>, vector<const char*>,  double);
        void createScript(vector<Plot>);
        void runScript();
    private:
        const char* script;
};

#endif // GNUPLOT_H
