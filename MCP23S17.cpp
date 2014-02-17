#include <avr/pgmspace.h>
#include <Arduino.h>
#include <MCP23S17.h>

// TODO: interrupt support

namespace MCP23S17
{

  void write_addr_raw(uint8_t (*transfer) (uint8_t),
                      uint8_t address,
                      uint8_t addr, 
                      uint16_t data)
  {
    transfer((WRITE & ~(B111 << 1)) | (address << 1));
    transfer(addr);
    transfer(data & 0xff);
    transfer((data >> 8) & 0xff);
  }

  uint16_t read_addr_raw(uint8_t (*transfer) (uint8_t), 
                         uint8_t address,
                         uint8_t addr)
  {
    uint8_t h,l;
    transfer((READ & ~(B111 << 1)) | (address << 1));
    transfer(addr);
    l = transfer(0x0);
    h = transfer(0x0);
    return  ((((uint16_t)h) << 8) | ((uint16_t)l));
  }

  Thing::Thing(void (*select) (), 
               void (*unselect) (),
               uint8_t (*transfer) (uint8_t),
               uint8_t address)
  {
    this->select   = select;
    this->unselect = unselect;
    this->transfer = transfer;
    this->address  = address;
    // TODO: send enable HAEN
  }

  void Thing::pinMode(uint8_t pin, bool mode)
  {
    uint16_t pins;

    select();
    pins = read_addr_raw(transfer, address, IODIR);
    unselect();

    if(mode == INPUT)
      {
        pins = (pins | (1 << pin));
      }
    else
      {
        pins = (pins & ~(1 << pin));
      }

    select();
    write_addr_raw(transfer, address, IODIR, pins);
    unselect();
  }

  void Thing::digitalWrite(uint8_t pin, bool mode)
  {
    uint16_t gpio;
      
    select();
    gpio = read_addr_raw(transfer, address, GPIO);
    unselect();

    select();
    if (mode)
      {
        write_addr_raw(transfer, address, GPIO, gpio | 1 << pin);
      }
    else
      {
        write_addr_raw(transfer, address, GPIO, gpio &  ~(1 << pin));
      }
    unselect();
  }

  bool Thing::digitalRead(uint8_t pin)
  {
    uint16_t gpio;
      
    select();
    gpio = read_addr_raw(transfer, address, GPIO);
    unselect();
    
    return ((gpio >> pin) & 1);
  }

  void Thing::writePort(uint16_t value)
  {
    select();
    write_addr_raw(transfer, address, GPIO, value);
    unselect();
  }

  uint16_t Thing::readPort()
  {
    uint16_t r;
    select();
    r = read_addr_raw(transfer, address, GPIO);
    unselect();
    return r;
  }

};
