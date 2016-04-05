#include "MultichannelSystem.h"
#include <iostream>
#include <math.h>
#define MAX_AVG_QUEUE 100
using namespace std;

MultichannelSystem::MultichannelSystem() : channelsNum(0), p0(1)
{
}

MultichannelSystem::MultichannelSystem(int num, int que) : channelsNum(num),  queMax(0), p0(0)
{
}

MultichannelSystem::~MultichannelSystem()
{
    //dtor
}

int MultichannelSystem::t_c = 38.0;

int MultichannelSystem::t_s = 117.0;

int MultichannelSystem::getChannelsNum()
{
    return channelsNum;
}

int MultichannelSystem::getQueueMax()
{
    return queMax;
}

void MultichannelSystem::setChannelsNum(int num)
{
    channelsNum = num;
}

void MultichannelSystem::setQueueMax(int num)
{
    queMax = num;
}

double MultichannelSystem::calculateProbabilityNo()
{
    double sum      = 1;
    double new_a    = 0;
    int factorial   = 1;

    if( channelsNum == 0) {
        return 1;
    }

    for(int i = 1; i <= channelsNum ; i++ )
    {
        factorial *= i;
        new_a = pow(t_s/t_c, i);
        sum += new_a/factorial;
    }

    p0 = 1/sum;

    return p0 * new_a /factorial;
}


double MultichannelSystem::calculateLoad()
{
    double sum = 0;
    double new_a = 0;
    int factorial = 1;

    if( channelsNum == 0) {
        return 0;
    }

    for(int i = 1; i < channelsNum; i++)
    {
        factorial *= i;
        new_a = pow(t_s/t_c, i);
        sum += (i * new_a * p0)/factorial;
    }

    return p0 * sum / channelsNum;
}


double MultichannelSystem::calculateProbabilityWithQue()
{
    if( channelsNum == 0) {
        return 1;
    }

    double k = calculateProbabilityNo() / p0;
    double pN = 0;

    p0 = 1 / ((1/p0) + k * pow((t_s/t_c)/ channelsNum , queMax));
    pN = p0 * k;

    return pN * pow((t_s/t_c)/ channelsNum , queMax);
}

double MultichannelSystem::calculateAvgQueue()
{
    double sum = 0;
    double k = calculateProbabilityNo() / p0;
    double eps = 0.01;
    double pi_k = 1;
    double double_k;
    int i;

    if(channelsNum == 0 || channelsNum == 1)
    {
        return MAX_AVG_QUEUE;
    }

    double_k  = (double)(t_s/t_c)/ channelsNum;
    for(i = 1; pi_k > eps && i < 10; i++)
    {
        pi_k = pow(double_k, i);
        //cout << "pi_k " << pi_k <<" " << double_k << endl;
        sum += i * pi_k;
    }

    p0 = 1 / ((1/p0) + k * pow((t_s/t_c)/ channelsNum , i));
    //cout << "p0: " <<p0  << "sum" << sum << endl;
    return sum * p0;
}

double MultichannelSystem::calculateAvgQueueWithLeave()
{
    double leaveFactor = 2.0;
    double pi_k = 1;
    double k = calculateProbabilityNo() / p0;
    double sum = 0;
    double sum_k = 0;
    double eps = 0.01;

    if(channelsNum == 0 || channelsNum == 1)
    {
        return MAX_AVG_QUEUE;
    }

    for(int i = 1; pi_k > eps && i < 20; i++)
    {
        pi_k = pow((double)(t_s/(t_c * channelsNum + i * leaveFactor)), i) * k;
        sum += i * pi_k;
        sum_k += pi_k;
    }

    p0 = 1/ ((1/p0) + sum_k);
    return p0 * sum;
}
