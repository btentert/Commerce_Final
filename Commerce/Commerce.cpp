// Commerce.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_set>
#include <list>
#include <iomanip>
#include <bitset>
#include <ctime>
#include <sstream>
#include <chrono>
using namespace std;

//Note that not ever customer will have a zipcode especially if they live in another country such as Costa Rica, that is why address is stored as one string

//Shipping
//Payment
//History

class Card
{
public:
    string Name_On_Card, Expiration_Date;
    uint32_t Number;
    uint64_t CVV;

    Card()
    {

    }

    Card(string Name_On_Card, uint64_t Number, uint16_t CVV, string Expiration_Date)
    {
        this->Name_On_Card = Name_On_Card;
        this->Number = Number;
        this->CVV = CVV;
        this->Expiration_Date = Expiration_Date;
    }

    void Show()
    {
        cout << "--------------------------------------------------------------------\n";
        cout << "Name:" << Name_On_Card << "\nNumber:" << Number << "\nCVV:" << CVV << "\nExpiration:" << Expiration_Date;
        cout << "\n--------------------------------------------------------------------\n";
    }
};

string Current_Date()
{
    chrono::system_clock::time_point date = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(date);
    char str[26];
    ctime_s(str, sizeof str, &t);
    return str;
}




// These are all physical movies sent.
class Movie_Product
{
public:
    // Variables in total.
    string Name, Description, Year, Director;
    string genre;
    float Cost;
    uint64_t Quantity_Left;

    Movie_Product() {};
    // The description of each movie.
    Movie_Product(string Name, string Description, string Director, string Genre, float Cost, uint64_t Quantity, uint16_t Year)
    {
        this->Name = Name;
        this->Description = Description;
        this->Cost = Cost;
        this->Quantity_Left = Quantity;
        this->genre = Genre;
    }
};

// Holds all of the movies in stock.
class Inventory
{
public:
    // Product IDs tied to product details.
    map <uint64_t, Movie_Product> Products;
    // All of the movies in the inventory.
    Inventory()
    {
        this->Products.insert(pair<uint64_t, Movie_Product>(1, Movie_Product("Hunger Games", "Fighting in a distopia", "Gary Ross & Francis Lawrence", "Romance", 29.99f, 1000, 2008)));
        this->Products.insert(pair<uint64_t, Movie_Product>(2, Movie_Product("Attack of the Clones", "Space Fighting", "George Lucas", "SciFi", 39.99f, 400, 2008)));
        this->Products.insert(pair<uint64_t, Movie_Product>(3, Movie_Product("The Lord of The Rings: The Fellowship of The Ring", "A group of mythical creatures takes a long hike to destroy some jewelry", "Peter Jackson", "SciFi", 44.99, 600, 2001)));
        this->Products.insert(pair<uint64_t, Movie_Product>(4, Movie_Product("The Cabin in The Woods", "A group of friends is tortured for a game", "Drew Goddard", "Horror", 44.99f, 1060, 2012)));
        this->Products.insert(pair<uint64_t, Movie_Product>(5, Movie_Product("Encanto", "Family-centered generational trauma set to music", "Bryon Howard & Jared Bush", "Animated Musical", 29.99f, 164, 2021)));
        this->Products.insert(pair<uint64_t, Movie_Product>(6, Movie_Product("John Wick", "A retired assassin seeks vengence when a thug stole his puppy", "Chad Stahelski", "Action", 34.99f, 380, 2014)));
        this->Products.insert(pair<uint64_t, Movie_Product>(7, Movie_Product("Spirited Away", "Little girl is forced into child labor after her parents won't stop eating", "Hayao Miyazaki", "Anime Fantasy", 49.99, 6, 2002)));
        this->Products.insert(pair<uint64_t, Movie_Product>(8, Movie_Product("50 First Dates", "A man falls for a girl with short term memory loss, and has to woo her every day", "Peter Segal", "Romance", 24.99, 500, 2004)));
        this->Products.insert(pair<uint64_t, Movie_Product>(9, Movie_Product("Mars Attacks!", "Martians arrive on earth claiming to be peaceful", "Tim Burton", "SciFi", 24.99f, 970, 1996)));
        this->Products.insert(pair<uint64_t, Movie_Product>(10, Movie_Product("Monsters, Inc.", "Monsters try to drain screams out of a small child for money", "Pete Docter", "Animated Comedy", 19.99f, 342, 2001)));
        this->Products.insert(pair<uint64_t, Movie_Product>(11, Movie_Product("Dr. Strangelove", "Air Force general sends his bomber to destroy the USSR", "Stanley Kubrick", "Comedy", 24.99f, 328, 1964)));
    }

