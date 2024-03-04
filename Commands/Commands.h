#ifndef RX_CONTROL_COMMANDS_H
#define RX_CONTROL_COMMANDS_H

#include "Broadcast_packet_structure.h"
#include "..\TCP/TCP.h"

#pragma once
#pragma pack(push, 1)

//Блок команд
/// @brief Заголовок запроса в ПРМ
struct header_req
{
    uint32_t size;
    uint32_t messid;
    uint16_t cmd_type;
};

/// @brief (0x1) Запроса состояния ПРМ
struct state
{
    header_req head;
};

/// @brief (0x2) Настроить ПРМ на частоту:
struct set_freq
{
    header_req head;

    uint32_t carrier_freq_Hz;
};

/// @brief (0xC) Управление потоком. Старт немедленно. Отменяет ожидание синхросигнала
struct ctrl_iq_stream_now
{
    header_req head;

    // dest ip в пакетах потока, если 0, то будет выбран ip
    // из dest_ip tcp сокета управляющего соединением
    uint32_t IP_stream;

    // dest port в пакетах потока, если 0, то будет выбран ip
    // из dest_port tcp сокета управляющего соединения
    uint16_t port_stream;

    // установить ЗПЧ, если 0xffff, то используется текущая частота
    uint16_t preset_num;
};

//Блок ответов
/// @brief Заголовок ответа от ПРМ
struct header_ans
{
    uint32_t size;
    uint32_t messid;
    uint16_t cmd_type;
    uint16_t cmd_ack_type;
    uint16_t cmd_complete; // enum cmd_complete_t
};

/// @brief Данные для ответа состояния ПРМ
struct status_data
{
    uint32_t size;
    uint32_t messid;
    uint16_t cmd_type;
    uint16_t cmd_ack_type;
    uint16_t cmd_complete; // enum cmd_complete_t

    uint8_t ant;              // enum ant_t *RXTX
    uint32_t sample_rate_Hz;  // частота дискретизации *RXTX
    uint32_t carrier_freq_Hz; // несущая частота *RXTX
    uint16_t preset_num;      // номер ЗПЧ, если не выбрано, то 0xffff *RXTX
    uint32_t att_bitmask;     // битовая маска включенных ступеней аттенюации *RXTX
    float att_dB;             // общее ослабление сигнала в дБ *RXTX

    uint8_t xcvr_state;          // enum xsvr_state_t, состояния машины состояний *RXTX
    uint8_t modulation;          // enum modulation_t, тип модуляции *RXTX
    uint8_t ctrl;                // enum ctrl_t, управление удаленное, ручное *RXTX
    uint8_t sync_ctrl;           // enum sync_ctrl_t,  срабатывание по фронту или по ПСП Баркера *RXTX
    uint8_t sync_status;         // enum sync_status_t, статус синхросигнала: ожидание, получен, таймаут, не используется *RXTX
    uint8_t gen;                 // enum gen_t, опорный генератор внутренний или внешний
    uint8_t debug_mode;          // enum debug_mode_t, включен или нет режим дебага

    float adc_temp_C;         // температура ячейки ЦОС, цельсии
    float preselector_temp_C; // температура преселектора 0 канала, цельсии

    uint8_t stream_status;    // enum stream_status_t  поток отдается или нет *RX *TX
    uint32_t stream_IP;       // dst ip в UDP-пакетах потока *RX
    uint16_t stream_src_port; // src port в UDP-пакетах потока *RX
    uint16_t stream_dst_port; // dst port в UDP-пакетах потока *RX *TX

    uint8_t test_low_sens_state; // enum test_low_sens_state_t *RX

    uint32_t hardware_errors_bitmask; // битовая маска, enum hardware_error_t *RXTX
    uint32_t software_errors_bitmask; // битовая маска, enum software_error_t *RXTX
};

class Commands {
public:
    std::vector<char> Get_Status();
    int Set_Freq(uint32_t  freq);
    int Get_IQ();
};

#pragma pack(pop)

#endif //RX_CONTROL_COMMANDS_H
