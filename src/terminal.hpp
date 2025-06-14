#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <Arduino.h>
#include <EasyNextionLibrary.h>
#include <io.hpp>

class Terminal
{
private:
    EasyNex *pHMI;
    IO *pIo = nullptr;
    bool mInitDone;

    struct data
    {
        struct buttons
        {
            bool start;             // Startstop Button
            bool btnPumpPressCalib; // Button for calibration of the pump pressure sensor
        } btn;

        struct sensors
        {
            uint16_t conduct;
            uint16_t pumpPressure;
            uint16_t temperature;
            uint16_t membraneSecPressure;

        } sensor;

        struct digInputs
        {
            bool bufferTankFillStart;
            bool bufferTankFillStop;
            bool hardnessToHigh;
            bool pumpProtectionRelay;
        } digInputs;

        struct digOut
        {
            bool solenoidValveFreshwater;
            bool solenoidValveConcentrate;
            bool solenoidValveBackflow;
            bool freshwaterPump;
            bool bufferPump;
            bool collectiveFault; // Collective fault lamp
        } digOutputs;

        struct settings
        {
            struct time
            {
                uint16_t svFreshwaterOpen = 3;    // Time for opening the freshwater solenoid valve [s]
                uint16_t startStopDuration = 60;  // Time for the start stop duration [s]
                uint16_t rinseOperation = 24;     // Time for rinsing during operation [h]
                uint16_t rinseStop = 48;          // Time for rinsing after stopping the plant [h]
                uint16_t rinseCylicDuration = 10; // Cyclic duration for rinsing during operation [s]
                uint16_t debounceTime = 6;        // Debounce time for the floats [s]
            } tim;

            struct pressure
            {
                float pumpPressureCalibration = 0.0F; // Calibration value for the pump pressure sensor
                uint16_t freshOvrPress = 135;         // Overpressure for the freshwater pump [mbar]
                uint16_t freshUndPress = 10;          // Underpressure for the freshwater pump [mbar]
            } press;

            struct conductivity
            {
                uint16_t conductLowLim = 0;   // Lower limit for conductivity sensor [myS/cm]
                uint16_t conductUpLim = 1000; // Upper limit for conductivity sensor [myS/cm]
                int16_t tempLowLim = -5;      // Lower limit for the temperature sensor [°C]
                int16_t tempUpLim = 90;       // Upper limit for the temperature sensor [°C]
            } conduct;

            struct temperature
            {
                uint8_t frostWarn = 4;    // Warn Threshold at which frost message appears [°C]
                uint8_t ovrheatWarn = 30; // Warn Threshold at which overheat message appears [°C]
                uint8_t ovrheatErr = 35;  // Shutdown Threshold at which overheat message appears [°C]
            } temp;

        } setting;

        struct maintenance
        {
            uint32_t counter_sv_freshwater;
            uint32_t counter_sv_backflow;
            uint32_t counter_sv_concentrate;
            uint32_t counter_rl1;
            uint32_t counter_rl2;
            uint32_t counter_rl3;
            uint32_t counter_rl4;
            uint32_t counter_rl5;
            uint16_t membrane1;

        } maint;

