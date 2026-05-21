/**
 * @file RPMsgHandler.h
 * @brief Header file for the RPMsgHandler class.
 *
 * This file defines the class responsible for Inter-Process Communication (IPC)
 * between the Linux Guest and Windows Host environments using RPMSG.
 */

#ifndef LEDMODEL_H
#define LEDMODEL_H
#include "RPMsg.h"

/*
 * @class LedModel
 * @brief Handles communication between Linux (Guest) and Windows (Host) via RPMSG.
 *
 * This class manages data reception from the RPMSG character device.
 * It monitors the device for incoming raw bytes and parses them into
 * structured data, emitting signals to update the UI components.
 */

class LedModel : public RPMsg {
    Q_OBJECT

public:
    explicit LedModel(QObject *parent = nullptr);
    void update_data(const rpmsg_can_frame_t &structure);

signals:
    /**
     * @brief Signal emitted when the engine fault state changes.
     * @param state The current state of the engine fault.
     */
    void stateEngineFault(int state);

    /**
     * @brief Signal emitted when the oil temperature warning state changes.
     * @param state The current state of the oil temperature warning.
     */
    void stateOilTemperature(int state);



};


#endif