    void Update(uint64_t ID, uint64_t Amount)
    {
        if (Exists(ID))
            Products[ID].Quantity_Left = Amount;
    }

    // Finds the user's movie ID they entered.
    bool Exists(uint64_t ID)
    {
        return Products.find(ID) != Products.end();
    }
    // Checks to see if the movie is in stock.
    bool In_Stock(uint64_t ID)
    {
        return Exists(ID) && Products[ID].Quantity_Left > 0;
    }
    // Gets the genre of that specified movie.
    bool Has_Enough(uint64_t ID, uint16_t Amount)
    {
        return Products[ID].Quantity_Left >= Amount;
    }
    uint16_t Stock(uint64_t ID)
    {
        return Products[ID].Quantity_Left;
    }
    string Get_Genre(uint64_t ID)
    {
        return Products[ID].genre;
    }
    // Gets the price of that movie.
    float Movie_Price(uint64_t ID)
    {
        return Products[ID].Cost;
    }
    // Choice 1 in the sign in menu: Display all the information for each movie in the inventory.
    void Display()
    {
        cout << "Here's a list of all our movies.\n----------------------------------------------------------------------------------------\n";
        for (const auto& pair : Products)
        {
            cout << "\nID: " << pair.first;
            cout << "\nName: " << pair.second.Name;
            cout << "\nCost: $" << pair.second.Cost;
            cout << "\nStock Left: " << pair.second.Quantity_Left;
            cout << "\nGenre: " << pair.second.genre;
            cout << "\nDescription: " << pair.second.Description << "\n";
        }
        cout << "----------------------------------------------------------------------------------------\n";
    }
    // For the checkout class to use.
    void Display(uint64_t ID, uint16_t Quantity)
    {
        if (Exists(ID))
        {
            Movie_Product movie = Products[ID];
            cout << "\nID: " << ID;
            cout << "\nName: " << movie.Name;
            cout << "\nCost: $" << movie.Cost;
            cout << "\nQuantity: " << Quantity;
            cout << "\nTotal Cost: $" << movie.Cost * (float)Quantity << " | (" << Quantity << "*" << movie.Cost << ")";
            cout << "\nGenre: " << movie.genre;
            cout << "\nDescription: " << movie.Description << "\n";
        }
    }

    string Movie_Name(uint64_t ID)
    {
        return Products[ID].Name;
    }
    // Removes that movie from the inventory because the customer has purchased it.
    bool Buy(uint64_t Product_ID)
    {
        if (Exists(Product_ID))
        {
            Movie_Product product = Products[Product_ID];
            if (product.Quantity_Left > 0)
            {
                Products[Product_ID].Quantity_Left--;
                return true;
            }
        }
        return false;
    }
    // Removes the movie the certain number of times of the quantity that the user wants to buy.
    bool Buy(uint64_t Product_ID, uint32_t Quantity)
    {
        if (Exists(Product_ID))
        {
            Products[Product_ID].Quantity_Left -= Quantity;
        }
        return false;
    }
};

Inventory inventory;

class Order
{
public:

    map <uint64_t, uint16_t> Products; // Products tied to quantity ordered.
    float Total_Cost; // Complete cost of the cart.
    string Date, Address;
    // Card Information.
    Card card;

    Order()
    {

    }

    Order(map <uint64_t, uint16_t> Products, float Total_Cost, Card card, string Delivery)
    {
        this->Products = Products;
        this->Total_Cost = Total_Cost;
        this->card = card;
        this->Address = Delivery;
        Date = Current_Date();
    }

    void Show()
    {
        cout << "\nOrder Summary\n----------------------------------------------------------------------------------------\n";
        cout << "Date ordered was " << Date << "\n";
        cout << "Delivery Address:" << Address << endl << "Expected Delivery Date: Never! Nonexistent!" << endl;
        cout << card.Name_On_Card << "'s card was used and the card number was " << card.Number << "\n";
        cout << "Here's all of the movies you ordered\n\n";

        for (const auto& pair : Products)
        {
            cout << "ID: " << pair.first << endl;
            cout << "Name:" << inventory.Movie_Name(pair.first);
            cout << "\nCost Per Movie: $" << inventory.Movie_Price(pair.first);
            cout << "\nQuantity: " << pair.second;
            cout << "\nTotal Cost: $" << inventory.Movie_Price(pair.first) * pair.second << " | (" << pair.second << "*" << inventory.Movie_Price(pair.first) << ")\n";
        }


        cout << "----------------------------------------------------------------------------------------\n";
        cout << "Your total was $" << Total_Cost << "\n";
        cout << "----------------------------------------------------------------------------------------\n";
    }
};

