#include "user.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

User::User(int id, Password &password) : id(id), password(&password)
{
    is_logged_in = false;
};

void User::save()
{
    std::ofstream file("users.txt", std::ios::app);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open users.txt for writing");
    }

    file << id << " | " << password->str() << "\n";
    file.close();
}

int User::login(const char *raw_password)
{
    std::ifstream file("users.txt");
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open users.txt for reading");
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream stream(line);
        int file_id;
        std::string encrypted_password;
        char delim;

        stream >> file_id >> delim >> encrypted_password;
        if (file_id == id)
        {
            std::cout << "Matching user ID found. Checking password...\n";
            Password stored_password(encrypted_password, true);
            Password input_password(raw_password, false);
            if (stored_password == input_password.str())
            {
                std::cout << "Password is correct. Login successful.\n";
                is_logged_in = true;
                return 1;
            }
        }
    }

    file.close();
    return 0;
}

User &User::get(int id)
{
    std::ifstream file("users.txt");
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open users.txt for reading");
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream stream(line);
        int file_id;
        std::string encrypted_password;
        char delim;

        stream >> file_id >> delim >> encrypted_password;
        if (file_id == id)
        {
            Password *password = new Password(encrypted_password, true);
            file.close();
            return *new User(file_id, *password);
        }
    }

    file.close();
    throw std::runtime_error("User not found");
}
