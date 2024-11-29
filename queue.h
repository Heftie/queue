/**
  ******************************************************************************
  * @file    queue.h
  * @author  Jonas Sigmund
  * @date    2024-11-22
  * @brief   queue
  *          This is a simple queue implementation for an embedded system
  *          using a circular buffer to store data.
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdlib.h"
/* Exported types ------------------------------------------------------------*/
typedef enum {
    QUEUE_OK = 0,
    QUEUE_FULL,
    QUEUE_EMPTY,
    QUEUE_ERROR
} queue_status_t;

typedef struct {
    uint8_t *buffer;
    uint32_t size;
    uint32_t head;
    uint32_t tail;
    uint32_t count;
} queue_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

queue_status_t queue_init(queue_t *queue, uint8_t *buffer, uint32_t size);
queue_status_t queue_enqueue(queue_t *queue, uint8_t data);
queue_status_t queue_dequeue(queue_t *queue, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif  /* QUEUE_H */