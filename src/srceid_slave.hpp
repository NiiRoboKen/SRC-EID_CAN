#pragma once

#include <esp_can.hpp>
#include "srceid_id_edit.hpp"

namespace NNCT {
namespace SRCEID {
    
class Slave {
    public:
    
    Slave(CanDriver& can_driver, uint8_t master_id, uint8_t slave_id);
    void onReceive(twai_message_t& msg);
    void boot();
    void poweroff();
    void ping();

    enum class State {
        GOING_TO_BED,
        SLEPT,
        SLEEPING,
        BOOTING,
        BOOTED,
        RECEIVING_PING,
        RETURNED_PONG,
        ERROR,
        RUNNING
    };
    
    State is();

    protected:
    CanDriver&  m_can_driver;
    State       m_state;
    uint8_t     m_slave_id;
    Identifier  m_persed_id;
    uint8_t     m_tx_buf[8];
    uint8_t     m_tx_buf_len;
    
    void send(uint16_t command);
    void payload_write(uint8_t *payload, uint8_t payload_len, uint8_t payload_max_len);
    virtual void virtualOnReceive(twai_message_t& msg) = 0;

    void boot(uint8_t *payload, uint8_t payload_len);
    void poweroff(uint8_t *payload, uint8_t paylaod_len);
    void ping(uint8_t *payload, uint8_t payload_len);
};

}
}
