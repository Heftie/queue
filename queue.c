/**
  ******************************************************************************
  * @file    queue.c
  * @author  Jonas Sigmund
  * @date    2024-11-22
  * @brief   queue
  *          This is a simple queue implementation for an embedded system
  *          using a circular buffer to store data. This implementation uses a
  *          static buffer. The buffer is defined by the user by creating an 
  *          array of uint8_t and passing it to the queue_init function.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
# include "queue.h"  

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 * @brief Initialize the queue with a buffer and size
 * 
 * @param queue   Pointer to the queue structure
 * @param buffer  Pointer to the buffer array where the data will be stored
 * @param size    Size of the buffer array
 * @return queue_status_t 
 */
queue_status_t queue_init(queue_t *queue, uint8_t *buffer, uint32_t size)
{
    if (queue == NULL || buffer == NULL || size == 0)
    {
        return QUEUE_ERROR;
    }

    queue->buffer = buffer;
    queue->size = size;
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;

    return QUEUE_OK;
}


/**
 * @brief Enqueue data to the queue
 * 
 * @param queue   Pointer to the queue structure
 * @param data    Pointer to the data variable where the data will be stored
 * @return queue_status_t 
 */
queue_status_t queue_enqueue(queue_t *queue, uint8_t data)
{
    // Check first if the queue exists to prevent null pointer dereference
    if (queue == NULL)
    {
        return QUEUE_ERROR;
    }
    if (queue->buffer == NULL || queue->size == 0)
    {
        return QUEUE_ERROR;
    }

    if (queue->count == queue->size)
    {
        return QUEUE_FULL;
    }

    queue->buffer[queue->tail] = data;
    queue->tail = (queue->tail + 1) % queue->size;
    queue->count++;

    return QUEUE_OK;
}


/**
 * @brief Dequeue data from the queue
 * 
 * @param queue   Pointer to the queue structure
 * @param data    Pointer to the data variable where the data will be stored
 * @return queue_status_t 
 */
queue_status_t queue_dequeue(queue_t *queue, uint8_t *data)
{
    // Check first if the queue exists to prevent null pointer dereference
    if (queue == NULL)
    {
        return QUEUE_ERROR;
    }
    if (queue->buffer == NULL || queue->size == 0)
    {
        return QUEUE_ERROR;
    }

    if (queue->count == 0)
    {
        return QUEUE_EMPTY;
    }

    *data = queue->buffer[queue->head];
    queue->head = (queue->head + 1) % queue->size;
    queue->count--;

    return QUEUE_OK;
}

/* Private functions ---------------------------------------------------------*/