# Queue Module

This is a simple queue handler implemented in C, designed to be reused for simple tasks like queues for embedded interfaces such as SPI or UART. The module uses a circular buffer to store data, providing efficient enqueue and dequeue operations.

## Features

- Circular buffer implementation
- Enqueue and dequeue operations
- Error handling for full and empty queues
- Initialization with custom buffer, size, and element size

## Usage

### Include the Header

Include the `queue.h` header file in your source code to use the queue functions.

### Initialize the Queue
Initialize the queue with a buffer, size, and element size using the `queue_init` function. This function returns a status code indicating the result of the initialization.

```c
queue_t queue;
uint8_t buffer[10];
queue_status_t status = queue_init(&queue, buffer, 10, sizeof(uint8_t));
```

### Enqueue Data
To add data to the queue, use the `queue_enqueue` function. This function takes the queue pointer and the data to be enqueued as arguments.

```c
uint8_t data = 1;
queue_status_t status = queue_enqueue(&queue, &data);
```

### Dequeue Data
To remove data from the queue, use the `queue_dequeue` function. This function takes the queue pointer and a pointer to the variable where the dequeued data will be stored.

```c
uint8_t data;
queue_status_t status = queue_dequeue(&queue, &data);
```

### Error Handling
The `queue_enqueue` and `queue_dequeue` functions return an error code to indicate if the operation was successful. The error codes are defined in the `queue.h` header file.

```c
queue_status_t status = queue_enqueue(&queue, &data);
if (status == QUEUE_FULL) {
    // Handle full queue error
}

status = queue_dequeue(&queue, &data);
if (status == QUEUE_EMPTY) {
    // Handle empty queue error
}
```

### Example with Struct Data Type
You can also use the queue with a struct data type. Here is an example:

```c
typedef struct {
    uint8_t id;
    uint16_t value;
    uint8_t padding; // Padding to align the struct size
} data_t;

queue_t queue;
data_t buffer[10];
queue_init(&queue, buffer, 10, sizeof(data_t));

data_t data = {1, 100, 0};
queue_enqueue(&queue, &data);

data_t dequeued_data;
queue_dequeue(&queue, &dequeued_data);
```

## Unit Tests

Unit tests for the queue module are written using GoogleTest. To run the tests, follow these steps:

1. Install GoogleTest.
2. Create a `test` directory and add the `test_queue.cpp` file with the test cases.
3. Update your `CMakeLists.txt` to include the test directory and link GoogleTest.
4. Build and run the tests using CMake.

```sh
cmake .
make
ctest
```
