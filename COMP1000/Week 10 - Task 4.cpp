#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class Account {
    protected:
        static inline int accountCounter = 0;

        int m_accountNumber;
        float m_balance = 0;

    public:
        Account() {
            m_accountNumber = accountCounter;
            accountCounter++;
        };

        int getAccountNumber() {
            return m_accountNumber;
        }

        float getBalance() {
            return m_balance;
        }

        void deposit(float bal) {
            m_balance += bal;
        }

        virtual void displayInfo() {
            std::cout << "Account ID: " << m_accountNumber
                << ", Balance: £" << std::fixed << std::setprecision(2) << m_balance << std::endl;
        }
};

class SavingsAccount : public Account {
    protected:
        float m_interestRate = 0;
        int m_compoundFreq = 12;

    public:
        SavingsAccount(): Account() {}
        SavingsAccount(float interestRate): Account(), m_interestRate(interestRate) {}
        SavingsAccount(float interestRate, int compoundFreq): Account(), m_interestRate(interestRate), m_compoundFreq(compoundFreq) {}

        void updateInterestRate(float interestRate, int compoundFreq) {
            m_interestRate = interestRate;
            m_compoundFreq = compoundFreq;
        }

        void updateInterestRate(float interestRate) {
            m_interestRate = interestRate;
        }

        float calculateInterest(int years) {
            float rn = m_interestRate / m_compoundFreq;
            float nt = m_compoundFreq * years;
            return m_balance * std::pow((1 + rn), nt);
        }

        void compoundInterest(int years) {
            m_balance = calculateInterest(years);
        }

        virtual void displayInfo() {
            std::cout << "Account ID: " << m_accountNumber
                << ", Balance: £" << std::fixed << std::setprecision(2) << m_balance
                << ", Interest Rate: " << m_interestRate * 100 << "% (" << m_compoundFreq << " times per year)" << std::endl;
        }
};

class Customer {
    protected:
        static inline int userIdCounter = 0;

        int m_userId;
        std::vector<Account*> m_accounts;
        std::string m_name;

    public:

        Customer(std::string name): m_name(name) {
            m_userId = userIdCounter;
            userIdCounter++;
        }

        Account* getAccountByNumber(int accountNumber) {
            // was originally named 'lamb' for lambda, but I think
            // ham is also a fine meat. hi jett :3
            auto ham = [&accountNumber](Account* obj) {
                return obj->getAccountNumber() == accountNumber;
            };

            auto it = std::find_if(m_accounts.begin(), m_accounts.end(), ham);
            if (it != m_accounts.end())
                return *it;
            
            return nullptr;
        }

        void registerAccount(Account* account) {
            auto it = std::find(m_accounts.begin(), m_accounts.end(), account);
            
            if (it != m_accounts.end()) {
                std::cerr << "That account is already registered with this user" << std::endl;
                return;
            }
            
            m_accounts.push_back(account);
            std::cout << "Registered account " << account->getAccountNumber() << " to user" << std::endl;
        }

        void displayInfo() {
            std::cout << "Customer: " << m_name << " (ID: " << m_userId << ")" << std::endl
                << "Accounts (" << m_accounts.size() << "): " << std::endl;

            if (m_accounts.size() > 0) {
                for (auto &c : m_accounts) {
                    std::cout << '\t';
                    c->displayInfo();
                }
            } else {
                std::cout << "\tNo Accounts Available :(" << std::endl;
            }

        }
};

int main() {
    SavingsAccount* sa = new SavingsAccount(0.07, 12);
    sa->deposit(12000);

    Account* ra = new Account();
    ra->deposit(650);

    Customer c("Emily");
    c.displayInfo();
    c.registerAccount(sa);
    c.registerAccount(ra);
    c.displayInfo();

    float newVal = sa->calculateInterest(1);
    std::cout << "After 1 year, account " << sa->getAccountNumber()
        << " will gain £" << (newVal - sa->getBalance()) << " in interest" << std::endl;
    sa->compoundInterest(1); // Add 1 years worth of compounding interest
    sa->displayInfo();

    // Good to delete them when done
    delete sa;
    delete ra;

    return 0;
}