#include <tci/views.hpp>

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>





int main()
{
    std::vector<std::shared_ptr<std::string>> myvec;
    myvec.emplace_back(std::make_shared<std::string>("one"));
    myvec.emplace_back(std::make_shared<std::string>("two"));
    myvec.emplace_back(std::make_shared<std::string>("three"));
    myvec.emplace_back(std::make_shared<std::string>("four"));
    myvec.emplace_back(std::make_shared<std::string>("five"));

    tci::view<decltype(myvec)> vecview{ myvec };

    for (auto ptr : vecview)
    {
        ptr->append(" woop");
    }
    for (auto ptr : vecview)
    {
        std::cout << *ptr << std::endl;
    }

    std::map<std::string, std::unique_ptr<std::string>> mymap;
    mymap.emplace("1", std::make_unique<std::string>("one"));
    mymap.emplace("2", std::make_unique<std::string>("two"));
    mymap.emplace("3", std::make_unique<std::string>("three"));
    mymap.emplace("4", std::make_unique<std::string>("four"));
    mymap.emplace("5", std::make_unique<std::string>("five"));

    //using Conv = tci::get_pointer_to_second<std::string, std::unique_ptr<std::string>>;

    //Conv::convert()

    //decltype(mymap)::key_type
    tci::values_view<decltype(mymap)> m_view{ mymap };

    for (auto ptr : m_view)
    {
        ptr->append("yeet");
    }

    tci::const_values_view<std::map<std::string, std::unique_ptr<std::string>>> m_view2{ mymap };

    for (auto ptr : m_view2)
    {
        std::cout << *ptr << std::endl;
    }

    std::cout << "ghello" << std::endl;

}
