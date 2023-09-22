/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Aya Salama
 * Date        : 9/12/2023
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <iostream>

using namespace std;

class PrimesSieve
{
public:
    PrimesSieve(int limit);

    // destructor
    ~PrimesSieve()
    {
        delete[] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool *const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit}
{
    sieve();
}

void PrimesSieve::display_primes() const
{
    const int max_prime_width = num_digits(max_prime_),
              primes_per_row = 80 / (max_prime_width + 1);
    int primes_in_row = 0;
    if (limit_ <= 106)
    {
        for (int i = 2; i <= limit_; i++)
        {
            if (is_prime_[i])
            {
                if (primes_in_row == 0)
                {
                    cout << i;
                    primes_in_row++;
                }
                else
                {
                    cout << " " << i;
                }
            }
        }
    }
    else
    {
        for (int i = 2; i <= limit_; i++)
        {
            if (is_prime_[i])
            {
                if (primes_in_row == 0 && num_digits(i) == max_prime_width)
                {
                    cout << i;
                    primes_in_row = 1;
                }
                else if (primes_in_row == 0)
                {
                    cout << setw(max_prime_width - num_digits(i)) << right << " " << i;
                    primes_in_row = 1;
                }
                else if (primes_in_row <= primes_per_row)
                {
                    cout << setw(max_prime_width - num_digits(i) + 1) << right << " " << i;
                    primes_in_row++;
                    if (primes_in_row == primes_per_row)
                    {
                        cout << endl;
                        primes_in_row = 0;
                    }
                }
            }
        }
    }
}

void PrimesSieve::sieve()
{
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.
    for (int i = 2; i <= limit_; i++)
    {
        is_prime_[i] = true;
    }
    max_prime_ = 2;
    for (int i = 2; i <= sqrt(limit_); i++)
    {
        if (is_prime_[i])
        {
            for (int j = i * i; j <= limit_; j += i)
            {
                is_prime_[j] = false;
            }
        }
    }
    int num_primes = 0;
    for (int i = 2; i <= limit_; i++)
    {
        if (is_prime_[i])
        {
            num_primes++;
            if (i > max_prime_)
            {
                max_prime_ = i;
            }
        }
    }
    cout << "Number of primes found: " << num_primes << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
}

int PrimesSieve::num_digits(int num)
{
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    return to_string(num).length();
}

int main()
{
    cout << "**************************** "
         << "Sieve of Eratosthenes"
         << " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if (!(iss >> limit))
    {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2)
    {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    cout << endl;
    PrimesSieve user(limit);
    user.display_primes();
    return 0;
}