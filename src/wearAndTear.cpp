#include "wearAndTear.hpp"

auto WearAndTear::begin(IO &_io, Terminal &_terminal) -> void
{
    pIo = &_io;
    pTerminal = &_terminal;
}

/**
 * @brief 
 * 
 */
auto WearAndTear::countSwitchingCycles() -> void 
{
    if(pIo == nullptr || pTerminal == nullptr)
        return;
    
    if (!pTerminal->isAlive())
        return;
    
    if (_trigFreshwaterValve.edgeDetection(pTerminal->getVal<bool>(Terminal::GET::SV_FRESHWATER), EdgeDetection<bool>::type::RISING_EDGE, true))
        inc(Terminal::SET::WEAR_TEAR_SV_FRESH, Terminal::GET::WEAR_TEAR_SV_FRESH);

    if (_trigConcentrateValve.edgeDetection(pTerminal->getVal<bool>(Terminal::GET::SV_CONCENTRATE), EdgeDetection<bool>::type::RISING_EDGE, true))
        inc(Terminal::SET::WEAR_TEAR_SV_CONC, Terminal::GET::WEAR_TEAR_SV_CONC);
    
    if (_trigConcentrateValve.edgeDetection(pTerminal->getVal<bool>(Terminal::GET::SV_BACKFLOW), EdgeDetection<bool>::type::RISING_EDGE, true))
        inc(Terminal::SET::WEAR_TEAR_SV_BACK, Terminal::GET::WEAR_TEAR_SV_BACK);
    
    if (_trigConcentrateValve.edgeDetection(pTerminal->getVal<bool>(Terminal::GET::WEAR_TEAR_RL1), EdgeDetection<bool>::type::RISING_EDGE, true))
        inc(Terminal::SET::WEAR_TEAR_RL1, Terminal::GET::WEAR_TEAR_RL1);

    if (_trigConcentrateValve.edgeDetection(pTerminal->getVal<bool>(Terminal::GET::WEAR_TEAR_RL2), EdgeDetection<bool>::type::RISING_EDGE, true))
        inc(Terminal::SET::WEAR_TEAR_RL2, Terminal::GET::WEAR_TEAR_RL2);

    if (_trigConcentrateValve.edgeDetection(pTerminal->getVal<bool>(Terminal::GET::WEAR_TEAR_RL3), EdgeDetection<bool>::type::RISING_EDGE, true))
        inc(Terminal::SET::WEAR_TEAR_RL3, Terminal::GET::WEAR_TEAR_RL3);

    if (_trigConcentrateValve.edgeDetection(pTerminal->getVal<bool>(Terminal::GET::WEAR_TEAR_RL4), EdgeDetection<bool>::type::RISING_EDGE, true))
        inc(Terminal::SET::WEAR_TEAR_RL4, Terminal::GET::WEAR_TEAR_RL4);

    if (_trigConcentrateValve.edgeDetection(pTerminal->getVal<bool>(Terminal::GET::WEAR_TEAR_RL5), EdgeDetection<bool>::type::RISING_EDGE, true))
        inc(Terminal::SET::WEAR_TEAR_RL5, Terminal::GET::WEAR_TEAR_RL5);
    

}
/**
 * @brief increase the counter value 
 * @param _set 
 * @param _get 
 */
auto WearAndTear::inc(Terminal::SET _set, Terminal::GET _get) -> void
{
    auto counter = pTerminal->getVal<uint32_t>(_get);
    counter++;
    pTerminal->setVal(_set, counter);

}
/**
 * @brief Calculates the membrane SoH with the help of an exp average
 * 
 * @param _oldAvg Old Average 
 * @param _currVal Current Conductivity
 * @return uint16_t new calculated exponential average 
 */
auto WearAndTear:: calcMembraneSoH(const uint16_t _oldAvg, const uint16_t _current) -> uint16_t
{
    static auto smoothFac = 0.02F;

    return smoothFac*_current+(1-smoothFac)*_oldAvg;
}
/**
 * @brief Main loop in this class
 * 
 */
auto WearAndTear::run() -> void
{
    if(pIo==nullptr || pTerminal==nullptr)
        return;

    countSwitchingCycles();

    auto conductivity = pTerminal->getVal<uint16_t>(Terminal::GET::SENS_CONDUCTIVITY);
    auto newAvgConductivity1 = calcMembraneSoH(mOldAverage_membrane1, conductivity);
    pTerminal->setVal(Terminal::SET::WEAR_TEAR_MEMBRANE1, newAvgConductivity1);
}