#include <gtest.h>
#include <tqueue.h>

TEST(TQueue, can_create_queue)
{
    ASSERT_NO_THROW(TQueue<int> q);
}

TEST(TQueue, can_create_queue_with_positive_length)
{
    ASSERT_NO_THROW(TQueue<int> q(5));
}

TEST(TQueue, cant_create_too_large_queue)
{
    ASSERT_ANY_THROW(TQueue<int> q(MAX_QUEUE_SIZE + 1));
}

TEST(TQueue, throws_when_create_queue_with_negative_length)
{
    ASSERT_ANY_THROW(TQueue<int> q(-5));
}

TEST(TQueue, can_create_copied_queue)
{
    TQueue<int> q(5);
    ASSERT_NO_THROW(TQueue<int> q1(q));
}

TEST(TQueue, copied_queue_is_equal_to_source_one)
{
    TQueue<int> q(5);
    q.AddToTail(1);
    q.AddToTail(2);
    TQueue<int> q2(q);
    ASSERT_TRUE(q == q2);
}

TEST(TQueue, copied_queue_has_its_own_memory)
{
    TQueue<int> q(3);
    q.AddToTail(1);
    q.AddToTail(2);
    TQueue<int> q2(q);

    q.RemoveFromHead();
    int* elem = q2.RemoveFromHead();
    ASSERT_EQ(*elem, 1);
    delete elem;
}

TEST(TQueue, can_assign_queue)
{
    TQueue<int> q1(3);
    TQueue<int> q2(2);
    ASSERT_NO_THROW(q1 = q2);
}

TEST(TQueue, can_assign_queue_to_itself)
{
    TQueue<int> q(3);
    ASSERT_NO_THROW(q = q);
}

TEST(TQueue, assigned_queue_is_equal_to_source_one)
{
    TQueue<int> q1(3);
    q1.AddToTail(1);
    q1.AddToTail(2);
    TQueue<int> q2(1);
    q2 = q1;
    ASSERT_TRUE(q1 == q2);
}

TEST(TQueue, can_add_to_tail)
{
    TQueue<int> q(3);
    ASSERT_NO_THROW(q.AddToTail(1));
}

TEST(TQueue, can_remove_from_head)
{
    TQueue<int> q(3);
    q.AddToTail(1);
    ASSERT_NO_THROW(q.RemoveFromHead());
}

TEST(TQueue, add_to_tail_increases_count)
{
    TQueue<int> q(3);
    q.AddToTail(1);
    q.AddToTail(2);
    ASSERT_FALSE(q.IsEmpty());
    ASSERT_EQ(*q.RemoveFromHead(), 1);
    delete q.RemoveFromHead();
}

TEST(TQueue, remove_from_head_decreases_count)
{
    TQueue<int> q(3);
    q.AddToTail(1);
    q.AddToTail(2);
    delete q.RemoveFromHead();
    ASSERT_FALSE(q.IsEmpty());
    delete q.RemoveFromHead();
    ASSERT_TRUE(q.IsEmpty());
}

TEST(TQueue, throws_when_add_to_full_queue)
{
    TQueue<int> q(1);
    q.AddToTail(1);
    ASSERT_ANY_THROW(q.AddToTail(2));
}

TEST(TQueue, throws_when_remove_from_empty_queue)
{
    TQueue<int> q(1);
    ASSERT_ANY_THROW(q.RemoveFromHead());
}

TEST(TQueue, can_check_empty_queue)
{
    TQueue<int> q(3);
    ASSERT_TRUE(q.IsEmpty());
}

TEST(TQueue, can_check_full_queue)
{
    TQueue<int> q(1);
    q.AddToTail(1);
    ASSERT_TRUE(q.IsFull());
}

TEST(TQueue, empty_queue_is_not_full)
{
    TQueue<int> q(3);
    ASSERT_FALSE(q.IsFull());
}

TEST(TQueue, full_queue_is_not_empty)
{
    TQueue<int> q(1);
    q.AddToTail(1);
    ASSERT_FALSE(q.IsEmpty());
}

TEST(TQueue, can_get_length)
{
    TQueue<int> q(5);
    ASSERT_EQ(q.GetLen(), 5);
}

TEST(TQueue, can_resize_queue)
{
    TQueue<int> q(3);
    ASSERT_NO_THROW(q.Resize(5));
}

TEST(TQueue, resize_increases_capacity)
{
    TQueue<int> q(2);
    q.AddToTail(1);
    q.AddToTail(2);
    q.Resize(4);
    ASSERT_NO_THROW(q.AddToTail(3));
}

TEST(TQueue, resize_preserves_data_order)
{
    TQueue<int> q(3);
    q.AddToTail(1);
    q.AddToTail(2);
    q.Resize(5);

    int* elem1 = q.RemoveFromHead();
    ASSERT_EQ(*elem1, 1);
    delete elem1;

    int* elem2 = q.RemoveFromHead();
    ASSERT_EQ(*elem2, 2);
    delete elem2;
}

TEST(TQueue, throws_when_resize_to_negative_length)
{
    TQueue<int> q(3);
    ASSERT_ANY_THROW(q.Resize(-1));
}

TEST(TQueue, circular_buffer_works_correctly)
{
    TQueue<int> q(3);
    q.AddToTail(1);
    q.AddToTail(2);
    q.AddToTail(3);

    delete q.RemoveFromHead();
    q.AddToTail(4);
    int* elem2 = q.RemoveFromHead();
    ASSERT_EQ(*elem2, 2);
    delete elem2;

    int* elem3 = q.RemoveFromHead();
    ASSERT_EQ(*elem3, 3);
    delete elem3;

    int* elem4 = q.RemoveFromHead();
    ASSERT_EQ(*elem4, 4);
    delete elem4;
}

TEST(TQueue, fifo_order_with_add_to_tail)
{
    TQueue<int> q(3);
    q.AddToTail(1);
    q.AddToTail(2);
    q.AddToTail(3);

    int* elem1 = q.RemoveFromHead();
    ASSERT_EQ(*elem1, 1);
    delete elem1;

    int* elem2 = q.RemoveFromHead();
    ASSERT_EQ(*elem2, 2);
    delete elem2;

    int* elem3 = q.RemoveFromHead();
    ASSERT_EQ(*elem3, 3);
    delete elem3;
}

TEST(TQueue, not_equal_operator_works)
{
    TQueue<int> q1(3);
    q1.AddToTail(1);

    TQueue<int> q2(3);
    q2.AddToTail(2);

    ASSERT_TRUE(q1 != q2);
}

TEST(TQueue, queue_with_zero_length)
{
    TQueue<int> q(0);
    ASSERT_TRUE(q.IsEmpty());
    ASSERT_TRUE(q.IsFull());
    ASSERT_ANY_THROW(q.AddToTail(1));
    ASSERT_ANY_THROW(q.RemoveFromHead());
}

TEST(TQueue, multiple_add_remove_operations)
{
    TQueue<int> q(5);

    for (int i = 0; i < 5; i++) {
        q.AddToTail(i);
    }

    for (int i = 0; i < 5; i++) {
        int* elem = q.RemoveFromHead();
        ASSERT_EQ(*elem, i);
        delete elem;
    }

    ASSERT_TRUE(q.IsEmpty());
}