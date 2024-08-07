// Abdul

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime> 
#include <cstdlib> 

using namespace std;

class Order 
{
    private:
    double priceArray[5] = {5.25, 5.75, 5.95, 5.95, 5.95};
    double quantityArray[5] = {0, 0, 0, 0, 0};

    public:
    void displayMenu() 
    {
        cout << "******************** DE ANZA COLLEGE FOOD COURT ********************\n\n\n";
        cout << "Option 1 - De Anza Burger: $5.25\n";
        cout << "Option 2 - Bacon Cheese: $5.75\n";
        cout << "Option 3 - Mushroom Swiss: $5.95\n";
        cout << "Option 4 - Western Burger: $5.95\n";
        cout << "Option 5 - Don Cali Burger: $5.95\n\n\n";
        cout << "*******************************************************************\n\n";
    }
    

    void getInputs(double& option) 
    {
        cout << setprecision(2) << fixed; // Set precision for output
        cout << "Choose the option (Enter the corresponding number): \n";
        cout << "Option: ";
        cin >> option;

        // Validate user input for option
        while (option < 1 || option > 5 || option != (int)option) 
        {
            cout << "Please choose a valid option (1 to 5): ";
            cin >> option;
        }

        // Prompt for quantity
        cout << "How many do you want: ";
        cin >> quantityArray[(int)option - 1]; // Update quantity in the array

        // Validate quantity
        while (quantityArray[(int)option - 1] <= 0) 
        {
            cout << "Please enter a valid quantity: ";
            cin >> quantityArray[(int)option - 1];
        }
    }

    void calculateBill(double& total_price, double& taxPrice, double& totalCost, string people) 
    {
        double tax = 0.09;
        // Calculate total price before tax
        for (int i = 0; i < 5; ++i) {
            total_price += quantityArray[i] * priceArray[i];
        }

        // Calculate tax and total cost if the user is a staff
        if (people == "Staff" || people == "staff") 
        {
            taxPrice = total_price * tax;
            totalCost = total_price + taxPrice;
        } 
        
        else 
        {
            totalCost = total_price;
        }
    }

    void printBill(double total_price, double taxPrice, double totalCost, string people) 
    {
        // Display receipt
        cout << "***********************************************\n";
        cout << "                  RECEIPT                      \n\n";
        cout << "Food Items \t Quantity \t Cost\n";
        cout << "***********************************************\n";

        string options[] = {"De Anza Burger", "Bacon Cheese", "Mushroom Swiss", "Western Burger", "Don Cali Burger"};
        // Display items with non-zero quantities
        for (int i = 0; i < 5; ++i) 
        {
            if (quantityArray[i] > 0)
                cout << options[i] << "\t\t" << quantityArray[i] << "\t\t$" << quantityArray[i] * priceArray[i] << '\n';
        }

        // Display total price and tax if applicable
        cout << "Total amount :  \t$" << total_price << '\n';
        if (people == "Staff" || people == "staff") 
        {
            cout << "Tax amount:         \t$" << taxPrice << '\n';
            cout << "Total after tax:    \t$" << totalCost << '\n';
        }
    }

    void saveBillToFile(double total_price, double taxPrice, double totalCost, string people) 
    {
        ofstream outFile;
        // Generate a random number between 1000 and 2000 for the file name
        srand(time(0));
        int fileName = rand() % 1001 + 1000;

        // Open file with generated name
        outFile.open(to_string(fileName) + ".txt");

        // Write bill details to file
        outFile << "***********************************************\n";
        outFile << "                  RECEIPT                      \n\n";
        outFile << "Food Items \t Quantity \t Cost\n";
        outFile << "***********************************************\n";

        string options[] = {"De Anza Burger", "Bacon Cheese", "Mushroom Swiss", "Western Burger", "Don Cali Burger"};
        // Write items with non-zero quantities
        for (int i = 0; i < 5; ++i) 
        {

            if (quantityArray[i] > 0)
                outFile << options[i] << "\t\t" << quantityArray[i] << "\t\t$" << quantityArray[i] * priceArray[i] << '\n';
        }

        // Write total price and tax if applicable
        outFile << "Total amount :  \t$" << total_price << '\n';
        if (people == "Staff" || people == "staff") 
        {
            outFile << "Tax amount:         \t$" << taxPrice << '\n';
            outFile << "Total after tax:    \t$" << totalCost << '\n';
        }

        // Close file
        outFile.close();

        cout << "Bill saved to file " << fileName << ".txt" << endl;
    }
};

int main() 
{
    Order order;

    double option;
    char again = 'Y';
    double total_price = 0, taxPrice = 0, totalCost = 0;
    string people;

    // Prompt the user if they are a student or a staff
    cout << "Before you order, are you a student or a staff? Type (Student) if you are. Otherwise type (Staff) if you work here: ";
    cin >> people;

    // Validate user input
    while (people != "Student" && people != "student" && people != "Staff" && people != "staff") 
    {
        cout << "PLEASE ENTER 'Student' IF YOU ARE A STUDENT OR ENTER 'Staff' IF YOU ARE A STAFF: ";
        cin >> people;
    }

    // Loop to continue ordering
    do 
    {
        order.displayMenu(); // Display the menu
        order.getInputs(option); // Get inputs from user
        cout << "Would you like to order again? Enter 'Y' to continue or 'N' to exit.\n";
        cin >> again;
    } while (again == 'Y' || again == 'y');

    // Calculate total price, tax, and total cost
    order.calculateBill(total_price, taxPrice, totalCost, people);

    // Print the bill
    order.printBill(total_price, taxPrice, totalCost, people);


 // Save the bill to a file
    order.saveBillToFile(total_price, taxPrice, totalCost, people);

    return 0;
}

