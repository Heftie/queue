# Queue Module

This is a simple queue handler implemented in C, designed to be reused for simple tasks like queues for embedded interfaces such as SPI or UART. The module uses a circular buffer to store data, providing efficient enqueue and dequeue operations.

## Features

- Circular buffer implementation
- Enqueue and dequeue operations
- Error handling for full and empty queues
- Initialization with custom buffer and size

## Usage

### Include the Header

Include the `queue.h` header file in your source code to use the queue functions.

### Initialize the Queue
Initialize the queue with a buffer and size using the queue_init function. This function returns a pointer to the initialized queue.

```c
queue_t *queue = queue_init(buffer, size);
```

### Enqueue Data
To add data to the queue, use the `queue_enqueue` function. This function takes the queue pointer and the data to be enqueued as arguments.

```c
queue_enqueue(queue, data);
```

### Dequeue Data
To remove data from the queue, use the `queue_dequeue` function. This function takes the queue pointer as an argument and returns the dequeued data.

```c
data = queue_dequeue(queue);
```

### Error Handling
The `queue_enqueue` and `queue_dequeue` functions return an error code to indicate if the operation was successful. The error codes are defined in the `queue.h` header file.

```c
error = queue_enqueue(queue, data);
if (error == QUEUE_FULL) {
    // Handle full queue error
}
```

## Example

```c
#include "queue.h"

int main() {
    uint8_t buffer[10];
    queue_t *queue = queue_init(buffer, 10);

    queue_enqueue(queue, 1);
    queue_enqueue(queue, 2);
    queue_enqueue(queue, 3);

    uint8_t data = queue_dequeue(queue); // data = 1
    data = queue_dequeue(queue); // data = 2
    data = queue_dequeue(queue); // data = 3

    queue_destroy(queue);

    return 0;
}
