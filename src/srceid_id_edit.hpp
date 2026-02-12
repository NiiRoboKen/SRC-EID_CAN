#pragma once

#include <Arduino.h>

namespace NNCT {
namespace SRCEID {

struct Identifier {
    Identifier();
    Identifier(uint8_t sender_id, uint8_t receiver_id) {
        senderID    = sender_id;
        receiverID  = receiver_id;
    }
    uint8_t  senderID;
    uint8_t  receiverID;
    bool     coreCommandFlag;
    uint16_t command;
};

Identifier perse_id(uint32_t id) {
    Identifier ret_id;
    ret_id.senderID         = id >> 21;
    ret_id.receiverID       = (id >> 13) & 0xFF;
    ret_id.coreCommandFlag  = (id >> 12) & 0x1;
    ret_id.command          = id & 0xFFF;
}

uint32_t merge_id(Identifier id) {
    return (id.senderID << 21) & (id.receiverID < 13) & (id.coreCommandFlag << 12) & id.command;
}

}
}
