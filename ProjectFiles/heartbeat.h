/*
 * light.h
 *
 *  Created on: Apr 24, 2019
 *      Author: joel
 */
#include <pthread.h>

#ifndef LIGHT_H_
#define LIGHT_H_
extern pthread_t        heartbeat_handler;
extern void *heartbeat(void *arg0);


#endif /* LIGHT_H_ */
