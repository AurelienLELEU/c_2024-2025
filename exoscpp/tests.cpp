#include "password.hpp"
#include "user.hpp"
#include <cassert>
#include <iostream>

void test_password()
{
    Password password("test", false);
    assert(password.str() == "whvw");

    assert(password == "whvw");
    Password encrypted_password("whvw", true);
    assert(password == encrypted_password);

    std::cout << "Tests Password réussis." << std::endl;
}

void test_user()
{
    Password password("test", false);
    User user(1, password);
    user.save();

    User &retrieved_user = User::get(1);

    assert(retrieved_user.login("test") == 1);
    assert(retrieved_user.login("wrong") == 0);

    std::cout << "Tests User réussis." << std::endl;
}

int main()
{
    test_password();
    test_user();

    std::cout << "Tous les tests ont été passés avec succès !" << std::endl;
    return 0;
}
