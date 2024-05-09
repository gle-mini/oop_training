#include "class/Bank.hpp"

Bank::Account::Account(int accountId) : id(accountId), value(0) {}

int Bank::Account::getId() const {
    return id;
}

int Bank::Account::getValue() const {
    return value;
}

std::ostream& operator<<(std::ostream& p_os, const Bank::Account& p_account) {
    p_os << "[" << p_account.id << "] - [" << p_account.value << "]";
    return p_os;
}

Bank::Bank() : liquidity(0) {}

Bank::~Bank() {
    for (std::vector<Account*>::iterator it = clientAccounts.begin(); it != clientAccounts.end(); ++it) {
        delete *it;
    }
}

int Bank::getLiquidity() const {
    return liquidity;
}

Bank::Account* Bank::findAccountById(int id) const {
    for (std::vector<Account*>::const_iterator it = clientAccounts.begin(); it != clientAccounts.end(); ++it) {
        if ((*it)->getId() == id) {
            return *it;
        }
    }
    return nullptr;
}

void Bank::createAccount(int id) {
    if (findAccountById(id) != nullptr) {
        throw std::runtime_error("Account ID already exists.");
    }
    Account* newAccount = new Account(id);
    clientAccounts.push_back(newAccount);
}

void Bank::deleteAccount(int id) {
    for (std::vector<Account*>::iterator it = clientAccounts.begin(); it != clientAccounts.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            clientAccounts.erase(it);
            return;
        }
    }
    throw std::runtime_error("Account not found.");
}

void Bank::deposit(int id, int amount) {
    Account* account = findAccountById(id);
    if (!account) {
        throw std::runtime_error("Account not found.");
    }
    int fee = amount * 0.05;
    liquidity += fee;
    account->value += (amount - fee);
}

void Bank::withdraw(int id, int amount) {
    Account* account = findAccountById(id);
    if (!account) {
        throw std::runtime_error("Account not found.");
    }
    if (account->value < amount) {
        throw std::runtime_error("Insufficient funds.");
    }
    account->value -= amount;
}

void Bank::grantLoan(int id, int amount) {
    if (liquidity < amount) {
        throw std::runtime_error("Bank has insufficient funds.");
    }
    Account* account = findAccountById(id);
    if (!account) {
        throw std::runtime_error("Account not found.");
    }
    account->value += amount;
    liquidity -= amount;
}

Bank::Account& Bank::operator[](int id) {
    Account* account = findAccountById(id);
    if (!account) {
        throw std::runtime_error("Account not found.");
    }
    return *account;
}

const Bank::Account& Bank::operator[](int id) const {
    Account* account = findAccountById(id);
    if (!account) {
        throw std::runtime_error("Account not found.");
    }
    return *account;
}

std::ostream& operator<<(std::ostream& p_os, const Bank& p_bank) {
    p_os << "Bank information: " << std::endl;
    p_os << "Liquidity: " << p_bank.liquidity << std::endl;
    for (std::vector<Bank::Account*>::const_iterator it = p_bank.clientAccounts.begin(); it != p_bank.clientAccounts.end(); ++it) {
        p_os << **it << std::endl;
    }
    return p_os;
}
