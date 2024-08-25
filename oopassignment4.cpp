#include <iostream>
#include <string>
using namespace std;

class Item {
protected:
    int itemID;
    string title;
    bool availability;
public:
    Item(int id, string t, bool avail)
    {
        itemID = id;
        title = t;
        availability = avail;
    }
    virtual void getItemDetails() = 0;
    virtual bool checkAvailability() = 0;
    virtual void checkOut() = 0;
    virtual void checkIn() = 0;
    int getItemID()
    { 
        return itemID;
    }
    string getTitle() 
    {
        return title;
    }
};

class Book : public Item {
private:
    string author;
    string ISBN;
public:
    Book(int id, string t, bool avail, string auth, string isbn) : Item(id, t,avail)
    {
        author = auth;
        ISBN = isbn;
    }
    void getItemDetails() override 
    {
        cout << "Book ID: " << itemID << endl;
        cout << "BOok title: " << title << endl;
        cout << "Book availibility: " << availability << endl;
        cout << "Author of the book: " << author << endl;
        cout << "ISBN number: " << ISBN << endl << endl;

    }
    bool checkAvailability() override 
    {
        return availability;
    }
    void checkOut() override 
    {
        if (availability)
        {
            availability = false;
            cout << "Checked out: " << title << endl;
        }
        else {
            cout << "Book is not available." << endl;
        }
    }
    void checkIn() override
    {
        availability = true;
        cout << "Checked in: " << title << endl;
    }
};
class Journal : public Item {
private:
    string publisher;
    int issueNumber;
public:
    Journal(int id, string t, bool avail, string pub, int issue) : Item(id, t, avail)
    {
        publisher = pub;
        issueNumber = issue;
    }
    void getItemDetails() override
    {
        cout << "Journal ID: " << itemID << endl;
        cout << "Title: " << title << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "Issue Number: " << issueNumber << endl << endl;
    }
    bool checkAvailability() override 
    {
        return availability;
    }
    void checkOut() override
    {
        if (availability)
        {
            availability = false;
            cout << "Checked out: " << title << endl;
        }
        else 
        {
            cout << "Journal is not available." << endl;
        }
    }
    void checkIn() override 
    {
        availability = true;
        cout << "Checked in: " << title << endl;
    }
};
class Member
{
private:
    int memberID;
    string name;
    string contactInfo;
    int loanLimit;
    Item* borrowedItems[10];  // Fixed-size array for borrowed items
    int itemCount;  // Track the number of borrowed items

public:
    string getName()
    {
        return name; 
    }
    Member(int id, string n, string contact, int limit)
    {
        memberID = id;
        name = n;
        contactInfo = contact;
        loanLimit = limit;
        itemCount = 0;

        for (int i = 0; i < 10; ++i) 
        {
            borrowedItems[i];
        }
    }
    void borrowItem(Item& item) 
    {
        if (itemCount < loanLimit) //checks if the borrowed items are less than the borrow limit
        {
            if (item.checkAvailability())
            {
                item.checkOut();
                borrowedItems[itemCount++] = &item;
                cout << name << " has borrowed " << item.getTitle() << endl << endl;
            }
            else 
            {
                cout << item.getTitle() << " is not available for borrowing." << endl << endl;
            }
        }
        else {
            cout << name << " has reached the loan limit." << endl << endl;
        }
    }
    void returnItem(Item& item)
    {
        for (int i = 0; i < itemCount; ++i)
        {
            if (borrowedItems[i] == &item)
            {
                item.checkIn();
                borrowedItems[i] = borrowedItems[itemCount - 1];  // Replaces with last item
                borrowedItems[itemCount - 1] = nullptr;
                itemCount--;
                cout << name << " has returned " << item.getTitle() << endl << endl;
                return;
            }
        }
        cout << item.getTitle() << " was not borrowed by " << name << endl << endl;
    }
    void getLoanHistory() 
    {
        cout << name << " has borrowed the following items:" << endl;
        for (int i = 0; i < itemCount; ++i) 
        {
            cout << "  " << borrowedItems[i]->getTitle() << endl;
        }
    }
};
class Loan 
{
private:
    int loanID;
    Item* loanedItem;
    Member* borrowingMember;
    string dueDate;
    string returnDate;
    const double finePerDay = 2;  // we will keep the fine 2 per due date

public:
    Loan(int id, Item* item, Member* member, string due, string returnD)
    {
        loanID = id;
        loanedItem = item;
        borrowingMember = member;
        dueDate = due;
        returnDate = returnD;
    }
    void setReturnDate(string date) 
    {
        returnDate = date;
    }

    double calculateFine()
    {
        if (returnDate > dueDate)
        {
                return finePerDay;
        
        }
        return 0.0;
    }

    void displayLoanDetails() 
    {
        cout << "Loan ID: " << loanID << endl;
        cout << "Item: " << loanedItem->getTitle() << endl;
        cout << "Borrower: " << borrowingMember->getName() << endl;
        cout << "Due Date: " << dueDate << endl;
        cout << "Return Date: " << (returnDate.empty() ? "Not returned yet" : returnDate) << endl;
        if (!returnDate.empty()) {
            cout << "Fine: $" << calculateFine() << endl << endl;
        }
    }
};

int main() {
    Book book1(101, "OOP", true, "abdullah tariq", "123456662");
    book1.getItemDetails();
    book1.checkOut();
    book1.checkIn();
    Journal journal1(201, "OOP Journal", true, "publish", 55);
    journal1.getItemDetails();
    journal1.checkOut();
    journal1.checkIn();
    Member member1(1, "abdullah tariq", "abdullahtariq@gmail.com", 5);

    member1.borrowItem(book1);
    member1.getLoanHistory();
    member1.returnItem(book1);
    member1.getLoanHistory();

    Loan loan1(420, &book1, &member1, "2024-08-20", "");
    loan1.displayLoanDetails();

   
    loan1.setReturnDate("2024-08-25");
    loan1.displayLoanDetails();

    return 0;
}
