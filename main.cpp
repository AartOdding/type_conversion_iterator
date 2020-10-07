


#include <iostream>

#include <reference_view.hpp>
#include <forward_list>



struct A_tag {};
struct B_tag : public A_tag {};
struct C_tag : public B_tag {};

struct A_part
{
    using AAA = int;

    void do_A() {}
};

template<typename Tag, typename Enable = void>
struct B_part : A_part
{
    // B_part does not have do_B() if tag has no B
};

template<typename Tag>
struct B_part<Tag, std::enable_if_t<std::is_base_of_v<B_tag, Tag>>> : A_part
{
    void do_B() {}
    AAA p;
};

template<typename Tag, typename Enable = void>
struct C_part : B_part<Tag>
{
    // C_part does not have do_C() if tag has no C
};

template<typename Tag>
struct C_part <Tag, std::enable_if_t<std::is_base_of_v<C_tag, Tag>>> : B_part<Tag>
{
    void do_C() {}
};

template<typename Tag>
struct parts : C_part<Tag>
{

};


int main()
{
    std::vector<int> ints{10, 20, 30};
    auto ptr = standard_iterator_adapter<std::vector<int>::iterator>::get_pointer(ints.begin());
    *ptr = 100;

    std::cout << ints.front() << std::endl;


    parts<A_tag> a; // only has do_A()
    parts<B_tag> b; // has do_A() and do_B()
    parts<C_tag> c; // has do_A(), do_B() and do_C()
    c.p;


    // nh.always();
    // h1.sometimes();
    // h2.sometimes();

    // std::forward_list<std::unique_ptr<const stuff>> stuffs;

    // stuffs.emplace_front(new stuff());
    // stuffs.emplace_front(new stuff());
    // stuffs.emplace_front(new stuff());
    // stuffs.emplace_front(new stuff());
    // stuffs.emplace_front(new stuff());

    // data_iterator<decltype(stuffs)> itb = stuffs.begin();
    // data_iterator<decltype(stuffs)> ite = stuffs.end();

    // std::cout << decltype(itb)::atleast_forward << std::endl;
    // std::cout << decltype(itb)::atleast_bidirectional << std::endl;
    // std::cout << decltype(itb)::atleast_random_access << std::endl;
    
    // for (auto it = itb; it != ite; ++it)
    // {
    //     std::cout << it->i << std::endl;
    // }

    // for (auto it = itb; it != ite; ++it)
    // {
    //     std::cout << it->i << std::endl;
    // }

    // stuff s{ 100, true };

    // auto sp = &s;
    // const stuff * csp = &s;

    // auto up = std::make_unique<stuff>();
    // const auto cup = std::make_unique<stuff>();
    // auto ucp = std::make_unique<const stuff>();

    // converter<stuff*, stuff&> cp1;
    // converter<stuff*, const stuff&> cp2;
    // converter<const stuff*, const stuff&> cp3;
    // converter<const stuff*, stuff&> cp4; // conversion not allowed

    // auto& bp1 = cp1(sp); // OMG
    // auto& bp2 = cp2(sp);
    // auto& bp3 = cp3(sp);
    //auto& bp4 = cp4(sp);

    // converter<stuff&, std::unique_ptr<stuff>> cu1;
    // converter<const stuff&, std::unique_ptr<stuff>> cu2;
    // converter<const stuff&, std::unique_ptr<const stuff>> cu3;
    //converter<stuff&, std::unique_ptr<const stuff>> cu4;

    // auto& bu1 = cu1(up);
    // auto& bu2 = cu2(up);
    // auto& bu3 = cu3(ucp);
    //auto& bu4 = cu4(&s);

    // converter<stuff&, std::unique_ptr<stuff>> cu1;


    // converter<stuff&, const std::unique_ptr<stuff>> cu2;
    // converter<stuff&, std::unique_ptr<const stuff>> cu3;
    // converter<stuff&, const std::unique_ptr<const stuff>> cu4;
    
    // auto& bu1 = cu1(up);
    // auto& bu2 = cu2(cup);
    // auto& bu3 = cu3(ucp);
    // auto& bu4 = cu4(ucp);


    //converter<const stuff&, const std::unique_ptr<stuff>> cu6;
    //converter<const stuff&, const std::unique_ptr<const stuff>> cu7;
    //converter<stuff&, const std::unique_ptr<const stuff>> cu8;

    // auto& bu5 = cu5(up);
    // auto& bu6 = cu6(up);
    // auto& bu7 = cu7(up);
    // auto& bu8 = cu8(up);

    // std::cout << "hello world " <<  bp1.i << std::endl;

};
