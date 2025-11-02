#include <gtest.h>
#include <tqueue.h>

TEST(TStack, can_create_stack)
{
    ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, cant_create_too_large_stack)
{
    ASSERT_ANY_THROW(TStack<int> s(MAX_STACK_SIZE + 1));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, can_create_copied_stack)
{
    TStack<int> s(5);
    ASSERT_NO_THROW(TStack<int> s1(s));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
    TStack<int> s(5);
    s.Push(1);
    s.Push(2);
    TStack<int> s2(s);
    ASSERT_TRUE(s == s2);
}

TEST(TStack, copied_stack_has_its_own_memory)
{
    TStack<int> s(3);
    s.Push(1);
    s.Push(2);
    TStack<int> s2(s);

    s.Pop();
    int elem = s2.Pop();
    ASSERT_EQ(elem, 2);
}

TEST(TStack, can_assign_stack)
{
    TStack<int> s1(3);
    TStack<int> s2(2);
    ASSERT_NO_THROW(s1 = s2);
}

TEST(TStack, can_assign_stack_to_itself)
{
    TStack<int> s(3);
    ASSERT_NO_THROW(s = s);
}

TEST(TStack, assigned_stack_is_equal_to_source_one)
{
    TStack<int> s1(3);
    s1.Push(1);
    s1.Push(2);
    TStack<int> s2(1);
    s2 = s1;
    ASSERT_TRUE(s1 == s2);
}

TEST(TStack, can_push_element)
{
    TStack<int> s(3);
    ASSERT_NO_THROW(s.Push(1));
}

TEST(TStack, can_pop_element)
{
    TStack<int> s(3);
    s.Push(1);
    ASSERT_NO_THROW(s.Pop());
}

TEST(TStack, pop_returns_correct_element)
{
    TStack<int> s(3);
    s.Push(42);
    int elem = s.Pop();
    ASSERT_EQ(elem, 42);
}

TEST(TStack, push_increases_top)
{
    TStack<int> s(3);
    s.Push(1);
    s.Push(2);
    int elem = s.Pop();
    ASSERT_EQ(elem, 2);
}

TEST(TStack, pop_decreases_top)
{
    TStack<int> s(3);
    s.Push(1);
    s.Push(2);
    s.Pop();
    int elem = s.Pop();
    ASSERT_EQ(elem, 1);
}

TEST(TStack, throws_when_push_to_full_stack)
{
    TStack<int> s(1);
    s.Push(1);
    ASSERT_ANY_THROW(s.Push(2));
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
    TStack<int> s(1);
    ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, can_check_empty_stack)
{
    TStack<int> s(3);
    ASSERT_TRUE(s.IsEmpty());
}

TEST(TStack, can_check_full_stack)
{
    TStack<int> s(1);
    s.Push(1);
    ASSERT_TRUE(s.IsFull());
}

TEST(TStack, empty_stack_is_not_full)
{
    TStack<int> s(3);
    ASSERT_FALSE(s.IsFull());
}

TEST(TStack, full_stack_is_not_empty)
{
    TStack<int> s(1);
    s.Push(1);
    ASSERT_FALSE(s.IsEmpty());
}

TEST(TStack, can_get_length)
{
    TStack<int> s(5);
    ASSERT_EQ(s.GetLen(), 5);
}

TEST(TStack, can_resize_stack)
{
    TStack<int> s(3);
    ASSERT_NO_THROW(s.Resize(5));
}

TEST(TStack, resize_increases_capacity)
{
    TStack<int> s(2);
    s.Push(1);
    s.Push(2);
    s.Resize(4);
    ASSERT_NO_THROW(s.Push(3));
}

TEST(TStack, resize_preserves_data)
{
    TStack<int> s(3);
    s.Push(1);
    s.Push(2);
    s.Resize(5);

    int elem2 = s.Pop();
    ASSERT_EQ(elem2, 2);

    int elem1 = s.Pop();
    ASSERT_EQ(elem1, 1);
}

TEST(TStack, throws_when_resize_to_negative_length)
{
    TStack<int> s(3);
    ASSERT_ANY_THROW(s.Resize(-1));
}

TEST(TStack, can_set_data)
{
    int** data = new int* [2];
    data[0] = new int(10);
    data[1] = nullptr;

    TStack<int> s;
    ASSERT_NO_THROW(s.SetData(data, 2));
}

TEST(TStack, set_data_changes_stack_content)
{
    int** data = new int* [2];
    data[0] = new int(10);
    data[1] = nullptr;

    TStack<int> s;
    s.SetData(data, 2);

    int elem = s.Pop();
    ASSERT_EQ(elem, 10);
}

TEST(TStack, can_create_moved_stack)
{
    TStack<int> s(3);
    s.Push(1);
    ASSERT_NO_THROW(TStack<int> s2(std::move(s)));
}

TEST(TStack, moved_stack_has_correct_state)
{
    TStack<int> s1(3);
    s1.Push(42);
    TStack<int> s2(std::move(s1));

    int elem = s2.Pop();
    ASSERT_EQ(elem, 42);
}

TEST(TStack, original_stack_is_empty_after_move)
{
    TStack<int> s1(3);
    s1.Push(42);
    TStack<int> s2(std::move(s1));

    ASSERT_TRUE(s1.IsEmpty());
    ASSERT_EQ(s1.GetLen(), 0);
}

TEST(TStack, not_equal_stacks_are_different)
{
    TStack<int> s1(3);
    s1.Push(1);
    TStack<int> s2(3);
    s2.Push(2);

    ASSERT_TRUE(s1 != s2);
}

