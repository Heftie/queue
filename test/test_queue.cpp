#include "queue.h"
#include "gtest/gtest.h"


TEST(QueueTest, Initialization) {
    queue_t queue;
    uint8_t buffer[10];
    EXPECT_EQ(queue_init(&queue, buffer, 10), QUEUE_OK);
}

TEST(QueueTest, Enqueue) {
    queue_t queue;
    uint8_t buffer[10];
    queue_init(&queue, buffer, 10);
    EXPECT_EQ(queue_enqueue(&queue, 1), QUEUE_OK);
    EXPECT_EQ(queue.buffer[0], 1);
}

TEST(QueueTest, Dequeue) {
    queue_t queue;
    uint8_t buffer[10];
    queue_init(&queue, buffer, 10);
    queue_enqueue(&queue, 1);
    uint8_t item = 0;
    EXPECT_EQ(queue_dequeue(&queue, &item), QUEUE_OK);
    EXPECT_EQ(item, 1);
}

TEST(QueueTest, Full) {
    queue_t queue;
    uint8_t buffer[10];
    queue_init(&queue, buffer, 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(queue_enqueue(&queue, i), QUEUE_OK);
    }
    EXPECT_EQ(queue_enqueue(&queue, 10), QUEUE_FULL);
}

TEST(QueueTest, Empty) {
    queue_t queue;
    uint8_t buffer[10];
    queue_init(&queue, buffer, 10);
    uint8_t item = 0;
    EXPECT_EQ(queue_dequeue(&queue, &item), QUEUE_EMPTY);
}

TEST(QueueTest, Null) {
    uint8_t buffer[10];
    EXPECT_EQ(queue_init(NULL, buffer, 10), QUEUE_ERROR);
    queue_t queue;
    EXPECT_EQ(queue_init(&queue, NULL, 10), QUEUE_ERROR);
    EXPECT_EQ(queue_init(&queue, buffer, 0), QUEUE_ERROR);
    EXPECT_EQ(queue_init(&queue, buffer, 10), QUEUE_OK);
    EXPECT_EQ(queue_enqueue(NULL, 1), QUEUE_ERROR);
    EXPECT_EQ(queue_enqueue(&queue, 1), QUEUE_OK);
    uint8_t item = 0;
    EXPECT_EQ(queue_dequeue(NULL, &item), QUEUE_ERROR);
    EXPECT_EQ(queue_dequeue(&queue, &item), QUEUE_OK);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}