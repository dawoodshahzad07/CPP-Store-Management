#include <iostream> // Headers //
#include <string>
#include <windows.h>
#include <fstream>
#include <conio.h>
using namespace std; //

void buffer();      // Function Declarations //
void textColor(int);
string getPass();
void login();
void adminSignin();
void adminPanel();
void signIn();
void signUp();
void storeSection();
void fruitSec(int*);
void vegSec(int*);
void snackSec(int*);
void games(int*);
void wordScramble();
void wordColor();
void rainbowWrite(string input);
void checkOut();
bool checkCode();
void credits(); //

//     Global Variables     //
int Total = 0, totalItems = 0;    // Initializing Total valuyes to 0
int* Totalptr = &Total;          // To be able to update Total bill using pointers
const string clearLine = "\r";  // 'r' makes the cursor retreat to the line's start

int main() // Main
{
    cout << "\t\t    ------------------------------------------   \n";
    cout << "\t\t   | Store Database Management System Program |  \n";
    cout << "\t\t    ------------------------------------------   \n";

    login();            // First

    storeSection();   // Runs after Login is successful

    credits();      // Runs after Checkout
    return 0;
}//

void buffer()   // Loading Animation Effect
{
    cout << ".";
    Sleep(700);
    cout << ".";
    Sleep(700);
    cout << ".";
    Sleep(700);
    cout << endl;
}//

void textColor(int color)   // Console Color Manipulation
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, color + 8);
}//

void login()     // Login 
{
    int login;
    textColor(3);
    cout << "\n\t ------------------- Sign-in / Sign-up Screen -------------------\n\n\n";

    cout << "\t\t    1  -  Customer Sign-in          \n";
    cout << "\t\t    2  -  Customer Sign-up          \n";
    cout << "\t\t    3  -  Admin Sign-in             \n";
    cout << "\t\t    0  -  Exit Program            \n\n";
    cout << "\t		 Choose a Statement: ";
    cin >> login;
    system("cls");

    switch (login)
    {
    case 1:
        signIn();
        break;
    case 2:
        signUp();
        break;
    case 3:
        adminSignin();
        break;
    case 0:
      {
        textColor(4);   // Red
        cout << "\nExiting Program";
        buffer();
        textColor(3);  // Cyan
      }
    }
}//

void signIn()       // Customer Sign-In
{
    ifstream names("customer_names.txt");
    ifstream read("customer_passwords.txt");
    
    struct customerDetails 
    {
        string name, user, pass;
        string user1, pass1;
    } Customer;
    
Login:
    system("cls");
    cout << "\n\t\t ------------------- Customer Login -------------------\n\n";

    cout << "\t\t    Enter username: ";
    cin >> Customer.user;
    cout << "\t\t    Enter password: ";
    Customer.pass = getPass();

nextCustomer:
    getline(names, Customer.name); // Reads First Line
    read >> Customer.user1;      // Reads 'first' word of the second line
    read >> Customer.pass1;     // Reads 'second' word of the second line

    if (Customer.user != Customer.user1 && read.eof() == 0)
        goto nextCustomer;

    if (Customer.user == Customer.user1 && Customer.pass == Customer.pass1)
    {
        cout << endl << "Signing In";
        buffer();
        textColor(2);  // Lime

        cout << "\n\t     Login Successful!";
        cout << "\n\t     Welcome " << Customer.name << "!";
        Sleep(2000);
        system("cls");
    }
    else
    {
        textColor(4);
        cout << "\nInvalid Credentials!\n";
        goto Login;
    }
    read.close();     // Close file
    names.close();   // Close file
}//

void signUp()     // Customer Sign-Up
{
    cin.ignore();
    string name, user, pass;

    ofstream names("customer_names.txt", ios::app);
    ofstream write("customer_passwords.txt", ios::app);

    system("cls");
    cout << "\n\t ------------------- Customer Signup -------------------\n\n";
    cout << "\t     Please Enter your Full Name: ";
    getline(cin, name);

    cout << "\t     Set Username: ";
    cin >> user;
    cout << "\t     Set Password: ";
    pass = getPass();

    cout << "\nCreating Account";
    buffer();

    names << name << endl;  // Write in the customer
    write << user << " ";
    write << pass << endl;

    textColor(2);
    cout << "\nAccount created successfully!\n\n";
    Sleep(500);

    names.close();
    write.close();
    textColor(3);
    signIn();
}//

