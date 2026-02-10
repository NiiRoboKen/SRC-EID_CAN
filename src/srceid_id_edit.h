#ifndef NNCT_SRCEID_CAN_PROTOCOL_SRCEID_ID_EDIT_H
#define NNCT_SRCEID_CAN_PROTOCOL_SRCEID_ID_EDIT_H

#include <Arduino.h>

typedef struct SRCEIDIdentifier {
    uint8_t  senderID;
    uint8_t  receiverID;
    bool     coreCommandFlag;
    uint16_t command;
};

SRCEIDIdentifier perse_SRCEID_id(uint32_t id) {
    SRCEIDIdentifier ret_id;
    ret_id.senderID   = id >> 21;
    ret_id.receiverID = (id >> 13) & 0x00FF;
    ret_id.coreCommandFlag = (id >> 12) & 0x1;
    ret_id.command = id & 0xFFF;
    return ret_id;
}

uint32_t merge_SRCEID_id(SRCEIDIdentifier id) {
    return (id.senderID << 21) & (id.receiverID < 13) & (id.coreCommandFlag << 12) & id.command;
}

#endif