        uint8_t plantState;
        bool plantOp;
        uint8_t messageId;
        bool retVarSucces;
        uint8_t currentPageId;
    };

public:
    enum class GET
    {
        BTN_START,
        BTN_PUMP_PRESS_CALIB,
        TIME_SV_FRESHWATER_OPEN,
        TIME_START_STOP_DURATION,
        TIME_RINSE_OPERATION,
        TIME_RINSE_STOP,
        TIME_RINSE_CYCLIC_DURATION,
        PUMP_PRESSURE,
        PRESSURE_PUMP_CALIBRATION,
        PRESSURE_PUMP_UNDERPRESSURE,
        PRESSURE_PUMP_OVERPRESSURE,
        SENS_CONDUCTIVITY,
        SENS_PUMP_PRESSURE,
        SENS_TEMPERATURE,
        SENS_MEMBRANE_SEC_PRESSURE,
        CONDUCT_LOWER_LIMIT,
        CONDUCT_UPPER_LIMIT,
        TEMPERATURE_LOWER_LIMIT,
        TEMPERATURE_UPPER_LIMIT,
        TEMPERATURE_FROST_WARN,
        TEMPERATURE_OVRHEAT_WARN,
        TEMPERATURE_OVRHEAT_ERR,
        SV_FRESHWATER,
        SV_CONCENTRATE,
        SV_BACKFLOW,
        FRESHWATER_PUMP,
        BUFFER_PUMP,
        COLLECTIVE_FAULT,
        WEAR_TEAR_SV_FRESH,
        WEAR_TEAR_SV_BACK,
        WEAR_TEAR_SV_CONC,
        WEAR_TEAR_RL1,
        WEAR_TEAR_RL2,
        WEAR_TEAR_RL3,
        WEAR_TEAR_RL4,
        WEAR_TEAR_RL5

    };

    enum class SET
    {
        SENS_CONDUCTIVITY,
        SENS_PUMP_PRESSURE,
        SENS_TEMPERATURE,
        SENS_MEMBRANE_SEC_PRESSURE,
        D23_BUFFER_MIN,
        D24_BUFFER_MAX,
        D25_HARDNESS,
        D28_F1F,
        RL1_SV_FRESHWATER,
        RL2_SV_CONCENTRATE,
        RL3_SV_BACKFLOW,
        RL4_PUMP,
        RL5_COLLECTIVE_FAULT,
        PLANT_OPERATIONAL,
        MESSAGE_ID,
        WEAR_TEAR_MEMBRANE1,
        WEAR_TEAR_SV_FRESH,
        WEAR_TEAR_SV_BACK,
        WEAR_TEAR_SV_CONC,
        WEAR_TEAR_RL1,
        WEAR_TEAR_RL2,
        WEAR_TEAR_RL3,
        WEAR_TEAR_RL4,
        WEAR_TEAR_RL5
    };

    enum class MESSAGE_ID
    {
        NONE,
        PLANT_STARTED,
        PERMEATE_PRODUCTION,
        BUFFERTANK_FULL,
        BUFFERTANK_EMPTY,
        ERR_F1F,
        ERR_HARDNESS,
        ERR_BUFFERTANK_PLAUSIBILITY,
        ERR_PUMP_PRESSURE_LOW,
        ERR_PUMP_PRESSURE_HIGH,

    };

    auto begin(IO &) -> void;
    auto run() -> void;
    auto isAlive() -> bool;