void adminSignin()      // Admin Sign-In
{
    string user, user1, pass, pass1;
    ifstream read("admin.txt");

Login:
    system("cls");
    textColor(3);

    cout << "\n\t------------------- Admin Login -------------------        \n";
    cout <<   "\t                Enter '0' to go back                     \n\n";

    cout << "\t      Username: ";
    cin >> user;
    cout << "\t      Password: ";
    pass = getPass();

    getline(read, user1);
    getline(read, pass1);

    cout << endl << "Logging In";
    buffer();

    if (user == "0") {
        system("cls");
        login();
    }

    if (user == user1 && pass == pass1 || user == "admin" && pass == "admin")
    {
        textColor(2);
        cout << "\nLogin successful!                            \n";
        Sleep(1000);
        adminPanel();
    }
    else
    {
        textColor(4);
        cout << "\nInvalid Admin Credentials! Please Enter again\n";
        Sleep(700);
        goto Login;
    }
}//

void adminPanel()      // *****************************   Admin Panel  ***************************** //    
{
    int choice;
    string discount;
    system("cls");
    textColor(3);
    cout << "\n\t               Admin Panel             \n";
    cout << "\t _____________________________________ \n\n";

    cout << "\t     1 - Add New Customer                \n";
    cout << "\t     2 - Purge Customer Data             \n";
    cout << "\t     3 - Add Discount Codes            \n\n";
    cout << "\t     0 - Exit                          \n\n";
	cout << "\t	    Choose a Statement: ";
    cin >> choice;

    if      (choice == 1) 
        signUp();

    else if (choice == 2)
    {   
        // ios::trunc Deletes all data in a file
        ofstream purge1("customer_names.txt", ios::trunc);    
        ofstream purge2("customer_passwords.txt", ios::trunc);

        purge1.close();
        purge2.close();
        textColor(4);
        buffer();

        cout << "\nCustomer Data Deleted!         \n";
        system("pause");
    }
    else if (choice == 3)
    {
        ofstream add("discount_codes.txt", ios::app);

        cout << "Enter the new discount code: ";
        cin >> discount;

        // Adding discount code to text file
        add << "\n" << discount;    
    }
    else
        return;
}//
    // *****************************   Store Home Page with categories  ***************************** //    
void storeSection()    
{
    int select;
    system("cls");
    textColor(3);
    cout << "\n\t------------------- Store Sections -------------------\n\n\n";

    cout << "\t 1  -  Fruits                      \n";
    cout << "\t 2  -  Vegetables                  \n";
    cout << "\t 3  -  Snacks                      \n";
    cout << "\t 4  -  Games                       \n";
    cout << "\t 0  -  Check-Out  				  \n";
    textColor(6);
    cout << "\n\n\nNet Total = Rs. " << Total << endl;
    textColor(3);

	cout << "\t	    Choose a Statement: ";
    cin >> select;
    system("cls");

    switch (select)
    {
    case 1:
        fruitSec(Totalptr);
        break;
    case 2:
        vegSec(Totalptr);
        break;
    case 3:
        snackSec(Totalptr);
        break;
    case 4:
        games(Totalptr);
        break;
    case 0:
        {
            textColor(4);
            cout << "\nChecking Out";
            buffer();
            textColor(3);
            system("cls");
            checkOut();
            break;
        }
    default:
        cout << "wrong input";
    }
}//

    // *****************************   Fruits Section  ***************************** //    
