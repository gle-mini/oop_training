#include <iostream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <exception>
#include "class/Bank.hpp"

void testDepositFee() {
    Bank bank;
    bank.createAccount(0);
    int initialLiquidity = bank.getLiquidity();

    bank.deposit(0, 100);
    Bank::Account* account = bank.findAccountById(0);

    assert(account->getValue() == 95); // 5% fee should be deducted
    assert(bank.getLiquidity() == initialLiquidity + 5); // Bank should receive 5% fee
    std::cout << "Test deposit fee passed!" << std::endl;
}

void testUniqueAccountIds() {
    Bank bank;
    bank.createAccount(0);
    try {
        bank.createAccount(0); // Attempt to create an account with a duplicate ID
        assert(false); // This should not be reached
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Account ID already exists.");
        std::cout << "Test unique account IDs passed!" << std::endl;
    }
}

void testAttributesNotModifiableFromOutside() {
    Bank::Account account(1);
    int initialId = account.getId();
    int initialValue = account.getValue();

    // Try to modify attributes (should not be possible)
    // account.id = 2; // Should be a compilation error
    // account.value = 200; // Should be a compilation error

    assert(account.getId() == initialId);
    assert(account.getValue() == initialValue);
    std::cout << "Test attributes not modifiable from outside passed!" << std::endl;
}

void testCreateDeleteModifyAccounts() {
    Bank bank;
    bank.createAccount(0);
    bank.createAccount(1);

    Bank::Account* account0 = bank.findAccountById(0);
    Bank::Account* account1 = bank.findAccountById(1);

    assert(account0 != nullptr);
    assert(account1 != nullptr);

    bank.deleteAccount(0);
    account0 = bank.findAccountById(0);

    assert(account0 == nullptr);
    std::cout << "Test create, delete, and modify accounts passed!" << std::endl;
}

void testGrantLoan() {
    Bank bank;
    bank.createAccount(0);
    bank.createAccount(1);
    bank.deposit(0, 100);
    bank.deposit(1, 100);
    bank.liquidity = 500; // Set initial liquidity for the bank

    bank.grantLoan(0, 200);

    Bank::Account* account = bank.findAccountById(0);
    assert(account->getValue() == 295); // Initial 95 + 200 loan
    assert(bank.getLiquidity() == 300); // 500 - 200 loan

    try {
        bank.grantLoan(1, 400); // Attempt to grant loan exceeding bank liquidity
        assert(false); // This should not be reached
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Bank has insufficient funds.");
        std::cout << "Test grant loan passed!" << std::endl;
    }
}

void testImpossibleDirectAddMoney() {
    Bank bank;
    bank.createAccount(0);
    Bank::Account* account = bank.findAccountById(0);

    // Try to directly modify account value (should not be possible)
    // account->value += 100; // Should be a compilation error

    int initialValue = account->getValue();
    bank.deposit(0, 100);
    assert(account->getValue() == initialValue + 95); // Only deposit through bank allowed
    std::cout << "Test impossible direct add money passed!" << std::endl;
}

int main() {
    try {
        Bank bank;
        bank.createAccount(0);
        bank.createAccount(1);

        bank.deposit(0, 100);
        bank.deposit(1, 100);

        bank.grantLoan(0, 50);

        std::cout << "Account 0: " << std::endl;
        std::cout << bank[0] << std::endl;
        std::cout << "Account 1: " << std::endl;
        std::cout << bank[1] << std::endl;

        std::cout << " ----- " << std::endl;

        std::cout << "Bank: " << std::endl;
        std::cout << bank << std::endl;

        // Testing error handling
        try {
            bank.createAccount(0); // Should throw an error
        } catch (const std::runtime_error& e) {
            std::cout << "Caught error: " << e.what() << std::endl;
        }

        try {
            bank[2]; // Should throw an error
        } catch (const std::runtime_error& e) {
            std::cout << "Caught error: " << e.what() << std::endl;
        }

        try {
            bank.grantLoan(1, 5000); // Should throw an error due to insufficient funds
        } catch (const std::runtime_error& e) {
            std::cout << "Caught error: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    testDepositFee();
    testUniqueAccountIds();
    testAttributesNotModifiableFromOutside();
    testCreateDeleteModifyAccounts();
    testGrantLoan();
    testImpossibleDirectAddMoney();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
