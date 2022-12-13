#pragma once
#include <functional>
class TDS
{
public:
    void loop();
    void setCallBack(std::function<void(float)>);
    void queueScan();
    TDS();
private:
    std::function<void(float)> callback;
    int getMedianNum(int bArray[], int iFilterLen);
};