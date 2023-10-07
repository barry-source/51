#include "gpio.h"

#ifndef _DHT11_H_
#define _DHT11_H_
extern char datas[5];

void dht_mode(uint32_t mode);

void check_dht(void);

int8_t trig_dht(void);

void receive_data(void);

#endif

