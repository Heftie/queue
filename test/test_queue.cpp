#include "queue.h"
#include "gtest/gtest.h"

struct TestStruct {
    uint8_t a;
    uint16_t b;
    uint32_t c;
};

// Test that the queue can be initialized
TEST(QueueTest, Initialization) {
    queue_t queue;
    uint8_t buffer[10];
    EXPECT_EQ(queue_init(&queue, buffer, 10, sizeof(uint8_t)), QUEUE_OK);
}

// Test that the queue can enqueue and dequeue an item
TEST(QueueTest, Enqueue) {
    queue_t queue;
    uint8_t buffer[10];
    queue_init(&queue, buffer, 10, sizeof(uint8_t));
    uint8_t data = 1;
    EXPECT_EQ(queue_enqueue(&queue, &data), QUEUE_OK);
    EXPECT_EQ(((uint8_t*)queue.buffer)[0], 1);
}

// Test that the queue dequeues the correct item
TEST(QueueTest, Dequeue) {
    queue_t queue;
    uint8_t buffer[10];
    queue_init(&queue, buffer, 10, sizeof(uint8_t));
    uint8_t data = 1;
    queue_enqueue(&queue, &data);
    uint8_t item = 0;
    EXPECT_EQ(queue_dequeue(&queue, &item), QUEUE_OK);
    EXPECT_EQ(item, 1);
}

// Test that the queue returns an error when enqueuing to a full queue
TEST(QueueTest, Full) {
    queue_t queue;
    uint8_t buffer[10];
    queue_init(&queue, buffer, 10, sizeof(uint8_t));
    uint8_t data = 0;
    for (int i = 0; i < 10; i++) {
        data = i;
        EXPECT_EQ(queue_enqueue(&queue, &data), QUEUE_OK);
    }
    data = 10;
    EXPECT_EQ(queue_enqueue(&queue, &data), QUEUE_FULL);
}

// Test that the queue returns an error when dequeuing from an empty queue
TEST(QueueTest, Empty) {
    queue_t queue;
    uint8_t buffer[10];
    queue_init(&queue, buffer, 10, sizeof(uint8_t));
    uint8_t item = 0;
    EXPECT_EQ(queue_dequeue(&queue, &item), QUEUE_EMPTY);
}

// Test that the queue returns an error when null pointers are passed
TEST(QueueTest, Null) {
    uint8_t buffer[10];
    EXPECT_EQ(queue_init(NULL, buffer, 10, sizeof(uint8_t)), QUEUE_ERROR);
    queue_t queue;
    EXPECT_EQ(queue_init(&queue, NULL, 10, sizeof(uint8_t)), QUEUE_ERROR);
    EXPECT_EQ(queue_init(&queue, buffer, 0, sizeof(uint8_t)), QUEUE_ERROR);
    EXPECT_EQ(queue_init(&queue, buffer, 10, sizeof(uint8_t)), QUEUE_OK);
    uint8_t data = 1;
    EXPECT_EQ(queue_enqueue(NULL, &data), QUEUE_ERROR);
    EXPECT_EQ(queue_enqueue(&queue, &data), QUEUE_OK);
    uint8_t item = 0;
    EXPECT_EQ(queue_dequeue(NULL, &item), QUEUE_ERROR);
    EXPECT_EQ(queue_dequeue(&queue, &item), QUEUE_OK);
}

// Test that the queue wraps around when full
TEST(QueueTest, WrapAround) {
    queue_t queue;
    uint8_t buffer[3];
    queue_init(&queue, buffer, 3, sizeof(uint8_t));
    uint8_t data = 1;
    queue_enqueue(&queue, &data);
    data = 2;
    queue_enqueue(&queue, &data);
    data = 3;
    queue_enqueue(&queue, &data);
    uint8_t item = 0;
    queue_dequeue(&queue, &item);
    EXPECT_EQ(item, 1);
    data = 4;
    queue_enqueue(&queue, &data);
    queue_dequeue(&queue, &item);
    EXPECT_EQ(item, 2);
    queue_dequeue(&queue, &item);
    EXPECT_EQ(item, 3);
    queue_dequeue(&queue, &item);
    EXPECT_EQ(item, 4);
}

