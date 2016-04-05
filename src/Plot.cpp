#include "Plot.h"

Plot::Plot()
{
    //ctor
}


Plot::Plot(const char* file, const char* plotTitle, double xmin, double xmax, double ymin, double ymax) : x_min(xmin), x_max(xmax), y_min(ymin), y_max(ymax)
{
    filePath = file;
    title = plotTitle;
    //ctor
}

Plot::~Plot()
{
    //dtor
}

const char* Plot::getFilePath()
{
    return filePath;
}

const char* Plot::getTitle()
{
    return title;
}


double Plot::getXmin()
{
    return x_min;
}


double Plot::getXmax()
{
    return x_max;
}



double Plot::getYmin()
{
    return y_min;
}


double Plot::getYmax()
{
    return y_max;
}


void Plot::setFilePath(const char* file)
{
    filePath = file;
}