    template <typename T>
    auto getVal(GET _get) -> T
    {
        switch (_get)
        {
        case Terminal::GET::BTN_START:
            return static_cast<T>(mData.btn.start);
            break;
        case Terminal::GET::BTN_PUMP_PRESS_CALIB:
            return static_cast<T>(mData.btn.btnPumpPressCalib);
            break;
        case Terminal::GET::TIME_SV_FRESHWATER_OPEN:
            return static_cast<T>(mData.setting.tim.svFreshwaterOpen);
            break;
        case Terminal::GET::TIME_START_STOP_DURATION:
            return static_cast<T>(mData.setting.tim.startStopDuration);
            break;
        case Terminal::GET::TIME_RINSE_OPERATION:
            return static_cast<T>(mData.setting.tim.rinseOperation);
            break;
        case Terminal::GET::TIME_RINSE_STOP:
            return static_cast<T>(mData.setting.tim.rinseStop);
            break;
        case Terminal::GET::TIME_RINSE_CYCLIC_DURATION:
            return static_cast<T>(mData.setting.tim.rinseCylicDuration);
            break;
        case Terminal::GET::PRESSURE_PUMP_OVERPRESSURE:
            return static_cast<T>(mData.setting.press.freshOvrPress);
            break;
        case Terminal::GET::PRESSURE_PUMP_UNDERPRESSURE:
            return static_cast<T>(mData.setting.press.freshUndPress);
            break;
        case Terminal::GET::CONDUCT_LOWER_LIMIT:
            return static_cast<T>(mData.setting.conduct.conductLowLim);
            break;
        case Terminal::GET::CONDUCT_UPPER_LIMIT:
            return static_cast<T>(mData.setting.conduct.conductUpLim);
            break;
        case Terminal::GET::TEMPERATURE_LOWER_LIMIT:
            return static_cast<T>(mData.setting.conduct.tempLowLim);
            break;
        case Terminal::GET::TEMPERATURE_UPPER_LIMIT:
            return static_cast<T>(mData.setting.conduct.tempUpLim);
            break;
        case Terminal::GET::SV_FRESHWATER:
            return static_cast<T>(mData.digOutputs.solenoidValveFreshwater);
            break;
        case Terminal::GET::SV_CONCENTRATE:
            return static_cast<T>(mData.digOutputs.solenoidValveConcentrate);
            break;
        case Terminal::GET::SV_BACKFLOW:
            return static_cast<T>(mData.digOutputs.solenoidValveBackflow);
            break;
        case Terminal::GET::FRESHWATER_PUMP:
            return static_cast<T>(mData.digOutputs.freshwaterPump);
            break;
        case Terminal::GET::BUFFER_PUMP:
            return static_cast<T>(mData.digOutputs.bufferPump);
            break;
        case Terminal::GET::COLLECTIVE_FAULT:
            return static_cast<T>(mData.digOutputs.collectiveFault);
            break;
        case Terminal::GET::TEMPERATURE_FROST_WARN:
            return static_cast<T>(mData.setting.temp.frostWarn);
            break;
        case Terminal::GET::TEMPERATURE_OVRHEAT_WARN:
            return static_cast<T>(mData.setting.temp.ovrheatWarn);
            break;
        case Terminal::GET::TEMPERATURE_OVRHEAT_ERR:
            return static_cast<T>(mData.setting.temp.ovrheatErr);
            break;
        case Terminal::GET::WEAR_TEAR_SV_FRESH:
            return static_cast<T>(mData.maint.counter_sv_freshwater);
            break; 
        case Terminal::GET::WEAR_TEAR_SV_BACK:
            return static_cast<T>(mData.maint.counter_sv_backflow);
            break;
        case Terminal::GET::WEAR_TEAR_SV_CONC:
            return static_cast<T>(mData.maint.counter_sv_concentrate);
            break;
        case Terminal::GET::WEAR_TEAR_RL1:
            return static_cast<T>(mData.maint.counter_rl1);
            break;
        case Terminal::GET::WEAR_TEAR_RL2:
            return static_cast<T>(mData.maint.counter_rl2);
            break;
        case Terminal::GET::WEAR_TEAR_RL3:
            return static_cast<T>(mData.maint.counter_rl3);
            break;
        case Terminal::GET::WEAR_TEAR_RL4:
            return static_cast<T>(mData.maint.counter_rl4);
            break;
        case Terminal::GET::WEAR_TEAR_RL5:
            return static_cast<T>(mData.maint.counter_rl5);
            break; 
        case Terminal::GET::SENS_CONDUCTIVITY:
            return static_cast<T>(mData.sensor.conduct); 
            break;   
        case Terminal::GET::SENS_MEMBRANE_SEC_PRESSURE:
            return static_cast<T>(mData.sensor.membraneSecPressure); 
            break;  
        case Terminal::GET::SENS_PUMP_PRESSURE:
            return static_cast<T>(mData.sensor.pumpPressure); 
            break; 
        case Terminal::GET::SENS_TEMPERATURE:
            return static_cast<T>(mData.sensor.temperature); 
            break; 
        default : 
            return false;
            break;
        }
    }

