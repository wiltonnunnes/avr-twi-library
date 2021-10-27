#include "twi_master.h"

void twi_init() {
  TWSR = 0x0C;
  TWBR = 0x0C;
  TWCR = (1 << TWEN);
}

void twi_start() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while ((TWCR & (1 << TWINT)) == 0);
}

void twi_stop() {
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

uint8_t twi_write(uint8_t data) {
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (TWCR & (1 << TWINT));
  if ((TWSR & 0xF8) != 0x28)
    return 1;
  return 0;
}