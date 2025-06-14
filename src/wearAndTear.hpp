#ifndef WEARANDTEAR_HPP
#define WEARANDTEAR_HPP

#include <Arduino.h>
#include "io.hpp"
#include "pinMapping.hpp"
#include "terminal.hpp"

#include <edgeDetect.hpp>

class WearAndTear
{

private:
    IO *pIo = nullptr;
    Terminal *pTerminal = nullptr;
    EdgeDetection<bool> _trigFreshwaterValve;
    EdgeDetection<bool> _trigBackflowValve;
    EdgeDetection<bool> _trigConcentrateValve;
    EdgeDetection<bool> _trigRL1;
    EdgeDetection<bool> _trigRL2;
    EdgeDetection<bool> _trigRL3;
    EdgeDetection<bool> _trigRL4;
    EdgeDetection<bool> _trigRL5;

    uint16_t mOldAverage_membrane1;

    auto inc(Terminal::SET _set, Terminal::GET _get) -> void;
    auto countSwitchingCycles() -> void;
    auto calcMembraneSoH(const uint16_t _oldAvg, const uint16_t _currVal) -> uint16_t;

public:
    auto begin(IO &_io, Terminal &_terminal) -> void;
    auto run() -> void;
};

#endif // WEARANDTEAR_HPP