class Cart
{
public:
    map <uint64_t, uint16_t> Movies_In_Cart; // Movie ID linked to the quantity.
    // Choice 2 in the sign in menu: displays the items in the cart.

    // Choice 3 in the sign in menu: 
        // Function that lets the user add one movie to the cart.
    void Add(uint64_t Product_ID)
    {
        if (!Exists(Product_ID))
            Movies_In_Cart.insert(pair<uint64_t, uint16_t>(Product_ID, 1));
        else Movies_In_Cart[Product_ID]++;
    }
    // Function that lets the user enter whatever quantity of movies they want.
    void Add(uint64_t Product_ID, uint16_t Quantity)
    {
        if (!Exists(Product_ID))
            Movies_In_Cart.insert(pair<uint64_t, uint16_t>(Product_ID, Quantity));
        else Movies_In_Cart[Product_ID] += Quantity;
    }
    // Choice 4 in the sign in menu: function that removes an item from the customer's shopping cart.
    void Remove(uint64_t Product_ID)
    {
        Movies_In_Cart.erase(Product_ID);
    }

    void Clear()
    {
        Movies_In_Cart.clear();
    }

    float Total()
    {
        float t = 0;
        for (const auto& pair : Movies_In_Cart)
        {
            t += (float)((float)inventory.Movie_Price(pair.first) * (float)pair.second);
        }
        return t;
    }

    bool Exists(uint64_t ID)
    {
        return Movies_In_Cart.find(ID) != Movies_In_Cart.end();
    }

    uint16_t Amount_Of_Movies(uint64_t ID)
    {
        if (Exists(ID)) return Movies_In_Cart[ID];
        return 0;
    }

    // Function that shows the shopping cart doesn't have any items in it.
    bool Is_Cart_Empty()
    {
        return Movies_In_Cart.size() == 0;
    }
};



// Customer's information.
class Customer
{
public:
    string Name, Address, Email, Password;
    uint32_t Phone_Number;
    Card card;


    Cart cart; // Object of the shopping cart class.
    vector<Order> Order_History;

    Order Checkout()
    {
        Order order = Order(cart.Movies_In_Cart, cart.Total(), card, Address);

        Order_History.push_back(order);
        cart.Clear();
        return order;
    }

    // Choice 6 in the sign in menu: displays the customer's order history.
    void Display_History()
    {
        if (Order_History.empty())
            cout << "You have no order history.\n";
        else
        {
            cout << "Here's Your Order History\n";
            for (auto& pair : Order_History)
            {
                pair.Show();
            }
        }
    }
    // Function that makes sure the password is correct.
    bool Correct_Password(string Password)
    {
        return (Password == this->Password);
    }
};



string Current_Email;

// Email linked to customer account.
map <string, Customer> Customers;

// Function to check to see if the user is signed in.
bool Signed_In()
{
    return Current_Email.length() > 0;
}

// Function to make sure the customer has created an account.
bool Customer_Exists(string Email)
{
    return Customers.find(Email) != Customers.end();
}

bool Display_Cart()
{
    bool notEmpty;

    if (!Customers[Current_Email].cart.Is_Cart_Empty())
    {
        notEmpty = 1;

        cout << "Here's a list of movies in your cart\n----------------------------------------------------------------------------------------\n";
        for (const auto& pair : Customers[Current_Email].cart.Movies_In_Cart)
        {
            inventory.Display(pair.first, pair.second);
        }
        cout << "----------------------------------------------------------------------------------------\nYour Cart Total is $" << Customers[Current_Email].cart.Total() << endl;
    }
    else { cout << "Your cart is empty\n"; notEmpty = 0; }

    return notEmpty;
}

// Choice 3 in the sign in menu: customer wants to add an item to their shopping cart.
bool Add_To_Cart(uint64_t Product_ID, uint16_t Quantity)
{
    // If the customer exists,
    if (Signed_In())
    {
        Customers[Current_Email].cart.Add(Product_ID, Quantity); // Add that movie to the cart.
        return true;
    }
    return false;
}

void Checkout()
{

    if (!Customers[Current_Email].cart.Is_Cart_Empty())
    {
        for (const auto& pair : Customers[Current_Email].cart.Movies_In_Cart)
        {
            inventory.Buy(pair.first, pair.second);
        }

        "Thanks for ordering, your order details are below.\n";
        Customers[Current_Email].Checkout().Show();
    }
    else cout << "Your cart is empty\n";
}

