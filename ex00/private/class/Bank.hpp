#ifndef BANK_HPP
#define BANK_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm> // for std::find_if
#include "Nullptr.hpp"

class Bank {
public:
    struct Account {
    private:
        int id;
        int value;

    public:
        Account(int accountId);
        int getId() const;
        int getValue() const;

        friend class Bank;

        friend std::ostream& operator<<(std::ostream& p_os, const Account& p_account);
	};

private:
    int liquidity;
    std::vector<Account*> clientAccounts;

    Account* findAccountById(int id) const;

public:
    Bank();
    ~Bank();

    int getLiquidity() const;

    void createAccount(int id);
    void deleteAccount(int id);
    void deposit(int id, int amount);
    void withdraw(int id, int amount);
    void grantLoan(int id, int amount);

    Account& operator[](int id);
    const Account& operator[](int id) const;

    friend std::ostream& operator<<(std::ostream& p_os, const Bank& p_bank);

	friend void testDepositFee();
	friend void testUniqueAccountIds();
	friend void testCreateDeleteModifyAccounts();
	friend void testGrantLoan();
	friend void testImpossibleDirectAddMoney();
};

#endif // BANK_HPP
