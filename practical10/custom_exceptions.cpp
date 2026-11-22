// Practical 10: Custom Exceptions - Banking Transaction
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

class InvalidAmount : public std::exception {
public:
    const char* what() const noexcept override {
        return "Transaction amount must be greater than zero.";
    }
};

class InsufficientFunds : public std::exception {
public:
    const char* what() const noexcept override {
        return "Transaction declined: insufficient funds.";
    }
};

class BankAccount {
public:
    explicit BankAccount(double balance) : balance_(balance) {}

    void withdraw(double amount) {
        if (amount <= 0) throw InvalidAmount();
        if (amount > balance_) throw InsufficientFunds();
        balance_ -= amount;
    }

    double balance() const { return balance_; }

private:
    double balance_;
};

void tryWithdrawal(BankAccount& account, double amount) {
    try {
        account.withdraw(amount);
        std::cout << "Withdrawal of Rs. " << amount << " successful.\n";
    } catch (const InvalidAmount& error) {
        std::cout << "Invalid amount: " << error.what() << '\n';
    } catch (const InsufficientFunds& error) {
        std::cout << "Insufficient funds: " << error.what() << '\n';
    }
    std::cout << "Current balance: Rs. " << account.balance() << "\n\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    BankAccount account(1000);
    tryWithdrawal(account, 250);
    tryWithdrawal(account, -10);
    tryWithdrawal(account, 900);
    tryWithdrawal(account, 500);
    return 0;
}
