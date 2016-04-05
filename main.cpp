#include <iostream>
#include <vector>
#include <algorithm>    // std::reverse
#include <MultichannelSystem.h>
#include <Gnuplot.h>
#include <Plot.h>

#define MAX_OPERATORS 25
#define MAX_AVG_QUEUE 100
#define PLOT_SCALE  2

using namespace std;

void task1(vector<Plot>* plots, Gnuplot gnup, vector<double>* xValues)
{
    MultichannelSystem measureSystem(1);
    vector<double> refuseChannels;
    vector<double> loadCoeff;

    double probRefuse;
    double k;
    double limits[4] = {0.25, 0.10, 0.5, 0.1};             // 25%, 10%, 5% and 1%
    int currentIndex = 0;

    for(int i = 0; i < MAX_OPERATORS && currentIndex < 4 ; i++ )
    {
        measureSystem.setChannelsNum(i);
        probRefuse = measureSystem.calculateProbabilityNo();
        refuseChannels.push_back(probRefuse);

        k = measureSystem.calculateLoad();
        loadCoeff.push_back(k);
        xValues->push_back(i);
        if (probRefuse < limits[currentIndex])
        {
            cout <<  limits[currentIndex] << "%:\t" << i << " - " << probRefuse << endl;
            currentIndex++;
        }
    }

    int lastOperatorNum = refuseChannels.size() - 1;
    Plot plot1_1("out/data1.txt", "Probability of refuse", 0, lastOperatorNum, 0, 1);
    Plot plot1_2("out/data1_2.txt", "Load coefficient",0 ,  lastOperatorNum, 0, loadCoeff[loadCoeff.size() - 1] * PLOT_SCALE );
    plots->push_back(plot1_1);
    plots->push_back(plot1_2);
    gnup.printDataToFile(*xValues, refuseChannels, plot1_1.getFilePath());
    gnup.printDataToFile(*xValues, loadCoeff, plot1_2.getFilePath());
}

void task2(vector<Plot>* plots, Gnuplot gnup, vector<double> xValues)
{
    MultichannelSystem measureSystem(1);
    vector<double> refuseChannels;
    vector<double> loadCoeff;
    double probRefuse;
    double k;
    int operatorsMax = xValues.size();

    for(int i = 0; i < operatorsMax ; i++ )
    {
        measureSystem.setChannelsNum(i);
        measureSystem.setQueueMax(operatorsMax - i);
        probRefuse = measureSystem.calculateProbabilityWithQue();
        k = measureSystem.calculateLoad();

        refuseChannels.push_back(probRefuse);
        loadCoeff.push_back(k);
    }

    Plot plot2_1("out/data2.txt", "Probability of refuse with Queue", 0, operatorsMax-1, 0, 1);
    Plot plot2_2("out/data2_2.txt", "Load coefficient with Queue",0 ,  operatorsMax-1, 0, loadCoeff[loadCoeff.size() - 1] * PLOT_SCALE);
    plots->push_back(plot2_1);
    plots->push_back(plot2_2);
    gnup.printDataToFile(xValues, refuseChannels, plot2_1.getFilePath());
    gnup.printDataToFile(xValues, loadCoeff, plot2_2.getFilePath());
}


void task3(vector<Plot>* plots, Gnuplot gnup, vector<double> xValues)
{
    MultichannelSystem measureSystem(1);
    int operatorsMax = xValues.size();
    vector<double> avgValues;
    double avgQueue;

    for(int i = 0; i < operatorsMax; i++ )
    {
        measureSystem.setChannelsNum(i);
        avgQueue = measureSystem.calculateAvgQueue();
        avgValues.push_back(avgQueue);
    }

    Plot plot3("out/data3.txt", "Avg Queue", 0, operatorsMax-1, 0, MAX_AVG_QUEUE);
    plots->push_back(plot3);
    gnup.printDataToFile(xValues, avgValues, plot3.getFilePath());
}


void task4(vector<Plot>* plots, Gnuplot gnup, vector<double> xValues)
{
    MultichannelSystem measureSystem(1);
    int operatorsMax = xValues.size();
    vector<double> avgValues;
    double avgQueue;

    for(int i = 0; i < operatorsMax; i++ )
    {
        measureSystem.setChannelsNum(i);
        avgQueue = measureSystem.calculateAvgQueueWithLeave();
        avgValues.push_back(avgQueue);
    }

    Plot plot3("out/data4.txt", "Avg Queue with leave factor", 0, operatorsMax-1, 0, MAX_AVG_QUEUE);
    plots->push_back(plot3);
    gnup.printDataToFile(xValues, avgValues, plot3.getFilePath());
}


int main()
{
    MultichannelSystem System(1);
    const char* gnuFile = "out/test.txt";
    Gnuplot gnuplot(gnuFile);
    vector<double> XVector;
    vector<Plot> plotsVector;

    task1(&plotsVector,gnuplot, &XVector);
    task2(&plotsVector,gnuplot, XVector);
    //task3(&plotsVector,gnuplot, XVector);
    //task4(&plotsVector,gnuplot, XVector);

    gnuplot.createScript(plotsVector);
    gnuplot.runScript();
    return 0;
}