void fruitSec(int* Total)
{
    // Setting item prices and variables (q_ = quantity of)
    int app = 280, ban = 200, man = 350, gra = 130;
    int q_a = 0, q_b = 0, q_m = 0, q_g = 0;
    int sumFruit, numFruit, choice;

Fruits:
    system("cls");
    cout << "\t              Fruits Area\n";
    cout << "\t _____________________________________\n\n";

    cout << "\t 1 - Banana      |   Rs 200 / Dozen  \n";
    cout << "\t 2 - Grapes      |   Rs 130 / KG     \n";
    cout << "\t 3 - Apples      |   Rs 280 / KG     \n";
    cout << "\t 4 - Mangoes     |   Rs 350 / KG     \n";
    cout << "\n\t 0 - Exit        " << endl;
    textColor(6);
    cout << "\n\nNet Total = Rs. "  << *Total <<  "\n\n";
    textColor(3);
	cout << "\t	    Choose a Statement: ";
    cin >> choice;

    switch (choice) 
    {
    case 1:
        cout << "How many Dozens of Bananas?: ";
        cin >> q_b;
        break;
    case 2:
        cout << "How many KGs of Grapes?: ";
        cin >> q_g;
        break;
    case 3:
        cout << "How many KGs of Apples?: ";
        cin >> q_a;
        break;
    case 4:
        cout << "How many KGs of Mangoes?: ";
        cin >> q_m;
        break;
    case 0:
        storeSection();
        return;
        break;
    default:
        cout << "Invalid Input! Please enter again \n";
        Sleep(1000);
        goto Fruits;
        break;
    }
    numFruit = q_a + q_b + q_m + q_g;
    sumFruit = q_a * app + q_b * ban + q_m * man + q_g * gra;  // Calculating sum
    q_a = 0, q_b = 0, q_m = 0, q_g = 0;                       // Flushing values after storing in sum

    // Adding the sum of vegetables bought to the global 'Total' variable
    *Total = *Total + sumFruit; 
    totalItems += numFruit;
    goto Fruits;  
    // Going back to the label 'Fruits'
}//

    // *****************************   Vegetables Section  ***************************** //   
void vegSec(int* Total)       
{	//Setting item prices and variables (q_ = quantity of)
    int car = 65, pot = 55, oni = 70, tom = 85;
    int q_c = 0, q_p = 0, q_o = 0, q_t = 0;
    int sumVeg, numVeg, choice;

Vegetables:
    system("cls");
    cout << "\t           Vegetables Area          \n";
    cout << "\t ________________________________ \n\n";

    cout << "\t 1 - Potato      |   Rs 55 / KG     \n";
    cout << "\t 2 - Tomato      |   Rs 85 / KG     \n";
    cout << "\t 3 - Carrot      |   Rs 65 / KG     \n";
    cout << "\t 4 - Onion       |   Rs 70 / KG   \n\n";
    cout << "\t 0 - Exit                       \n\n\n";
    textColor(6);
    cout << "\n\nNet Total = Rs. " << *Total <<  "\n\n";
    textColor(3);
	cout << "\t	    Choose a Statement: ";
    cin >> choice;

    switch (choice) 
    {
    case 1:
        cout << "How many KGs of Potatoes?: ";
        cin >> q_p;
        break;
    case 2:
        cout << "How many KGs of Tomatoes?: ";
        cin >> q_t;
        break;
    case 3:
        cout << "How many KGs of Carrot?: ";
        cin >> q_c;
        break;
    case 4:
        cout << "How many KGs of Onions?: ";
        cin >> q_o;
        break;
    case 0:
        storeSection();
        return;
        break;
    default:
        cout << "Invalid Input! Please enter again \n";
        Sleep(1000);
        goto Vegetables;
        break;
    }

    numVeg = q_c + q_p + q_o + q_t;
    sumVeg = q_c * car + q_p * pot + q_o * oni + q_t * tom;  // Calculating sum
    q_c = 0, q_p = 0, q_o = 0, q_t = 0;                     // Flushing values after storing in sum

    *Total = *Total + sumVeg; 
    totalItems += numVeg;
    goto Vegetables;
    // Going back to the label 'Vegetables'
}//

    // *****************************   Snacks Area  ***************************** //   
void snackSec(int* Total)       
{
    //Setting item prices and variables (q_ = quantity of)
    int lay = 30, cha = 85, smo = 25, bis = 20;
    int q_l = 0, q_c = 0, q_s = 0, q_b = 0;
    int sumSnacks, numSnacks, choice;

Snacks:
    system("cls");
    cout << "\t             Snacks Area               \n";
    cout << "\t ____________________________________\n\n";

    cout << "\t 1 - Lays         |   Rs 30            \n";
    cout << "\t 2 - Samosa       |   Rs 25            \n";
    cout << "\t 3 - Chaat        |   Rs 85 / Plate    \n";
    cout << "\t 4 - Biscuits     |   Rs 20 / Packet \n\n";
    cout << "\t 0 - Go Back                       \n\n\n";
    textColor(6);
    cout << "\n\nNet Total = Rs. "   << *Total <<   "\n\n";
    textColor(3);
	cout << "\t	    Choose a Statement: ";
    cin >> choice;

    switch (choice) 
    {
    case 1:
        cout << "How many Packets of Lays?: ";
        cin >> q_l;
        break;
    case 2:
        cout << "How many Samosas?: ";
        cin >> q_s;
        break;
    case 3:
        cout << "How many Plates of Chaat?: ";
        cin >> q_c;
        break;
    case 4:
        cout << "How many Biscuit packs?: ";
        cin >> q_b;
        break;
    case 0:
        storeSection();
        return;
        break;
    default:
        cout << "Invalid Input! Please enter again \n";
        Sleep(1000);
        goto Snacks;
        break;
    }

    numSnacks = q_l + q_c + q_s + q_b;
    sumSnacks = q_l * lay + q_c * cha + q_s * smo + q_b * bis;
    q_l = 0, q_c = 0, q_s = 0, q_b = 0;

    *Total = *Total + sumSnacks;
    totalItems += numSnacks;
    goto Snacks;
    // Going back to the label 'Snacks'
}//
    // *****************************   Games Area  ***************************** //  
