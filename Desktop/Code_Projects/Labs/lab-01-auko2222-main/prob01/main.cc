// TODO: please fill in below.
// <Your name>
// <Your section number> (e.g. CPSC 121L-01)
// <Date>
// <Your csu.fullerton.edu email>
// <Your GitHub username>
//
// Lab 1-1
// If it is a pair programming lab please specify partner below.
// Partner: @anabanana

#include <iostream>
#include <iomanip> 


double calculateTip(double cost, double percentage) {
    return cost * (percentage / 100.0);
}


double calculateTax(double cost) {
    return cost * 0.075;
}

int main() {
    double cost;
    double tipPercentage;
    double tipAmount;
    double taxAmount;
    double total;

    std::cout << std::fixed; 
    std::cout << std::setprecision(2);

    std::cout << "Please input meal cost: ";
    std::cin >> cost;
    std::cout << "Please input tip percentage: ";
    std::cin >> tipPercentage;

    tipAmount = calculateTip(cost, tipPercentage);
    taxAmount = calculateTax(cost);
    total = cost + tipAmount + taxAmount;

    std::cout << "\n";
    std::cout << "Restaurant Bill\n";
    std::cout << "====================\n";
    std::cout << "Subtotal: $" << cost << "\n";
    std::cout << "Taxes: $" << taxAmount << "\n";
    std::cout << "Tip: $" << tipAmount << "\n";
    std::cout << "====================\n";
    std::cout << "Total: $" << total << "\n";

    return 0;
}

