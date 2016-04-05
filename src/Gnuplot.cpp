#include "Gnuplot.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <Plot.h>

using namespace std;

Gnuplot::Gnuplot(const char* file) : script(file)
{
}


Gnuplot::~Gnuplot()
{
    //dtor
}

void Gnuplot::createScript(vector<const char*> path_files, vector<const char*> titles, double max_x)
{
    fstream fp;

    fp.open(script);
    fp << "set terminal x11 size 1360, 700" << endl;
    fp << "set title 'Result'" << endl;
    fp << "set xlabel 'X'" << endl;
    fp << "set ylabel 'Y'" << endl;
    fp << "set xrange [0.0:" << max_x << "]" << endl;
    fp << "set yrange [0.0:100]" << endl;
    fp << "set grid" << endl;
    fp << "plot \'";
    for(unsigned int i = 0; i < path_files.size() ; i++ )
    {
        fp << path_files[i] << "\' using 1:2 w l lw 2 title \'" << titles[i] << "\'";
        if(i < path_files.size()-1)
            fp << ",\\";
        fp << endl;
    }
    fp << "pause -1" << endl;
    fp.close();

}

void Gnuplot::createScript(vector<Plot> Plots)
{
    fstream fp;

    fp.open(script, ios::out | ios::trunc );
    fp << "set terminal x11 size 1360, 700" << endl;
    fp << "set title 'Result'" << endl;
    fp << "set xlabel 'X'" << endl;
    fp << "set ylabel 'Y'" << endl;
    fp << "set xrange [" << Plots[0].getXmin() << ":" << Plots[0].getXmax() << "]" << endl;
    fp << "set yrange [" << Plots[0].getYmin() << ":" << Plots[0].getYmax() << "]" << endl;
    fp << "set y2range [" << Plots[1].getYmin() << ":" << Plots[1].getYmax() << "]" << endl;
    fp << "set grid" << endl;
    fp << "plot ";
    for(unsigned int i = 0; i < Plots.size() ; i++ )
    {
        fp << "\'" << Plots[i].getFilePath() << "\' using 1:2 axes x1" << "y" << (i%2)+1;
        fp << " w l lw 2 title \'" << Plots[i].getTitle() << "\'";
        if(i < Plots.size()-1)
            fp << ",\\";
        fp << endl;
    }
    fp << "pause -1" << endl;

    fp.close();
}

void Gnuplot::runScript()
{
    char* str = new char(strlen("gnuplot ") + strlen(script));

    strcpy(str, "gnuplot ");
    strcat(str, script);
    system(str);

    delete str;
}


void Gnuplot::printDataToFile(vector<double> dataX, vector<double> dataY, const char* dataFile)
{
    fstream fp;

    fp.open(dataFile, ios::out | ios::trunc );
    cout << dataFile << endl;
    for(unsigned int i = 0; i < dataX.size() && i < dataY.size(); i++)
    {
        fp <<  dataX[i]<< " " << dataY[i] << endl;
        cout << dataX[i] << " " << dataY[i] << endl;
    }
    fp.close();
}


