#ifndef PLOT_H
#define PLOT_H

class Plot
{
    public:
        Plot();
        Plot(const char*, const char*, double = 0, double = 1, double = 0, double = 1);
        virtual ~Plot();
        const char* getFilePath();
        const char* getTitle();
        double getXmin();
        double getXmax();
        double getYmin();
        double getYmax();
        void setFilePath(const char*);
    private:
        const char* filePath;
        const char* title;
        double x_min;
        double x_max;
        double y_min;
        double y_max;


};

#endif // PLOT_H
