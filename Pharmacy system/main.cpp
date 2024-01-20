#include <iostream>
#include<string>
using namespace std;
class DLinkedList;
double PharmacyProfit{ 0 };
class medcine {
    //    friend ostream& operator<<(ostream& os,medcine& rhs);
private:
    string name;
    string descripttion;
    string substance;
    int price;
    int Sold_Medcine_Count;
public:
    medcine(string nameN = "noName", string descripttionN = "NA", string substanceN = "NA", int priceN = 0, int Sold_Medcine_CountN = 0) {
        name = nameN;
        price = priceN;
        substance = substanceN;
        descripttion = descripttionN;
        Sold_Medcine_Count = Sold_Medcine_CountN;
    }
    void setPriceNeg() { price *= -1; }
    void setName(string name) {
        this->name = name;
    }
    void print() {
        cout << name << " " << substance << " " << descripttion << " " << Sold_Medcine_Count << " Price: " << price << endl;
    }
    void increase_Sold_Count() {
        ++Sold_Medcine_Count;
    }
    void decrease_Sold_Count() {
        if (Sold_Medcine_Count != 0)
            --Sold_Medcine_Count;
    }
    int getSoldCount() { return Sold_Medcine_Count; }
    int getPrice() { return price; }
    friend DLinkedList;
};

struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
    medcine data;
    Node(medcine data) :data(data) {}
};
template<class t>class Stack {
private:
    struct StackNode
    {
        t item;
        StackNode* next;
    };
    StackNode* topPtr, * curPtr;
public:
    Stack() {
        topPtr = NULL;
    }
    bool isEmpty()
    {
        return topPtr == NULL;
    }
    void push(t newItem)
    {
        StackNode* newPtr = new StackNode;
        if (newPtr == NULL)
            cout << "Stack push cannot allocate memory";
        else
        {
            newPtr->item = newItem;
            newPtr->next = topPtr;
            topPtr = newPtr;
        }
    }
    void pop() {
        if (isEmpty())
            cout << "Stack empty on pop";
        else {
            StackNode* temp = topPtr;
            topPtr = topPtr->next;
            temp->next = NULL;
            delete temp;
        }
    }

    medcine& getTop()
    {
        if (isEmpty())
            cout << "stack empty on getTop";
        else
            return topPtr->item;
    }
    void display()
    {
        curPtr = topPtr;
        while (curPtr != NULL)
        {
            curPtr->item.print();
            curPtr = curPtr->next;
        }
    }

};
class DLinkedList {
private:
    Node* Head = nullptr;
    Node* Tail = nullptr;
    int length{ 0 };
public:
    int count() {
        Node* tmp = Head;
        int cnt{ 0 };
        while (tmp != Tail) {
            ++cnt;
            tmp = tmp->next;
        }
        return cnt;
    }
    void push_back(medcine item) {
        Node* new_item = new Node(item);
        if (Head == nullptr) {
            Head = Tail = new_item;
        }
        else {
            Tail->next = new_item;
            new_item->prev = Tail;
            Tail = new_item;
        }
        ++length;
    }
    void push_front(medcine item) {
        Node* new_item = new Node(item);
        if (Head == nullptr) {
            Head = Tail = new_item;
        }
        else {
            Head->prev = new_item;
            new_item->next = Head;
            Head = new_item;
        }
    }
    void insert(int poss, medcine item) {
        if (Head == nullptr) {
            push_front(item);
            return;
        }
        Node* new_node = new Node(item);
        Node* tmp = Head;
        while (tmp != nullptr && --poss) {
            tmp = tmp->next;
        }
        tmp->next->prev = new_node;
        new_node->next = tmp->next;
        new_node->prev = tmp;
        tmp->next = new_node;

    }
    void pop_back() {
        if (Tail != nullptr) {
            Node* del_node = Tail;
            Tail = Tail->prev;
            delete del_node;
            Tail->next = nullptr;
        }
    }
    void pop_front() {
        if (Head != nullptr) {
            Node* del_node = Head;
            Head = Head->next;
            delete del_node;
            Head->prev = nullptr;
        }
    }
    void erase(int poss) {
        Node* tmp = Head;
        while (tmp != nullptr && --poss)
            tmp = tmp->next;
        if (Head == tmp)
            pop_front();
        else if (tmp == Tail) {
            pop_back();
        }
        else {
            Node* del_ptr = tmp;
            Node* secNode = tmp->next;
            Node* firstNode = tmp->prev;
            firstNode->next = secNode;
            secNode->prev = firstNode;
            delete del_ptr;
        }
    }
    medcine& at(int poss) {
        if (poss >= length) {
            exit(1);
        }
        Node* tmp = Head;
        while (tmp != nullptr && poss--) {
            tmp = tmp->next;
        }
        return tmp->data;
    }

