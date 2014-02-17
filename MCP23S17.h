#include <avr/pgmspace.h>
#include <Arduino.h>

// TODO: HAEN support
#define WRITE B01000000
#define READ  B01000001

// registers
#define IOCON   0x0A
#define IODIR   0x00
#define GPIO    0x12
#define IPOL    0x02
#define GPINTEN 0x04
#define DEFVAL  0x06
#define INTCON  0x0A
#define GPPU    0x0c
#define INTF    0x0e
#define INTCAP  0x10
#define OLAT    0x14

namespace MCP23S17
{
  class Thing
  {
    void (*select) ();
    void (*unselect) ();
    uint8_t (*transfer) (uint8_t);
    uint8_t address;

  public:
    Thing(void (*select) (), 
          void (*unselect) (), 
          uint8_t (*transfer) (uint8_t),
          uint8_t address);
    void pinMode(uint8_t pin, bool mode);
    void digitalWrite(uint8_t pin, bool value);
    void writePort(uint16_t value);
    uint16_t readPort();
    bool digitalRead(uint8_t pin);
  };
};
