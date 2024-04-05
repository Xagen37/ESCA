struct A
{
    void foo();
    int a = 0;
};

void nullptr_infunc()
{
    A *a_ptr = nullptr;
    A *btr;
    a_ptr->foo();
    a_ptr->a = 42;
    a_ptr->a;
}

void nullptr_from_arg(A *arg_ptr)
{
    arg_ptr->foo();
    arg_ptr->a = 43;
    arg_ptr->a;
}

int main()
{
    nullptr_infunc();
    nullptr_from_arg(nullptr);
    return 0;
}
