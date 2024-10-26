#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int accountNumber;
    char name[50];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Function declarations
void createAccount();
void deposit(int accountNumber);
void withdraw(int accountNumber);
void displayBalance(int accountNumber);
void showAccounts();

int main() {
    int choice;

    while (1) {
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Display Balance\n");
        printf("5. Show All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2: {
                int accountNumber;
                printf("Enter Account Number: ");
                scanf("%d", &accountNumber);
                deposit(accountNumber);
                break;
            }
            case 3: {
                int accountNumber;
                printf("Enter Account Number: ");
                scanf("%d", &accountNumber);
                withdraw(accountNumber);
                break;
            }
            case 4: {
                int accountNumber;
                printf("Enter Account Number: ");
                scanf("%d", &accountNumber);
                displayBalance(accountNumber);
                break;
            }
            case 5:
                showAccounts();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot create more accounts.\n");
        return;
    }

    Account newAccount;
    newAccount.accountNumber = accountCount + 1; // Simple account number increment
    printf("Enter Name: ");
    scanf("%s", newAccount.name);
    newAccount.balance = 0.0;

    accounts[accountCount] = newAccount;
    accountCount++;
    printf("Account created successfully! Your account number is %d.\n", newAccount.accountNumber);
}

void deposit(int accountNumber) {
    if (accountNumber <= 0 || accountNumber > accountCount) {
        printf("Account not found!\n");
        return;
    }

    float amount;
    printf("Enter deposit amount: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    accounts[accountNumber - 1].balance += amount;
    printf("Deposited %.2f successfully! New balance is %.2f.\n", amount, accounts[accountNumber - 1].balance);
}

void withdraw(int accountNumber) {
    if (accountNumber <= 0 || accountNumber > accountCount) {
        printf("Account not found!\n");
        return;
    }

    float amount;
    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > accounts[accountNumber - 1].balance) {
        printf("Invalid amount or insufficient balance!\n");
        return;
    }

    accounts[accountNumber - 1].balance -= amount;
    printf("Withdrew %.2f successfully! New balance is %.2f.\n", amount, accounts[accountNumber - 1].balance);
}

void displayBalance(int accountNumber) {
    if (accountNumber <= 0 || accountNumber > accountCount) {
        printf("Account not found!\n");
        return;
    }

    printf("Account Holder: %s\n", accounts[accountNumber - 1].name);
    printf("Account Balance: %.2f\n", accounts[accountNumber - 1].balance);
}

void showAccounts() {
    printf("\n=== All Accounts ===\n");
    for (int i = 0; i < accountCount; i++) {
        printf("Account Number: %d, Name: %s, Balance: %.2f\n", 
               accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
}
