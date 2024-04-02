#pragma once

class Rcc
{
public:
    static Rcc *instance();
    void enableMaxClockSpeed();

private:
    Rcc() = default;
    void runHSE();
    void runPLL();
    void runPLLCLK();
    void setupPLL();
    void setupBusPrescalers();
    void setupFLASH();
};
