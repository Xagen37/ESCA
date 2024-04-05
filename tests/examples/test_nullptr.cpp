struct A
{
    void foo(){};
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

void good_infunc()
{
    A *agood_ptr = new A();
    agood_ptr->foo();
    agood_ptr->a = 42;
    delete agood_ptr;
}

void nullptr_from_arg(A *arg_ptr)
{
    arg_ptr->foo();
    arg_ptr->a = 43;
    arg_ptr->a;
}

void lateinit()
{
    A *late_ptr = nullptr;
    late_ptr->foo();
    late_ptr = new A();
    late_ptr->foo();
    delete late_ptr;
}

int main()
{
    nullptr_infunc();
    good_infunc();
    nullptr_from_arg(nullptr);
    return 0;
}
