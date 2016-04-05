#ifndef MULTICHANNELSYSTEM_H
#define MULTICHANNELSYSTEM_H


class MultichannelSystem
{
    public:
        MultichannelSystem();
        MultichannelSystem(int, int=0);
        virtual ~MultichannelSystem();

        static int t_s;
        static int t_c ;

        double calculateProbabilityNo();
        double calculateLoad();
        double calculateProbabilityWithQue();
        double calculateAvgQueue();
        double calculateAvgQueueWithLeave();
        int getChannelsNum();
        int getQueueMax();
        void setChannelsNum(int);
        void setQueueMax(int);

    private:
        int channelsNum;
        int queMax;
        double p0;
};

#endif // MULTICHANNELSYSTEM_H
