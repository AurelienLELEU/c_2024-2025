#include "password.hpp"
#include "user.hpp"

int main()
{
    Password password("test", false);
    User user(1, password);

    user.save();

    User &retrieved_user = User::get(1);

    retrieved_user.login("test");

    return 0;
}