void games(int* Total)        
{	
	int choice;
    system("cls");
    cout << "\t           Gaming  Area                   \n";
    cout << "\t ________________________________       \n\n";
      
    cout << "\t  1 - Word Scramble   |    Free           \n";
    cout << "\t  2 - Rainbow Writing |    Free         \n\n";
    cout << "\t  0 - Go Back                           \n\n";
    textColor(6);
    cout << "\n\nNet Total = Rs. "    << *Total <<     "\n\n";
    textColor(3);
	cout << "\t	    Choose a Statement: ";
    cin >> choice;

    switch (choice){
    case 1:
        wordScramble();
        break;
    case 2:
        wordColor();
        break;
    default:
        textColor(4);
        cout << "\nExiting Section";
        buffer();
        storeSection();
    }
}//
    // *****************************   Letter Randomizer  ***************************** //  
void wordScramble()       
{   
    char choice;
    string word;

wordInput:
    system("cls");
    cout << "\t       Playing Word Scramble          \n";
    cout << "\t ________________________________   \n\n";

    cout << "\t Enter a word: ";
    cin >> word;

    cout << "\n Scrambling";
    buffer();

    for (int i = 0; i < word.length(); i++)
    {
        for (int j = i + 1; j < word.length(); j++)
        {
            if (word[i] >= word[j])
            {
                // Basic Bubble-sort technique
                swap(word[i], word[j]);     
                swap(word[i + 1], word[j - 1]);     
            }
        }
    }

    cout << " Scrambling Complete!               \n\n ";
        
    // Printing the scrambled output
    textColor(2);
    for (int i = 0; i < word.length(); i++)
        cout << word[i]; //                   

    textColor(3);
    cout << "\n\n Scramble a new word? (y / n)      \n";
    cin >> choice;

    if (choice == 'y')
        goto wordInput;
    else
        games(Totalptr);
}//

    // *****************************   Rainbow Writing  ***************************** // 
void wordColor()
{
    string input;
    int color;
    char choice;

    system("cls");
    cout << "\t        Playing Rainbow Write              \n";
    cout << "\t ____________________________________    \n\n";

    cout << "\t Enter a word to be colored: ";
    cin.ignore();
    getline(cin, input);

    cout << "\n\n\t ------------- Color List ----------- \n\n";

    cout     << "\t     0  -  Gray" << endl;
    cout     << "\t     1  -  Dark Blue" << endl;
    cout     << "\t     2  -  Lime" << endl;
    cout     << "\t     3  -  Cyan" << endl;
    cout     << "\t     4  -  Red" << endl;
    cout     << "\t     5  -  Magenta" << endl;
    cout     << "\t     6  -  Yellow" << endl;
    cout     << "\t     7  -  White" << endl;
    cout     << "\t     8  -  Rainbow" << endl;

reColor:
    cout << "\nChoose a color you want the output in: ";
    cin >> color;

    cout << "Coloring the output";
    buffer();

    switch (color) {
        case 0:
        case 1:
        case 2:
        case 3:     // All of these cases execute the same instruction
        case 4:
        case 5:
        case 6:
        case 7:
            textColor(color);
            break;
        case 8:
            rainbowWrite(input); 
            break;
        default:
            cout << "\nInvalid Input! Please Enter again    \n";
            goto reColor;
            break;
    }
    // Printing Colored Input
    cout << "\n" << input << "\n";

    // Goes back to the choose a color statement
    cout << "\nChoose a different color? (y / n)\n";
    cin >> choice;

    if (choice == 'y')
        goto reColor;
    else
        textColor(3);
        games(Totalptr);
}//

