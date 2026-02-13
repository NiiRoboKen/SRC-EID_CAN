#include "srceid_slave.hpp"

namespace {
    constexpr uint16_t BOOT            {0x1000};
    constexpr uint16_t BOOT_NOTICE     {0x1001};
    constexpr uint16_t POWEROFF        {0x1002};
    constexpr uint16_t POWEROFF_NOTICE {0x1003};
    constexpr uint16_t ERROR           {0x1004};
    constexpr uint16_t PING            {0x1005};
    constexpr uint16_t PONG            {0x1006};
}

namespace NNCT {
namespace SRCEID {
    
Slave::Slave(CanDriver& can_driver, uint8_t master_id, uint8_t slave_id) :
    m_can_driver(can_driver),
    m_state(State::SLEEPING),
    m_slave_id(slave_id),
    m_persed_id(Identifier(master_id, slave_id)) {

}

void Slave::onReceive(twai_message_t& msg) {
    Identifier persed_id = perse_id(msg.identifier);
    if(persed_id.senderID != m_slave_id) return;
    
    switch(m_state) {
        case State::BOOTED:
            m_state = State::RUNNING;
            break;
        case State::SLEPT:
            m_state = State::SLEEPING;
            break;
        case State::RETURNED_PONG:
            m_state = State::RUNNING;
    }
    if(persed_id.command >> 12) {
        switch(persed_id.command) {
            case BOOT_NOTICE:
                m_state = State::BOOTED;
                break;
            case POWEROFF_NOTICE:
                m_state = State::SLEPT;
                break;
            case ERROR:
                m_state = State::ERROR;
                break;
            case PONG:
                m_state = State::RETURNED_PONG;
                break;
            default:
                break;
        }
    }
    
    virtualOnReceive(msg);    
}

void Slave::boot()      { this->boot(nullptr, 0); }
void Slave::poweroff()  { this->poweroff(nullptr, 0); }
void Slave::ping()      { this->ping(nullptr, 0); }

Slave::State Slave::is() { return m_state; }

void Slave::send(uint16_t command) {
    m_persed_id.command = command;
    m_can_driver.sendExtended(merge_id(m_persed_id), m_tx_buf, m_tx_buf_len);
}

void Slave::payload_write(uint8_t *payload, uint8_t payload_len, uint8_t payload_max_len) {
    if(payload_len > payload_max_len) throw;
    for(int i = 0; i < payload_len; i++) m_tx_buf[i] = payload[i];
    m_tx_buf_len = payload_len;
}

void Slave::boot(uint8_t *payload, uint8_t payload_len) {
    payload_write(payload, payload_len, 8);
    send(BOOT);
}
void Slave::poweroff(uint8_t *payload, uint8_t payload_len) {
    payload_write(payload, payload_len, 8);
    send(POWEROFF);
}
void Slave::ping(uint8_t *payload, uint8_t payload_len) {
    payload_write(payload, payload_len, 8);
    send(PING);
}

}
}