    template <typename T>
    auto setVal(SET _set, T _T) -> void
    {

        switch (_set)
        {
        case Terminal::SET::SENS_CONDUCTIVITY:
            mData.sensor.conduct = static_cast<uint16_t>(_T);
            break;
        case Terminal::SET::SENS_PUMP_PRESSURE:
            mData.sensor.pumpPressure = static_cast<uint16_t>(_T);
            break;
        case Terminal::SET::SENS_TEMPERATURE:
            mData.sensor.temperature = static_cast<uint16_t>(_T);
            break;
        case Terminal::SET::SENS_MEMBRANE_SEC_PRESSURE:
            mData.sensor.membraneSecPressure = static_cast<uint16_t>(_T);
            break;
        case Terminal::SET::PLANT_OPERATIONAL:
            mData.plantOp = static_cast<bool>(_T);
            break;
        case Terminal::SET::MESSAGE_ID:
            mData.messageId = static_cast<uint8_t>(_T);
            break;
        case Terminal::SET::D23_BUFFER_MIN:
            mData.digInputs.bufferTankFillStart = static_cast<bool>(_T);
            break;
        case Terminal::SET::D24_BUFFER_MAX:
            mData.digInputs.bufferTankFillStop = static_cast<bool>(_T);
            break;
        case Terminal::SET::D25_HARDNESS:
            mData.digInputs.hardnessToHigh = static_cast<bool>(_T);
            break;
        case Terminal::SET::D28_F1F:
            mData.digInputs.pumpProtectionRelay = static_cast<bool>(_T);
            break;
        case Terminal::SET::RL1_SV_FRESHWATER:
            mData.digOutputs.solenoidValveFreshwater = static_cast<bool>(_T);
            break;
        case Terminal::SET::RL2_SV_CONCENTRATE:
            mData.digOutputs.solenoidValveConcentrate = static_cast<bool>(_T);
            break;
        case Terminal::SET::RL3_SV_BACKFLOW:
            mData.digOutputs.solenoidValveBackflow = static_cast<bool>(_T);
            break;
        case Terminal::SET::RL4_PUMP:
            mData.digOutputs.freshwaterPump = static_cast<bool>(_T);
            break;
        case Terminal::SET::RL5_COLLECTIVE_FAULT:
            mData.digOutputs.collectiveFault = static_cast<bool>(_T);
            break;
        case Terminal::SET::WEAR_TEAR_SV_FRESH:
            mData.maint.counter_sv_freshwater = static_cast<bool>(_T);
            break; 
        case Terminal::SET::WEAR_TEAR_SV_BACK:
            mData.maint.counter_sv_backflow = static_cast<bool>(_T);
            break;
        case Terminal::SET::WEAR_TEAR_SV_CONC:
            mData.maint.counter_sv_concentrate = static_cast<bool>(_T);
            break;
        case Terminal::SET::WEAR_TEAR_RL1:
            mData.maint.counter_rl1 = static_cast<bool>(_T);
            break;
        case Terminal::SET::WEAR_TEAR_RL2:
            mData.maint.counter_rl2 = static_cast<bool>(_T);
            break;
        case Terminal::SET::WEAR_TEAR_RL3:
            mData.maint.counter_rl3 = static_cast<bool>(_T);
            break;
        case Terminal::SET::WEAR_TEAR_RL4:
            mData.maint.counter_rl4 = static_cast<bool>(_T);
            break;
        case Terminal::SET::WEAR_TEAR_RL5:
            mData.maint.counter_rl5 = static_cast<bool>(_T);
            break;  
        case Terminal::SET::WEAR_TEAR_MEMBRANE1:
            mData.maint.membrane1 = static_cast<uint16_t>(_T);
        default:
            break;
        }
    }

private:
    data mData;
    auto sendToHMI() -> void;
    auto readFromHMI() -> void;
};

#endif