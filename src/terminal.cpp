#include "terminal.hpp"

/**
 * @brief Init Nextion communication
 * 
 */
auto Terminal::begin(IO& _io) -> void
{
    if(mInitDone)
        return; 
    
    pIo = &_io;
    pHMI = new EasyNex(Serial);
    mInitDone = true; 
}
/**
 * @brief 
 * 
 */
auto Terminal::run() -> void
{
    if(!mInitDone || pHMI == nullptr)
        return;
    
    pHMI->NextionListen();
    readFromHMI();
    sendToHMI();


}
/**
 * @brief 
 * 
 */
auto Terminal::sendToHMI() -> void
{
    // Analog inputs
    pHMI->writeNum("mcu.A0_pumpPress.val", mData.sensor.pumpPressure);
    pHMI->writeNum("mcu.A1_secPress1.val", mData.sensor.membraneSecPressure);
    pHMI->writeNum("mcu.A8_conduct.val", mData.sensor.conduct);
    pHMI->writeNum("mcu.A9_Temperature.val", mData.sensor.temperature);
    // Digital Inputs
    pHMI->writeNum("mcu.D23_bufferMin.val", mData.digInputs.bufferTankFillStart);
    pHMI->writeNum("mcu.D24_bufferMax.val", mData.digInputs.bufferTankFillStop);
    pHMI->writeNum("mcu.D25_hardness.val", mData.digInputs.hardnessToHigh);
    pHMI->writeNum("mcu.D28_ProtRelay.val", mData.digInputs.pumpProtectionRelay);
    // Digital Outputs
    pHMI->writeNum("mcu.RL1_SV_Fresh.va", mData.digOutputs.solenoidValveFreshwater);
    pHMI->writeNum("mcu.RL2_SV_Conc.val", mData.digOutputs.solenoidValveConcentrate);
    pHMI->writeNum("mcu.RL3_SV_Back.val", mData.digOutputs.solenoidValveBackflow);
    pHMI->writeNum("mcu.RL4_Pump.val", mData.digOutputs.freshwaterPump);
    pHMI->writeNum("mcu.RL5_CollFault.val", mData.digOutputs.collectiveFault);

    // States
    pHMI->writeNum("mcu.plantState.val", mData.plantState);
    pHMI->writeNum("mcu.plantOp.val", mData.plantOp);


}
/**
 * @brief 
 * 
 */
auto Terminal::readFromHMI() -> void
{  
    mData.btn.start = pHMI->readNumber("mcu.start.val");
    mData.retVarSucces = pHMI->readNumber("mcu.retVarSuccess.val");

    // Overwrite MCU Data if HMI Connection is present
    if(mData.retVarSucces)
    {
        mData.setting.tim.startStopDuration         = pHMI->readNumber("Opt_Rinse1.n0.val");
        mData.setting.tim.rinseOperation            = pHMI->readNumber("Opt_Rinse1.n1.val");
        mData.setting.tim.rinseStop                 = pHMI->readNumber("Opt_Rinse1.n2.val");
        mData.setting.tim.rinseCylicDuration        = pHMI->readNumber("Opt_Rinse1.n3.val");

        mData.setting.tim.svFreshwaterOpen          = pHMI->readNumber("Opt_Freshwtr1.n0.val");
        mData.setting.press.freshOvrPress           = pHMI->readNumber("Opt_Freshwtr1.x1.val");
        mData.setting.press.freshUndPress           = pHMI->readNumber("Opt_Freshwtr1.x2.val");

        mData.setting.tim.debounceTime              = pHMI->readNumber("Opt_Buffer1.n0.val");

        mData.btn.btnPumpPressCalib                 = pHMI->readNumber("mcu.DoPumpCalib.val");
        mData.currentPageId                         = pHMI->readNumber("mcu.currentPageId.val");
        
        mData.maint.counter_sv_freshwater           = pHMI->readNumber("maint_WearTear.count_SV_Fresh.val");
        mData.maint.counter_sv_backflow             = pHMI->readNumber("maint_WearTear.count_SV_Back.val");
        mData.maint.counter_sv_concentrate          = pHMI->readNumber("maint_WearTear.count_SV_Conc.val");
        mData.maint.counter_rl1                     = pHMI->readNumber("maint_WearTear.count_RL1.val");
        mData.maint.counter_rl2                     = pHMI->readNumber("maint_WearTear.count_RL2.val");
        mData.maint.counter_rl3                     = pHMI->readNumber("maint_WearTear.count_RL3.val");
        mData.maint.counter_rl4                     = pHMI->readNumber("maint_WearTear.count_RL4.val");
        mData.maint.counter_rl5                     = pHMI->readNumber("maint_WearTear.count_RL5.val");
    }
}
/**
 * @brief  Return true if retentive Variables in HMI could be loaded
 * 
 * @return true 
 * @return false 
 */
auto Terminal::isAlive() -> bool 
{
    return mData.retVarSucces == true ? true : false; 
}