bool Remove_From_Cart(uint64_t Product_ID)
{
    // If the customer exists,
    if (Signed_In())
    {
        Customers[Current_Email].cart.Remove(Product_ID); // Add that movie to the cart.
        return true;
    }
    return false;
}

bool In_Cart(uint64_t Product_ID)
{
    return Customers[Current_Email].cart.Exists(Product_ID);
}

void Save();

// Choice 9 in the sign in menu: customer wants to sign out of their account.
bool Signout()
{
    // If the user is signed in,
    if (Current_Email.length() != 0)
    {
        cout << Customers[Current_Email].Name << " has been signed out.\n";
        Current_Email = ""; // No email address now.
        return true;
    }
    else
    {
        cout << "You're not signed in.\n";
        return false;
    }
}

void Main_Menu();
// Choice 8 in the sign in menu: customer wants to delete their account.
bool Delete_Account()
{
    if (Signed_In()) // Makes sure the user is signed in.
    {
        string Name = Customers[Current_Email].Name;
        string Email = Current_Email;
        Signout();
        Customers.erase(Email);
        cout << Name << ", your account has been deleted.\n";
        // Deletes their email.
        Save();
        return true;
    }
    cout << "No one is signed in.\n";
    return false;
}



// Choice 1 on the start up menu: customer creating their account.
bool Signup(string Email, Customer customer)
{
    bool New = !Customer_Exists(Email); // Customer doesn't already have an account.
    // If the user doesn't already have an account,
    if (New)
    {
        Customers.insert(pair<string, Customer>(Email, customer)); // Inserting the user's email into their account.
        Current_Email = Email; // Setting the current customer's email address to the new customer's email address.
        cout << customer.Name << " has been signed in.";
    }
    else cout << "A user already exists with that email, try loging in or signing up with a another email.";
    return New;
}

// Choice 2 on the start up menu: customer signing in to their account.
bool Signin(string Email, string Password)
{
    if (Customer_Exists(Email))
    {
        Customer customer = Customers[Email];
        if (customer.Correct_Password(Password))
        {
            Current_Email = Email;
            return true;
        }
        else return false;
    }
    cout << "User doesn't exist";
    return false;
}

bool Is_Number(char s)
{
    return (std::isdigit(s) != 0);
}

bool Is_Alphabet(char s)
{
    return ((s >= 'a' && s < 'z') || (s >= 'A' && s < 'Z'));
}

bool Contains(string Search, string Contain)
{
    return (Search.find(Contain) != std::string::npos);
}

bool String_Has_Letter_And_Number(string Search, uint16_t Min_Letters, uint16_t Min_Numbers)
{
    uint16_t Alphabets = 0; uint16_t Numbers = 0;
    for (int i = 0; i < Search.length(); i++)
    {

        if (Is_Alphabet(Search[i]))
        {
            Alphabets++;
        }
        else if (Is_Number(Search[i]))
        {
            Numbers++;
        }
    }

    return Alphabets >= Min_Letters && Numbers >= Min_Numbers;

}


void Save()
{
    ofstream myfile;
    myfile.open("inventory.txt");




    for (const auto& pair : inventory.Products)
    {
        myfile << pair.first << "|" << pair.second.Quantity_Left << "\n";
    }

    myfile.close();

    ofstream customersfile;
    customersfile.open("customers.txt");




    for (auto& pair : Customers)
    {
        customersfile << "Customer\n{\n" << "Name|" << pair.second.Name << "\nEmail|" << pair.first << "\nPassword|" << pair.second.Password << "\nAddress|" << pair.second.Address << "\nCardName|" << pair.second.card.Name_On_Card << "\nCardNumber|" << pair.second.card.Number << "\nCardCVV|" << pair.second.card.CVV << "\nCardExpiration|" << pair.second.card.Expiration_Date;
        if (!pair.second.cart.Is_Cart_Empty())
        {
            customersfile << "\nCart\n{\n";
            for (const auto& pair : pair.second.cart.Movies_In_Cart)
            {
                customersfile << pair.first << "|" << pair.second << "\n";
            }
            customersfile << "}";
        }

        if (!pair.second.Order_History.empty())
        {

            for (const auto& pair : pair.second.Order_History)
            {
                customersfile << "\nOrder\n{\n";
                customersfile << "Date|" << pair.Date << "\nDelivery|" << pair.Address << "\nCost|" << pair.Total_Cost << "\nCardName|" << pair.card.Name_On_Card << "\nCardNumber|" << pair.card.Number << "\nCardCVV|" << pair.card.CVV << "\nCardExpiration|" << pair.card.Expiration_Date;
                customersfile << "\nMovies\n{\n";
                for (const auto& pair : pair.Products)
                {
                    customersfile << pair.first << "|" << pair.second << "\n";
                }
                customersfile << "\n}\n}";
            }

        }
        customersfile << "\n}\n";


    }
    customersfile.close();
}

