#include "srceid_slave.hpp"

namespace NNCT {
namespace SRCEID {
    
Slave::Slave(CanDriver& can_driver, uint8_t master_id, uint8_t slave_id) :
    m_can_driver(can_driver),
    m_slave_id(slave_id),
    m_persed_id(Identifier(master_id, slave_id)) {

}

void Slave::onReceive(twai_message_t& msg) {
    virtualOnReceive(msg);    
}

void Slave::send(bool core_command_flag, uint16_t command) {
    m_can_driver.sendExtended(merge_id(m_persed_id), m_tx_buf, m_tx_buf_len);
}

void Slave::payload_write(uint8_t *payload, uint8_t payload_len, uint8_t payload_max_len) {
    if(payload_len > payload_max_len) throw;
    for(int i = 0; i < payload_len; i++) m_tx_buf[i] = payload[i];
    m_tx_buf_len = payload_len;
}

}
}