    bool search_For_Medicine(string target) {
        Node* current = Head;

        while (current != nullptr) {
            if (current->data.name == target) {
                return true;
            }
            current = current->next;
        }

        return false;
    }
    Node* search_For_Medicine_Return_Node(string target) {
        Node* current = Head;

        while (current != nullptr) {
            if (current->data.name == target) {

                return current;

            }
            current = current->next;
        }
        return nullptr;
    }
    void PrintAllMatchSubstance(string target) {
        Node* current = Head;
        while (current != nullptr) {
            if (current->data.substance == target) {
                current->data.print();
            }
            current = current->next;
        }
    }
};
DLinkedList medcine_List;
Stack<medcine>Orders;

int Choose_List() {
    cout << "1.insert A new Medcine\n"
            "2.serve peoble\n"
            "3.Sold Things\n";
    int x; cin >> x;
    return x;
}
bool insert() {
    string medecine_name;
    string descripttion;
    string substance;
    int price;
    cout << "enter medecine name"; cin >> medecine_name;
    cout << "enter medecine Substance name"; cin >> substance;
    cout << "enter Descripation:"; getline(cin, descripttion); cin.ignore(1000, '\n');
    cout << "enter price:"; cin >> price;
    if (medcine_List.search_For_Medicine(medecine_name)) { return false; }
    medcine_List.push_back(medcine{ medecine_name,descripttion,substance,price,0 });
    return true;
}
void SoldThings() {
    if (Orders.isEmpty()) {
        cout << "No thing has been sold\n";
    }
    else {
        Orders.display();
    }
}
void SearchForMedicen() {
    string MedienName;
    cout << "Enter Medicen Name to search: "; cin >> MedienName;
    Node* SearchRes = medcine_List.search_For_Medicine_Return_Node(MedienName);
    if (SearchRes == nullptr) {
        cout << "Sorry we don't  have this Medicen right now try search for substence\n";
    }
    else {
        //        cout<<MedienName<<endl;
        SearchRes->data.print();
    }
}
void SearchForMedicenSubStance() {
    string MedienName;
    cout << "Enter Medicen Name to search: "; cin >> MedienName;
    medcine_List.PrintAllMatchSubstance(MedienName);
}
void buy() {
    string medienName;
    cout << "Medicen that you want to buy:"; cin >> medienName;
    Node* SearchRes = medcine_List.search_For_Medicine_Return_Node(medienName);
    if (SearchRes == nullptr) {
        cout << "Medcine Not found" << endl;
    }
    else {
        PharmacyProfit += SearchRes->data.getPrice();
        SearchRes->data.increase_Sold_Count();
        Orders.push(SearchRes->data);
        cout << "Medine Sold successfully" << endl;
    }
}
void ReturnMedicn() {
    string MedicneName;
    cout << "Medicne Name that you want to return: "; cin >> MedicneName;
    Node* SearchRes = medcine_List.search_For_Medicine_Return_Node(MedicneName);
    if (SearchRes == nullptr) {
        cout << "Medicne name not found:" << endl;
    }
    else {
        if (SearchRes->data.getSoldCount()) {
            SearchRes->data.decrease_Sold_Count();
            PharmacyProfit -= SearchRes->data.getPrice();
            Orders.push(SearchRes->data);
            Orders.getTop().setPriceNeg();
        }
        else {
            cout << "Not sold Yet\n";
        }
    }
}
void Serve() {
    int NumOfPerson;
    cout << "Num of Person that you want to serve:"; cin >> NumOfPerson;
    while (NumOfPerson--) {
        cout << "1.Search for Medicen Name\n"
                "2.Search for Medicen substance\n"
                "3.buy midcen\n"
                "4.return midcen\n"; int ch; cin >> ch;
        switch (ch) {
            case 1:
                SearchForMedicen();
                break;
            case 2:
                SearchForMedicenSubStance();
                break;
            case 3:
                buy();
                break;
            case 4:
                ReturnMedicn();
                break;
            case 0:
                break;
            default:
                cerr << "Wrong choice";
        }
    }
}
void main_List() {
    bool IsFinished = false;
    do {
        cout<<"Profit: "<<PharmacyProfit<<endl;
        switch (Choose_List()) {
            case 0:
                IsFinished = true;
                break;
            case 1:
                insert();
                break;
            case 2:
                Serve();
                break;
            case 3:
                SoldThings();
                break;
            default:
                cerr << "Wrong choice";
        }
    } while (!IsFinished);
}
int main() {
    system("Color 01");
    main_List();
    return 0;
}