void Load()
{
    std::ifstream Command_File("inventory.txt");

    if (!Command_File.fail())
    {
        if (Command_File.is_open())
        {
            std::string line;
            while (std::getline(Command_File, line))
            {
                if (Contains(line, "|"))
                    inventory.Update(stoi(line.substr(0, line.find("|"))), stoi(line.substr(line.find("|") + 1)));
            }

            Command_File.close();
        }
        else
        {
            cout << "\nThe file couldn't be opened.\n";
        }
    }
    else
    {
        cout << "\nThat file doesn't exit.\n";
    }


    std::ifstream Customer_File("customers.txt");

    if (!Customer_File.fail())
    {
        if (Customer_File.is_open())
        {
            std::string line;
            int Case = 0;
            Customer customer;
            Order order;
            Cart cart;
            while (std::getline(Customer_File, line))
            {
                if (Case == 1)
                {
                    if (Contains(line, "Name|") && line.find("Name|") == 0)
                        customer.Name = line.substr(line.find("Name|") + 5);
                    if (Contains(line, "Email|"))
                        customer.Email = line.substr(line.find("Email|") + 6);
                    if (Contains(line, "Password|"))
                        customer.Password = line.substr(line.find("Password|") + 9);
                    if (Contains(line, "Address|"))
                        customer.Address = line.substr(line.find("Address|") + 8);
                    if (Contains(line, "CardName|") && line.find("CardName|") == 0)
                        customer.card.Name_On_Card = line.substr(line.find("CardName|") + 9);
                    if (Contains(line, "CardNumber|"))
                        customer.card.Number = stoull(line.substr(line.find("CardNumber|") + 11));
                    if (Contains(line, "CardExpiration|"))
                        customer.card.Expiration_Date = line.substr(line.find("CardExpiration|") + 15);
                    if (Contains(line, "CardCVV|"))
                        customer.card.CVV = stoi(line.substr(line.find("CardCVV|") + 8));
                    if (line == "Order")
                    {
                        Case = 2;
                        order = Order();
                    }
                    if (line == "Cart")
                    {
                        Case = 4;
                        cart = Cart();
                    }

                    if (line == "}")
                    {
                        Case--;
                        Customers.insert(pair<string, Customer>(customer.Email, customer));
                    }
                }
                if (Case == 2)
                {

                    if (Contains(line, "Cost|"))
                        order.Total_Cost = stof(line.substr(line.find("Cost|") + 5));
                    if (Contains(line, "Date|"))
                        order.Date = line.substr(line.find("Date|") + 5);
                    if (Contains(line, "Delivery|"))
                        order.Address = line.substr(line.find("Delivery|") + 9);
                    if (Contains(line, "CardName|"))
                        order.card.Name_On_Card = line.substr(line.find("CardName|") + 9);
                    if (Contains(line, "CardNumber|"))
                        order.card.Number = stoi(line.substr(line.find("CardNumber|") + 11));
                    if (Contains(line, "CardExpiration|"))
                        order.card.Expiration_Date = line.substr(line.find("CardExpiration|") + 15);
                    if (Contains(line, "CardCVV|"))
                        order.card.CVV = stoi(line.substr(line.find("CardCVV|") + 8));

                    if (line == "Movies")
                    {
                        Case++;
                    }

                    if (line == "}")
                    {
                        Case--;
                        customer.Order_History.push_back(order);
                    }

                }
                if (Case == 3)
                {
                    if (Contains(line, "|"))
                        order.Products.insert(pair<uint64_t, uint16_t>(stoi(line.substr(0, line.find("|"))), stoi(line.substr(line.find("|") + 1))));

                    if (line == "}")
                    {
                        Case--;
                    }

                }
                if (Case == 4)
                {

                    if (Contains(line, "|"))
                        cart.Add(stoi(line.substr(0, line.find("|"))), stoi(line.substr(line.find("|") + 1)));

                    if (line == "}")
                    {
                        Case = 1;
                        customer.cart = cart;
                    }

                }
                else
                    if (line == "Customer")
                    {
                        Case = 1;
                    }
            }

            Customer_File.close();
        }
        else
        {
            cout << "\nThe file couldn't be opened.\n";
        }
    }
    else
    {
        cout << "\nThat file doesn't exit.\n";
    }

}




