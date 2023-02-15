#include <iostream>
using namespace std;

class Cars;
class Driver
{
public:
    friend int PriceChange(Cars *ptr);
};

class Cars
{
private:
    int price = 0;
    friend Driver;
    friend int PriceChange(Cars *ptr);
};

int PriceChange(Cars *ptr)
{
    ptr->price += 1000;
    int temp = ptr->price;
    return temp;
};

int main()
{
    Cars car;
    Driver driver;
    cout << PriceChange(&car) << endl;
    return 0;
}
