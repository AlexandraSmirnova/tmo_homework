#include "MultichannelSystem.h"

MultichannelSystem::MultichannelSystem(int num) : channelsNum(num)
{
    //ctor
}

MultichannelSystem::~MultichannelSystem()
{
    //dtor
}

int MultichannelSystem::getChannelsNum()
{
    return channelsNum;
}

void MultichannelSystem::setChannelsNum(int num)
{
    channelsNum = num;
}
