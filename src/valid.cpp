// #include "utils.h"
#include "valid.h"
#include <string>
using namespace std;

bool isValidISBN(string isbn)
{
    string isbn_no_dashes;

    for (char c : isbn)
    {
        if (c != '-')
            isbn_no_dashes += c;
    }

    if (isbn_no_dashes.size() != 13)
        return false;

    int sum = 0;
    for (int i = 0; i < 12; ++i)
    {
        if (!isdigit(isbn_no_dashes[i]))
            return false;

        sum += (isbn_no_dashes[i] - '0') * ((i % 2 == 0) ? 1 : 3);
    }

    int check_digit = (10 - (sum % 10)) % 10;
    return (isbn_no_dashes[12] - '0') == check_digit;
}

bool isValidId(string id)
{
    try
    {
        int value = stoi(id);
        if (value >= 1 && value <= 20)
        {
            return true;
        }
        return false;
    }
    catch (...)
    {
        return false;
    }
}
