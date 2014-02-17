# MCP23S17

This is an arduino library for using a MCP23S17. My particular use
case requires using an alternative SPI library, so none of the
existing libraries would work for me.

This library lets you pass in your own SPI transfer function and your
own call backs for doing slave selection.

## Usage

```c++
#include <tinySPI.h>
#include <MCP23S17.h>

#define GPIO_SS 3

void gpio_select()
{
  digitalWrite(GPIO_SS, LOW);
}

void gpio_unselect()
{
  digitalWrite(GPIO_SS, HIGH);
}

MCP23S17::Thing io0 = 
  MCP23S17::Thing(&gpio_select,
                  &gpio_unselect,
                  &tinySPI::transfer8,
                  B000);

void setup()
{
  /* */
  tinySPI::begin();
  
  /* */
  pinMode(GPIO_SS, OUTPUT);
  gpio_unselect();

  /* */
  io0.pinMode(0, OUTPUT);
  io0.pinMode(1, OUTPUT);
  io0.digitalWrite(0, HIGH);
}

void loop () 
{
  io0.digitalWrite(1, HIGH);
  delay(1000);
  io0.digitalWrite(1, LOW);
  delay(1000);
}
```

## License

MIT, see LICENSE

## See also

http://ww1.microchip.com/downloads/en/DeviceDoc/21952b.pdf