auto Current_Menu = Main_Menu;

bool Is_Number_(string line, uint64_t& number)
{
    try
    {
        number = stoull(line);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool Is_Number(string line)
{
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

//Automatically Saves and loads
// Menu that shows up after the user has signed in.
void Sign_In_Menu()
{

    string Command;

    cout << "\nEnter 1 to view all the movies in inventory.\nEnter 2 to view all items in your shopping cart.\nEnter 3 to add a movie to your shopping cart.\nEnter 4 to remove a movie from your shopping cart.\nEnter 5 to checkout the movies currently in your shopping cart.\nEnter 6 to view your order history.\nEnter 7 to edit your account.\nEnter 8 to view your account details.\nEnter 9 to delete your account.\nEnter 10 to sign out.\nEnter 11 to exit.\n";
    getline(cin, Command);
    // Customer wants to view all of the movies. Done
    if (Command == "1")
        inventory.Display();
    // Customer wants to view all the items in their cart. Done
    if (Command == "2")
        Display_Cart();
    // Customer wants to add a movie to their cart. Done
    if (Command == "3")
    {

        if (!inventory.In_Stock(1) && !inventory.In_Stock(2) && !inventory.In_Stock(3) && !inventory.In_Stock(4) && !inventory.In_Stock(5) && !inventory.In_Stock(6) && !inventory.In_Stock(7) && !inventory.In_Stock(8) && !inventory.In_Stock(9) && !inventory.In_Stock(10) && !inventory.In_Stock(11))
        {
            cout << "\nSorry: all our movies are sold out!\n\n";
        }
        else
        {
            string ID;
            uint64_t id;
            inventory.Display();
            cout << "Enter the id of the movie you would like to add to your cart: \n";
            getline(cin, ID);

            while (!Is_Number_(ID, id) || !inventory.Exists(id))
            {
                cout << "Enter a valid movie id to your cart \n";
                getline(cin, ID);
            }

            while (!inventory.In_Stock(id) || !Is_Number_(ID, id))
            {
                cout << inventory.Movie_Name(id) << " is out of stock. Enter a valid movie id that's in stock \n";
                getline(cin, ID);
            }

            uint64_t Quantity;
            string quantity;
            cout << "How many would you like? Type 0 to go back. \n";
            getline(cin, quantity);

            while (!Is_Number_(quantity, Quantity) || Quantity > 1000 || !inventory.Has_Enough(id, Quantity + Customers[Current_Email].cart.Amount_Of_Movies(id)))
            {
                cout << "Note that stock is limited, you can only have " << inventory.Stock(id) << " of this in your cart and you can only add up to 1,000 at time. How many would you like?\n";
                getline(cin, quantity);

            }

            if (Quantity != 0)
            {
                Add_To_Cart(id, Quantity);
            }
        }
    }
    // Customer wants to remove the movie from their cart. Done
    if (Command == "4")
    {
        string ID;
        uint64_t id;
        if (Display_Cart())
        {
            cout << "Enter the id of the movie you would like to remove from your cart: \n";
            getline(cin, ID);

            while (!Is_Number_(ID, id) || id >= UINT32_MAX || !In_Cart(id))
            {
                cout << "Enter a valid movie id to remove from your cart: \n";
                getline(cin, ID);
            }

            Remove_From_Cart(id);
        }
    }
    // Customer wants to checkout. Done
    if (Command == "5")
    {
        string Confirm;



        cout << "___________________________________________________________\n";
        while (Confirm != "yes" && Confirm != "no")
        {
            cout << "Type yes to confirm checkout or no to go back\n";
            cout << "___________________________________________________________\n";
            getline(cin, Confirm);
        }

        if (Confirm == "yes")
        {
            Checkout();
        }


    }

    // Customer wants to see their order history. Done
    if (Command == "6")
    {

        Customers[Current_Email].Display_History();
    }
    // Customer wants to edit their account. Done, you shouldn't be able to change the customers registration email becuase it is a key so it should always stay the same.
    if (Command == "7")
    {
        cout << "\nEnter 1 to change your name.\nEnter 2 to change your password.\nEnter 3 to change your shipping address.\nEnter 4 to change your credit/debit card details.\nEnter anything else to go back.\n";
        cout << "___________________________________________________________\n";
        string Command;
        getline(cin, Command);

        //Done
        if (Command == "1")
        {
            cout << "What would you like to change your name to?\n";
            cout << "___________________________________________________________\n";
            string Previous = Customers[Current_Email].Name;
            getline(cin, Customers[Current_Email].Name);
            cout << "___________________________________________________________\n";
            cout << "Your name was changed from " << Previous << " to " << Customers[Current_Email].Name << endl;
        }

        //Done
        if (Command == "2")
        {
            string Password;
            cout << "___________________________________________________________\nWhat's your old password?\n";

            getline(std::cin, Password);

            while (Password != Customers[Current_Email].Password)
            {
                cout << "Incorrect, try agian.\n";
                getline(std::cin, Password);
            }
            cout << "___________________________________________________________\n";
            cout << "What would you like your new password to be? Please enter a password with at least 10 characters, 4 letters, and 4 numbers.\n";
            getline(std::cin, Password);
            Customers[Current_Email].Password = Password;

            while (Password.length() < 10 || !String_Has_Letter_And_Number(Password, 4, 4))
            {
                cout << "Please enter a password with at least 10 characters, 4 letters, and 4 numbers.\n";
                getline(std::cin, Password);
                Customers[Current_Email].Password = Password;
            }

            cout << "___________________________________________________________\n";

        }

        //Done
        if (Command == "3")
        {
            string Address;
            cout << "___________________________________________________________\n";

            cout << "What new address would you like your orders to be delivered to?\n Please enter all relevant info such as State,Street,Unit,Zipcode, etc.\n";
            getline(std::cin, Address);
            Customers[Current_Email].Address = Address;
            cout << "___________________________________________________________\n";


        }

        //Done
        if (Command == "4")
        {
            cout << "Here's your current primary card on file\n";
            Customers[Current_Email].card.Show();


            string Name_On_Card, Expiration_Date, Number, CVV;
            cout << "___________________________________________________________\n";

            cout << "Let's change your card details.\n What's the name on your card\n";

            getline(std::cin, Name_On_Card);
            cout << "___________________________________________________________\n";

            cout << "What's the expiration date on your card? Enter in #/#/# format\n";
            getline(std::cin, Expiration_Date);

            cout << "___________________________________________________________\n";

            cout << "What's the number on your card?\n";

            while (Number.length() < 14 || Number.length() > 20 || !Is_Number(Number))
            {
                cout << "Your card number should be between 14 - 20 digits long.\n";
                getline(std::cin, Number);
            }
            cout << "___________________________________________________________\n";

            cout << "What's the CVV on your card\n";

            while (CVV.length() != 3 || !Is_Number(CVV))
            {
                cout << "Your card CVV should be at least 3 digits long.\n";
                getline(std::cin, CVV);
            }
            cout << "___________________________________________________________\n";


            Customers[Current_Email].card = Card(Name_On_Card, stoull(Number), stoi(CVV), Expiration_Date);

        }
    }
    //View Account
    if (Command == "8")
    {
        Customer customer = Customers[Current_Email];
        cout << "\n___________________________________________________________\nAccount Details";
        cout << "\nName:" << customer.Name << "\nEmail:" << Current_Email << "\nDelivery Address:" << customer.Address;
        cout << "\n___________________________________________________________\nCredit/Debit Card On File\n";

        customer.card.Show();
    }
    // Customer wants to delete their account. Done
    if (Command == "9")
    {
        Delete_Account(); Current_Menu = Main_Menu;
    }

    // Customer wants to sign out of their account. Done
    if (Command == "10")
    {
        Signout();
        Current_Menu = Main_Menu;
    }

    //Exit
    if (Command == "11")
    {
        cout << "___________________________________________________________\n";
        cout << "Thanks for visiting Amalon, have a wonderful day!";
        exit(3);
    }

    Save();

    Current_Menu();
}





// Menu that shows up at the beginning of the program.
void Main_Menu()
{
    string Command;
    Customer customer;
    string Email;
    string Name = "";
    string Password;
    string Address;

    cout << "___________________________________________________________\n";
    cout << "\nAmalon Home Menu\n\nEnter 1 to create an account.\nEnter 2 to sign in to your account.\nEnter 3 to exit the app.\n";
    cout << "___________________________________________________________\n";
    getline(std::cin, Command);

    // Creating the user's account and putting the customer information in the customer class. Done
    if (Command == "1")
    {
        if (!Signed_In())
        {

            cout << "___________________________________________________________\n";
            cout << "What's your name?\n";
            getline(std::cin, Name);
            customer.Name = Name;
            cout << "___________________________________________________________\n";

            cout << "Nice to meet you " << Name << ", what would you like your signin email to be?\n";
            getline(std::cin, Email);
            customer.Email = Email;

            bool Invalid = !Contains(Email, "@") || Email.find("@") == 0 || Email.find("@") == Email.length() || !Contains(Email, ".") || Email.find(".") < Email.find("@") || Email.find(".") >= Email.length() - 1;
            while (Invalid || Customer_Exists(Email))
            {
                if (Invalid)
                    cout << "That email doesn't look correct, please enter an email with a correct format.\n";
                else
                    cout << "There's already an account with that email. Enter another one or go back to signin by entering #.\n";

                getline(std::cin, Email);
                if (Email == "#")
                {
                    Main_Menu();
                }

                Invalid = !Contains(Email, "@") || Email.find("@") == 0 || Email.find("@") == Email.length() || !Contains(Email, ".") || Email.find(".") < Email.find("@") || Email.find(".") >= Email.length() - 1;
            }




            customer.Email = Email;


            cout << "___________________________________________________________\n";

            cout << "What would you like your password to be? Please enter a password with at least 10 characters, a letter, and a number.\n";
            getline(std::cin, Password);
            customer.Password = Password;

            while (Password.length() < 10 || !String_Has_Letter_And_Number(Password, 4, 4))
            {
                cout << "Please enter a password with at least 10 characters, 4 letters, and 4 numbers.\n";
                getline(std::cin, Password);
                customer.Password = Password;
            }

            cout << "___________________________________________________________\n";

            cout << "What address would you like your orders to be delivered to?\n Please enter all relevant info such as State,Street,Unit,Zipcode, etc.\n";
            getline(std::cin, Address);
            customer.Address = Address;
            cout << "___________________________________________________________\n";

            string Name_On_Card, Expiration_Date, Number, CVV;

            cout << "Let's enter credit/debit details now.\n What's the name on your card\n";

            getline(std::cin, Name_On_Card);
            cout << "___________________________________________________________\n";

            cout << "What's the expiration date on your card? Enter in #/#/# format\n";
            getline(std::cin, Expiration_Date);

            cout << "___________________________________________________________\n";

            cout << "What's the number on your card?\n";

            while (Number.length() < 14 || Number.length() > 20 || !Is_Number(Number))
            {
                cout << "Your card number should be between 14 - 20 digits long.\n";
                getline(std::cin, Number);
            }
            cout << "___________________________________________________________\n";

            cout << "What's the CVV on your card\n";

            while (CVV.length() != 3 || !Is_Number(CVV))
            {
                cout << "Your card CVV should be at 3 digits long.\n";
                getline(std::cin, CVV);
            }
            cout << "___________________________________________________________\n";


            customer.card = Card(Name_On_Card, stoull(Number), stoi(CVV), Expiration_Date);

            if (Signup(Email, customer))
            {
                Save();
                Current_Menu = Sign_In_Menu;
                Sign_In_Menu();
                return;
            }
        }
        else cout << "You're already signed in.";
    }
    // Signing the user into their account. Done
    else if (Command == "2")
    {
        if (!Signed_In())
        {
            cout << "Let's get you signed in, what's your email?\n";
            getline(std::cin, Email);
            customer.Email = Email;
            while (!Customer_Exists(Email))
            {
                cout << "That email doesn't exist, please enter a valid email or go back to the start menu by entering #.\n";
                getline(std::cin, Email);
                if (Email == "#")
                    Current_Menu();
                else
                    customer.Email = Email;
            }
            cout << "___________________________________________________________\n";

            cout << "What's your password?\n";
            getline(std::cin, Password);

            while (!Signin(Email, Password))
            {
                cout << "That password is incorrect, try again or enter # to go back to the start menu.\n";
                getline(std::cin, Password);
                if (Password == "#")
                    Main_Menu();
            }
            cout << "___________________________________________________________\n";
            cout << "\nWelcome back " << Customers[Current_Email].Name << "!\n";
            Current_Menu = Sign_In_Menu;
            Sign_In_Menu();
            return;
        }
        else cout << "You're already signed in.\n";
    }
    //  User is exiting the program. Done
    else if (Command == "3")
    {
        cout << "________________________________________________________________________________________________________________________\n";
        cout << "Thanks for visiting Amalon, have a wonderful day!";
        exit(3);
    }
    else if (Current_Menu == Main_Menu)
        Current_Menu();
}



int main()
{
    Load();
    cout << "Welcome to Amalon, the off-brand Amazon.\n";
    cout << "For support call 1-800-Definitely-Not-A-Scam or email support@amalon-is-not-a-scam.com.\n";
    Current_Menu(); // Brings up the log in menu.
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging Sign_In_Menu
// Debug program: F5 or Debug > Start Debugging Sign_In_Menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