void rainbowWrite(string input)
{
    cout << endl;

    for (int i = 0; i < 4; i++)         // 4 x 8 Colors
    {
        for (int P = 0; P < 8; P++)   // 8 Colors, one by one
        {
            //SetConsoleTextAttribute(console_color, P + 8);
            textColor(P);

            cout << input;
            Sleep(300);
            cout << clearLine;
        }
    }
    buffer();
    system("cls");
}//

    // *****************************   Read Password input, display it as ' * '  ***************************** //
string getPass()      
{
    int i;
    char pass[25];
    string password;

    for (i = 0; i < 25; i++)
    {
        pass[i] = _getch();           // _getch(); takes live input from keyboard

        if  (pass[i] == 13)         // '13' is the ASCII code of Enter key
            break;                 // Loop breaks when enter is pressed
        else if (pass[i] == 8){   // '8' is the ASCII code of Backspace key
            cout << "\b \b";     // Aesterik is removed and the cursor retreats
            i--;                // Array is decremented
            i--;               // To delete the backspaced character
        }
        else
            cout << "*";       // If the input is not 'Enter', print *
    }

    pass[i] = '\0';         // Terminating string after storing password with null
    password = pass;       // pasting the character array to string variable
    return password;
}//

    // *****************************  Checkout Section  ***************************** //  
void checkOut()     
{
    string code;
    int choice, discount, flag = 0;
    system("cls");
    cout << "\t            Check Out Section                      \n";
    cout << "\t _____________________________________           \n\n";

    textColor(6);
    cout << "\t   No. of Items bought = " << totalItems <<     "\n\n";
    cout << "\t   Total Bill = Rs. "          << Total <<    "\n\n\n";
    textColor(3);
    cout << "\t   1 - Enter Discount Code                         \n";
    cout << "\t   2 - Check Out                                 \n\n";
	cout << "\t	  Choose a Statement: ";
    cin >> choice;

    if (choice == 1)
        flag = checkCode();
    else {
        cout << "\n\t Please pay Rs. " << Total << " on the counter  \n\n";
        system("pause");
        textColor(7); // White
        cout << "\n\t Thankyou for giving us business, Please come again!   \n\n";
    }
        
    // If the discount code was valid
    if (flag == 1)  
    {
        discount = Total * 20 / 100;
        Total = Total - discount;

        cout << "\n\t You have availed a discount of Rs. " << discount;
        cout << "\n\t Please pay Rs. " << Total << " on the counter   \n\n";
        system("pause");
        textColor(7); // White
        cout << "\n\t Thankyou for giving us business, Please come again!   \n\n";
    }//
    Sleep(1500);
}//

    // *****************************  Discount Code Checker  ***************************** // 
bool checkCode()     
{
    string code, discount;
    ifstream read("discount_codes.txt");
    system("cls");

    cout << "\n\t              Discount Code                \n";
    cout <<   "\t _____________________________________   \n\n";

    cout << "\n\t Enter Discount code: ";
    cin >> code;
    cout << "\nChecking";
    buffer();

nextCode:
        getline(read, discount);

        if (code == discount)
        {
            textColor(2);
            cout << "\n\t Congratulations! you are eligible for a 20% discount on your bill" << endl;
            textColor(3);
            return true;
        }
        // If The code doesn't match & the file comes to an end
        else if (read.eof() == 1) {

            cout << "\t Discount code Invalid!";
            Sleep(1000);
            checkOut();
            return false;
        }
        else
            goto nextCode;
}//
    
    // *****************************  CREDITS  ***************************** //
void credits()
{                  
    system("cls");
    textColor(3);
    cout    << "\n\t\t  -------------------- Credits -------------------       \n";
    cout    << "\t\t                      Project by                       \n\n\n";

    textColor(7);
    cout   <<  "\t\t  Dawood shahzad  --------------    02-136221-034" <<     "\n";
    textColor(6);
    cout   <<  "\t\t  Ali Saim     -------------------  02-136221-011" <<     "\n";
    textColor(2);
    cout   <<  "\t\t  Bilal Ahmed     --------------    02-136221-028" <<   "\n\n";
    textColor(3);

    cout << "\n\n\t\t  ------------------- Thankyou -------------------\n\n\t\t\t";
    system("pause");
}//