// Test that the queue is full after wrap around
TEST(QueueTest, FullWrapAround) {
    queue_t queue;
    uint8_t buffer[3];
    queue_init(&queue, buffer, 3, sizeof(uint8_t));
    uint8_t data = 1;
    queue_enqueue(&queue, &data);
    data = 2;
    queue_enqueue(&queue, &data);
    data = 3;
    queue_enqueue(&queue, &data);
    uint8_t item = 0;
    queue_dequeue(&queue, &item);
    EXPECT_EQ(item, 1);
    data = 4;
    queue_enqueue(&queue, &data);
    data = 5;
    queue_enqueue(&queue, &data);
    data = 6;
    EXPECT_EQ(queue_enqueue(&queue, &data), QUEUE_FULL);
}

// Test that the queue is empty after wrap around
TEST(QueueTest, EmptyWrapAround) {
    queue_t queue;
    uint8_t buffer[3];
    queue_init(&queue, buffer, 3, sizeof(uint8_t));
    uint8_t item = 0;
    EXPECT_EQ(queue_dequeue(&queue, &item), QUEUE_EMPTY);
    uint8_t data = 1;
    queue_enqueue(&queue, &data);
    data = 2;
    queue_enqueue(&queue, &data);
    data = 3;
    queue_enqueue(&queue, &data);
    queue_dequeue(&queue, &item);
    queue_dequeue(&queue, &item);
    queue_dequeue(&queue, &item);
    EXPECT_EQ(queue_dequeue(&queue, &item), QUEUE_EMPTY);
}

// Test struct data storage
TEST(QueueTest, StructStorage) {
    uint8_t buffer[16];
    TestStruct test_struct;
    queue_t queue;
    EXPECT_EQ(queue_init(&queue, buffer, 16, sizeof(test_struct)), QUEUE_OK);
    test_struct.a = 1;
    test_struct.b = 2;
    test_struct.c = 3;
    EXPECT_EQ(queue_enqueue(&queue, &test_struct), QUEUE_OK);
    test_struct.a = 0;
    test_struct.b = 0;
    test_struct.c = 0;
    EXPECT_EQ(queue_dequeue(&queue, &test_struct), QUEUE_OK);
    EXPECT_EQ(test_struct.a, 1);
    EXPECT_EQ(test_struct.b, 2);
    EXPECT_EQ(test_struct.c, 3);
}

// Test if multiple structs can be stored in the queue
TEST(QueueTest, MultipleStructs) {
    queue_t queue;
    struct {
        uint8_t a;
        uint16_t b;
        uint32_t c;
    } test_struct;
    uint8_t buffer[16];
    EXPECT_EQ(queue_init(&queue, buffer, 16, sizeof(test_struct)), QUEUE_OK);
    test_struct.a = 1;
    test_struct.b = 2;
    test_struct.c = 3;
    EXPECT_EQ(queue_enqueue(&queue, &test_struct), QUEUE_OK);
    test_struct.a = 4;
    test_struct.b = 5;
    test_struct.c = 6;
    EXPECT_EQ(queue_enqueue(&queue, &test_struct), QUEUE_OK);
    test_struct.a = 0;
    test_struct.b = 0;
    test_struct.c = 0;
    EXPECT_EQ(queue_dequeue(&queue, &test_struct), QUEUE_OK);
    EXPECT_EQ(test_struct.a, 1);
    EXPECT_EQ(test_struct.b, 2);
    EXPECT_EQ(test_struct.c, 3);
    EXPECT_EQ(queue_dequeue(&queue, &test_struct), QUEUE_OK);
    EXPECT_EQ(test_struct.a, 4);
    EXPECT_EQ(test_struct.b, 5);
    EXPECT_EQ(test_struct.c, 6);
}

// Test if the size fits the data type to be stored
TEST(QueueTest, Size) {
    queue_t queue;
    uint8_t buffer[16];
    uint8_t data = 1;
    EXPECT_EQ(queue_init(&queue, buffer, 16, sizeof(uint8_t)), QUEUE_OK);
    EXPECT_EQ(queue_init(&queue, buffer, 16, sizeof(uint16_t)), QUEUE_OK);
    EXPECT_EQ(queue_init(&queue, buffer, 16, sizeof(uint32_t)), QUEUE_OK);
    uint16_t buffer16[15];
    EXPECT_EQ(queue_init(&queue, buffer, 15, sizeof(uint8_t)), QUEUE_OK);
    EXPECT_EQ(queue_init(&queue, buffer16, 15, sizeof(uint16_t)), QUEUE_BUFFER_ERROR);
    EXPECT_EQ(queue_init(&queue, buffer, 15, sizeof(uint32_t)), QUEUE_BUFFER_ERROR);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}