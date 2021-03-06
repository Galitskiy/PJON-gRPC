#define PJON_INCLUDE_PACKET_ID
#define TS_RESPONSE_TIME_OUT 150000
#include <PJONThroughSerial.h>
#include <PJONSoftwareBitBang.h>

const byte deviceID = 1;
PJONThroughSerial busA(5);
PJONSoftwareBitBang busB(deviceID);


void receiver_functionA(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  // Forward packet to specified target device on bus B
  busA.strategy.send_response(PJON_ACK);
  busB.forward(packet_info, (char *)payload, length);
}

void receiver_functionB(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  // Forward packet to remote worker on bus A
  busA.forward(packet_info, (char *)payload, length);
}

void loop() {
  busA.receive();
  busB.update();
  busB.receive();
  busA.update();
};

void setup() {
  Serial.begin(57600);

  // PRi
  busA.strategy.set_serial(&Serial);
  busA.set_receiver(receiver_functionA);
  busA.set_acknowledge(true);
  busA.set_crc_32(true);
  busA.set_router(true);
  busA.set_packet_id(true);
  busA.begin();

  // Devices via SoftwareBitBang
  busB.strategy.set_pin(7);
  busB.set_receiver(receiver_functionB);
  busB.set_acknowledge(true);
  busB.set_crc_32(true);
  busB.set_packet_id(true);
  busB.begin();
}
