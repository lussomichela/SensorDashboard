/**
 * @file RPMsgHandler.cpp
 * @brief Implementation of the RPMsgHandler class for handling Remote Processor Messaging (RPMsg).
 *
 * This file contains the logic for opening the RPMsg device, monitoring it for incoming
 * data using QSocketNotifier, and parsing the raw byte stream into CAN frame structures.
 */
#include "RPMsg.h"
#include "LedModel.h"


LedModel::LedModel(QObject *parent) : RPMsg(parent) {


}

/**
 * @brief Slot triggered when data is available on the RPMsg device.
 *
 * Reads all available bytes from the device. If the data size matches or exceeds
 * the expected CAN frame structure, it casts the raw data and emits signals
 * representing the engine fault and oil temperature states.
 */
void LedModel::update_data(const rpmsg_can_frame_t &structure)  {


    // Emit parsed states to the UI or other handlers
    emit stateEngineFault(structure.engine_fault);
    emit stateOilTemperature(structure.oil_temperature);
}



