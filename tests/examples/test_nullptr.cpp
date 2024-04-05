struct A
{
    void foo(){};
    int a = 0;
};

// ESCA +: finds both for a_ptr, no false positive for b_ptr
void nullptr_infunc()
{
    A *a_ptr = nullptr;
    A *btr;
    a_ptr->foo();
    a_ptr->a;
}

// ESCA +: no false positives
void good_infunc()
{
    A *agood_ptr = new A();
    agood_ptr->foo();
    agood_ptr->a = 42;
    delete agood_ptr;
}

// ESCA -: does not detect
void nullptr_from_arg(A *arg_ptr)
{
    arg_ptr->foo();
    arg_ptr->a = 43;
    arg_ptr->a;
}

// ESCA +: finds first, no false positive for second
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
    lateinit();
    nullptr_from_arg(nullptr);
    return 0;
}
