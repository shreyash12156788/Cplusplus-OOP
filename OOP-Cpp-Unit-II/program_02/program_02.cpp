#include <iostream>   // Used for displaying output
#include <memory>     // Used for smart pointers like unique_ptr
#include <string>     // Used for storing text values
#include <vector>     // Used for storing multiple payment objects

using namespace std;


// Base class for different types of payment methods
class PaymentMethod
{
protected:

    // Stores the transaction ID
    string transactionId;

    // Stores the payment amount
    double amount;


public:

    // Constructor used to initialize transaction details
    PaymentMethod(string tid, double amt)
        : transactionId(tid), amount(amt)
    {
        // Transaction ID and amount are initialized here
    }


    // Pure virtual function for processing payment
    // Each payment method will implement it differently
    virtual bool processPayment() const = 0;


    // Virtual destructor for safe destruction of derived objects
    virtual ~PaymentMethod() = default;
};


// Class for processing credit card payments
class CreditCardPayment : public PaymentMethod
{
private:

    // Stores the masked credit card number
    string maskedCardNumber;


public:

    // Constructor used to initialize credit card payment details
    CreditCardPayment(string tid, double amt, string card)
        : PaymentMethod(tid, amt),
          maskedCardNumber(card)
    {
        // Credit card details are initialized here
    }


    // Overrides the payment processing function
    bool processPayment() const override
    {
        // Display the credit card transaction details
        cout << "Credit-card transaction " << transactionId
             << " for Rs. " << amount
             << " using " << maskedCardNumber
             << " completed." << endl;

        // Return true because the payment was completed
        return true;
    }
};


// Class for processing UPI payments
class UPIPayment : public PaymentMethod
{
private:

    // Stores the UPI ID
    string upiId;


public:

    // Constructor used to initialize UPI payment details
    UPIPayment(string tid, double amt, string upi)
        : PaymentMethod(tid, amt),
          upiId(upi)
    {
        // UPI details are initialized here
    }


    // Overrides the payment processing function
    bool processPayment() const override
    {
        // Display the UPI transaction details
        cout << "UPI transaction " << transactionId
             << " for Rs. " << amount
             << " from " << upiId
             << " completed." << endl;

        // Return true because the payment was completed
        return true;
    }
};


// Class for processing net-banking payments
class NetBankingPayment : public PaymentMethod
{
private:

    // Stores the bank name
    string bankName;


public:

    // Constructor used to initialize net-banking details
    NetBankingPayment(string tid, double amt, string bank)
        : PaymentMethod(tid, amt),
          bankName(bank)
    {
        // Bank details are initialized here
    }


    // Overrides the payment processing function
    bool processPayment() const override
    {
        // Display the net-banking transaction details
        cout << "Net-banking transaction " << transactionId
             << " for Rs. " << amount
             << " through " << bankName
             << " completed." << endl;

        // Return true because the payment was completed
        return true;
    }
};


int main()
{
    // Create a vector to store different payment objects
    vector<unique_ptr<PaymentMethod>> payments;


    // Add a credit card payment to the vector
    payments.push_back(
        make_unique<CreditCardPayment>(
            "TXN001", 2500, "XXXX-XXXX1234"
        )
    );


    // Add a UPI payment to the vector
    payments.push_back(
        make_unique<UPIPayment>(
            "TXN002", 1200, "student@upi"
        )
    );


    // Add a net-banking payment to the vector
    payments.push_back(
        make_unique<NetBankingPayment>(
            "TXN003", 5000, "Example Bank"
        )
    );


    // Display the payment gateway heading
    cout << "=== Payment Gateway ===" << endl;


    // Go through each payment stored in the vector
    for (const auto& payment : payments)
    {
        // Process the current payment
        // The correct overridden function is called automatically
        payment->processPayment();
    }


    // End the program successfully
    return 0;
}