TEST(TStack, can_push_after_pop)
{
    TStack<int> s(2);
    s.Push(1);
    s.Push(2);
    s.Pop();
    ASSERT_NO_THROW(s.Push(3));
}

TEST(TStack, multiple_push_pop_operations)
{
    TStack<int> s(3);

    for (int i = 1; i <= 3; i++) {
        s.Push(i * 10);
    }

    for (int i = 3; i >= 1; i--) {
        int elem = s.Pop();
        ASSERT_EQ(elem, i * 10);
    }
}

TEST(TStack, stack_with_zero_length)
{
    TStack<int> s(0);
    ASSERT_TRUE(s.IsEmpty());
    ASSERT_TRUE(s.IsFull());
    ASSERT_ANY_THROW(s.Push(1));
    ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, assignment_operator_works_correctly)
{
    TStack<int> s1(3);
    s1.Push(1);
    s1.Push(2);

    TStack<int> s2(1);
    s2 = s1;

    ASSERT_EQ(s1.GetLen(), s2.GetLen());
    ASSERT_EQ(s1.IsEmpty(), s2.IsEmpty());

    int elem1 = s1.Pop();
    int elem2 = s2.Pop();
    ASSERT_EQ(elem1, elem2);
}

TEST(TStack, assignment_operator_creates_deep_copy)
{
    TStack<int> s1(2);
    s1.Push(10);
    s1.Push(20);

    TStack<int> s2(1);
    s2 = s1;

    s1.Pop();
    int elem = s2.Pop();
    ASSERT_EQ(elem, 20);
}

TEST(TStack, self_assignment_works_correctly)
{
    TStack<int> s(3);
    s.Push(1);
    s.Push(2);

    ASSERT_NO_THROW(s = s);

    ASSERT_FALSE(s.IsEmpty());
    int elem = s.Pop();
    ASSERT_EQ(elem, 2);
}

TEST(TStack, equal_operator_returns_true_for_equal_stacks)
{
    TStack<int> s1(3);
    s1.Push(1);
    s1.Push(2);

    TStack<int> s2(3);
    s2.Push(1);
    s2.Push(2);

    ASSERT_TRUE(s1 == s2);
}

TEST(TStack, equal_operator_returns_false_for_different_stacks)
{
    TStack<int> s1(3);
    s1.Push(1);
    s1.Push(2);

    TStack<int> s2(3);
    s2.Push(1);
    s2.Push(3);

    ASSERT_FALSE(s1 == s2);
}

TEST(TStack, equal_operator_returns_false_for_different_sizes)
{
    TStack<int> s1(3);
    s1.Push(1);

    TStack<int> s2(2);
    s2.Push(1);

    ASSERT_FALSE(s1 == s2);
}

TEST(TStack, equal_operator_returns_true_for_self_comparison)
{
    TStack<int> s(3);
    s.Push(1);
    s.Push(2);

    ASSERT_TRUE(s == s);
}

TEST(TStack, not_equal_operator_returns_true_for_different_stacks)
{
    TStack<int> s1(3);
    s1.Push(1);
    s1.Push(2);

    TStack<int> s2(3);
    s2.Push(1);
    s2.Push(3);

    ASSERT_TRUE(s1 != s2);
}

TEST(TStack, not_equal_operator_returns_false_for_equal_stacks)
{
    TStack<int> s1(3);
    s1.Push(1);
    s1.Push(2);

    TStack<int> s2(3);
    s2.Push(1);
    s2.Push(2);

    ASSERT_FALSE(s1 != s2);
}

TEST(TStack, assignment_preserves_stack_functionality)
{
    TStack<int> s1(3);
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    TStack<int> s2(1);
    s2 = s1;

    ASSERT_TRUE(s2.IsFull());

    int elem3 = s2.Pop();
    ASSERT_EQ(elem3, 3);

    int elem2 = s2.Pop();
    ASSERT_EQ(elem2, 2);

    int elem1 = s2.Pop();
    ASSERT_EQ(elem1, 1);

    ASSERT_TRUE(s2.IsEmpty());
}

TEST(TStack, assignment_with_different_initial_states)
{
    TStack<int> s1(3);
    s1.Push(10);
    s1.Push(20);

    TStack<int> s2;
    s2 = s1;

    ASSERT_TRUE(s1 == s2);
}

TEST(TStack, compare_stacks_with_nullptr_elements)
{
    TStack<int> s1(3);
    s1.Push(1);
    s1.Push(2);

    TStack<int> s2(3);
    s2.Push(1);
    s2.Push(2);

    ASSERT_TRUE(s1 == s2);
}

TEST(TStack, compare_stacks_with_different_nullptr_patterns)
{
    TStack<int> s1(3);
    s1.Push(1);

    TStack<int> s2(3);
    s2.Push(1);
    s2.Push(2);

    ASSERT_FALSE(s1 == s2);
}

TEST(TStack, assignment_to_full_stack)
{
    TStack<int> s1(2);
    s1.Push(10);
    s1.Push(20);

    TStack<int> s2(3);
    s2.Push(30);

    s2 = s1;

    ASSERT_TRUE(s2.IsFull());
    ASSERT_EQ(s2.GetLen(), 2);

    int elem = s2.Pop();
    ASSERT_EQ(elem, 20);
}

TEST(TStack, assignment_from_empty_stack)
{
    TStack<int> s1;
    TStack<int> s2(3);
    s2.Push(1);
    s2.Push(2);

    s2 = s1;

    ASSERT_TRUE(s2.IsEmpty());
    ASSERT_EQ(s2.GetLen(), 0);
}