#include<iostream>
#include<string>
#include <ctime>
#include<iomanip>
#include<cstdlib>
#include <io.h>
#include <fcntl.h>

#define SPADE L"\u2660"
#define CLUB L"\u2663"
#define HEART L"\u2665"
#define DIAMOND L"\u2666"

using namespace std;

void printSuit(int suitToSelect)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    if (suitToSelect == 1)
        wcout << "\033[30;47m" << SPADE << "\033[0m";
    else if (suitToSelect == 2)
        wcout << "\033[30;47m" << CLUB << "\033[0m";
    else if (suitToSelect == 3)
        wcout << "\033[31;47m" << HEART << "\033[0m";
    else if (suitToSelect == 4)
        wcout << "\033[31;47m" << DIAMOND << "\033[0m";

    _setmode(_fileno(stdout), _O_TEXT);

}

template<class T>
class List
{
private:
    class Node
    {
    public:
        T data;
        Node* next;
        Node* prev;
        Node()
        {
            data = T();
            next = nullptr;
            prev = nullptr;
        }
        Node(T d, Node* _next, Node* _prev)
        {
            data = d;
            next = _next;
            prev = _prev;
        }
        Node(T d)
        {
            data = d;
            next = nullptr;
            prev = nullptr;
        }
    };

    Node* head = NULL;
    Node* tail = NULL;
    int size;

public:
    class Iterator
    {

        friend class List;
        Node* current;

        Iterator(Node* p)
        {
            current = p;
        }
    public:
        Iterator()
        {
            current = nullptr;
        }
        T& operator*() const
        {
            return current->data;
        }
        Iterator& operator++()
        {
            current = current->next;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator old = *this;
            current = current->next;
            return old;
        }
        Iterator& operator--()
        {
            current = current->prev;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator old = *this;
            current = current->prev;
            return old;
        }

        bool operator!=(const Iterator& rhs) const
        {
            return current != rhs.current;
        }
        bool operator==(const Iterator& rhs) const
        {
            return current == rhs.current;
        }
        typename Node* getNode() const
        {
            return current;
        }

    };

    List() {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
        size = 0;
    }
    
    int getSize()
    {
        return size;
    }
    void insertathead(T  value)
    {
        Node* newNode = new Node(value, head->next, head);
        newNode->prev->next = newNode;
        newNode->next->prev = newNode;
        size++;
    }
    void takeandplacebwlistandstack(List<T>* L)
    {

        size--;
        Node* temp = tail->prev;
        temp->prev->next = tail;
        tail->prev = temp->prev;

        Node* temp2 = L->head->next;
        L->head->next = temp;
        temp->next = temp2;
        if (temp2 != nullptr)
        {
            temp2->prev = temp;
        }
        temp->prev = L->head;


        L->size++;
    }


    void takeandplacebwstackandlist(List<T>* L)
    {
        if (head->next == nullptr)
        {
            return;
        }


        size--;
        Node* temp = head->next;

        head->next = temp->next;
        if (temp->next != nullptr)
        {
            temp->next->prev = head;
        }


        Node* temp2 = L->tail->prev;
        if (temp2 == nullptr) {
            return;
        }

        temp2->next = temp;
        temp->prev = temp2;
        temp->next = L->tail;
        L->tail->prev = temp;

        L->size++;
    }

    void takeandplacebwstacks(List<T>* L)
    {

        if (head->next == nullptr)
        {
            return;
        }
        size--;
        Node* temp = head->next;

        head->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = head;
        }


        Node* temp2 = L->head->next;
        L->head->next = temp;
        temp->next = temp2;
        if (temp2 != nullptr) {
            temp2->prev = temp;
        }
        temp->prev = L->head;
        L->size++;
    }

    void insertAtEnd(T  value)
    {
        Node* newNode = new Node(value, tail, tail->prev);
        tail->prev = newNode;
        newNode->prev->next = newNode;
        size++;
    }
    bool isempty()
    {
        return (size == 0);
    }
    Iterator begin() const
    {
        return Iterator(head->next);
    }

    Iterator end() const
    {
        return Iterator(tail);
    }

    void deleteathead()
    {
        if (size == 0)
        {
            cout << "List is empty. Cannot delete element.\n";
            return;
        }

        Node* toDelete = head->next;
        head->next = toDelete->next;
        toDelete->next->prev = head;
        delete toDelete;
        size--;
    }

    void deleteAtTail()
    {
        if (size == 0)
        {
            cout << "List is empty. Cannot delete element.\n";
            return;
        }

        Node* toDelete = tail->prev;
        tail->prev = toDelete->prev;
        toDelete->prev->next = tail;
        delete toDelete;
        size--;
    }


    void moveSubList(Iterator cutStart, Iterator cutEnd, List<T>& destList, int numOfCards)
    {

        if (cutStart == end() || cutEnd == end())
        {
            return;
        }


        Node* cutStartNode = cutStart.getNode();
        Node* cutEndNode = cutEnd.getNode();

        if (cutStartNode->prev != head)
        {
            cutStartNode->prev->next = cutEndNode->next;
        }
        else {

            head->next = cutEndNode->next;
        }


        if (cutEndNode->next)
        {
            cutEndNode->next->prev = cutStartNode->prev;
        }
        else
        {

            tail->prev = cutStartNode->prev;
        }

        Node* destTailPrev = destList.tail->prev;
        if (destTailPrev)
        {
            destTailPrev->next = cutStartNode;
            cutStartNode->prev = destTailPrev;
        }


        cutEndNode->next = destList.tail;
        destList.tail->prev = cutEndNode;



        size -= numOfCards;
        destList.size += numOfCards;
    }

    T gotheaddata()
    {

        return head->next->data;

    }
    Node* gothead()
    {
        return head->next;
    }

    ~List()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

template<class T>
class Stack
{
    List<T>s;
    int size;
public:
    Stack()
    {
        size = 0;
    }
    int getSize()
    {
        return s.getSize();
    }
    void push(T d)
    {

        s.insertathead(d);
        size++;
    }


    bool pop(T& d)
    {
        if (!isempty())
        {
            size--;
            d = s.gotheaddata();
            s.deleteathead();
            return true;
        }
        return false;
    }

    bool isempty()
    {
        return (s.getSize() == 0);
    }
    bool top(T& d)
    {
        if (!isempty())
        {
            d = s.gotheaddata();

            return true;
        }
        return false;
    }
    void popandpush(Stack<T>* w)
    {
        s.takeandplacebwstacks(&w->s);

    }

    void popandpush(List<T>* C)
    {

        s.takeandplacebwstackandlist(C);
    }
    List<T>* getList()
    {
        return &s;
    }

};

class Card
{
public:
    bool ishidden;
    string suit;
    string rank;

    Card(string s, string r)
    {
        suit = s;
        rank = r;
        ishidden = true;

    }
    Card()
    {
        suit = " ";
        rank = " ";
        ishidden = true;
    }
    bool checkIfHidden()
    {
        return ishidden;
    }
    void revealCard()
    {
        ishidden = false;
    }

    int convertRankToInt()
    {
        if (rank == "A") return 1;
        if (rank == "J") return 11;
        if (rank == "Q") return 12;
        if (rank == "K") return 13;


        return stoi(rank);
    }
    void displayCard1() const
    {


        if (this != nullptr)
        {


            if (!ishidden) {
                char s = suit[0];
                if (s == 'S')
                {
                    cout << " " << setw(7) << "\033[30;47m" << rank << "\033[0m";
                    printSuit(1);
                }
                else if (s == 'C')
                {
                    cout << " " << setw(7) << "\033[30;47m" << rank << "\033[0m";
                    printSuit(2);
                }
                else if (s == 'H')
                {
                    cout << " " << setw(7) << "\033[31;47m" << rank << "\033[0m";
                    printSuit(3);
                }
                else
                {
                    cout << " " << setw(7) << "\033[31;47m" << rank << "\033[0m";
                    printSuit(4);
                }
            }
            else
            {
                cout << " " << setw(7) << "\033[30;47m" << "[]" << "\033[0m";

            }
        }

        else
        {
            cout << " " << setw(7) << "\033[30;47m" << "[]" << "\033[0m";

        }


    }
    bool operator==(Card* other) const
    {
        return (this->rank == (*other).rank && this->suit == (*other).suit);
    }
    bool isOppositeColor(const Card* other) const
    {
        return (isRed() && (*other).isBlack()) || (isBlack() && (*other).isRed());
    }

    bool isSameSuit(const Card* other)
    {
        return (this->suit == (*other).suit);
    }
    bool isRed() const
    {
        return (suit == "H" || suit == "D");
    }


    bool isBlack() const
    {
        return (suit == "S" || suit == "C");
    }




};
class Command
{
private:
    int MoveFrom;
    int MoveTo;
    int numOfCards;
    char operand1;
    char operand2;
    char mainCommand;
    bool wasCardRevealed;

public:

    Command()
    {

        MoveFrom = 0;
        MoveTo = 0;
        numOfCards = 0;
        mainCommand = 0;
        operand1 = ' ';
        operand2 = ' ';
        wasCardRevealed = false;
    }

    void StoreCommand(char maincmd, int from = 0, int to = 0, int num = 0, char op1 = 0, char op2 = 0, bool revealed = false)
    {
        MoveFrom = from;
        MoveTo = to;
        numOfCards = num;
        mainCommand = maincmd;
        operand1 = op1;
        operand2 = op2;
        wasCardRevealed = revealed;
    }

    int getMoveFrom() const
    {
        return MoveFrom;
    }
    int getMoveTo() const
    {
        return MoveTo;
    }
    int getNumOfCards() const
    {
        return numOfCards;
    }
    char getCommand() const
    {
        return mainCommand;
    }
    char getOperand1() const
    {
        return operand1;
    }
    char getOperand2() const
    {
        return operand2;
    }
    bool getWasCardRevealed() const
    {
        return wasCardRevealed;
    }
    void setWasCardRevealed(bool revealed)
    {
        wasCardRevealed = revealed;
    }

};
class Game
{
    List<Card*> tableau[7];
    Stack<Card*> stock;
    Stack<Card*> waste;
    Stack<Card*> foundation[4];
    Stack<Command> commandStack;
    List<Card*> deck;
    string Invalid;

public:
    Game()
    {
        initializeDeck();
        shuffleDeck();
        initializeGame();
        Invalid = "0";
    }

    void initializeGame()
    {

        List<Card*>::Iterator it = deck.begin();
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j <= i; j++)
            {

                Card* currentCard = *it;

                if (j == i)
                {
                    currentCard->revealCard();
                }

                tableau[i].insertAtEnd(currentCard);

                ++it;

            }
        }



        while (it != deck.end())
        {
            Card* currentCard = *it;
            currentCard->revealCard();
            stock.push(currentCard);
            ++it;
        }
    }
    void initializeDeck()
    {
        string suits[] = { "H", "S", "C", "D" };
        string ranks[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

        for (int s = 0; s < 4; s++)
        {
            for (int r = 0; r < 13; r++)
            {
                Card* newCard = new Card(suits[s], ranks[r]);
                deck.insertAtEnd(newCard);
            }
        }
    }
    void shuffleDeck()
    {
        srand(time(0));
        for (int i = 0; i < 52; i++)
        {
            int randIdx = rand() % 52;
            swapCards(i, randIdx);
        }
    }
    void swapCards(int idx1, int idx2)
    {
        List<Card*>::Iterator it1 = deck.begin();
        List<Card*>::Iterator it2 = deck.begin();

        for (int i = 0; i < idx1; ++i, it1++);
        {
            for (int i = 0; i < idx2; ++i, it2++);
            {
                Card* temp = *it1;
                *it1 = *it2;
                *it2 = temp;
            }
        }
    }

    bool placeOnFoundation(Card* card, int foundationIndex)
    {

        if (foundationIndex < 0 || foundationIndex >= 4)
        {
            Invalid = "Invalid foundation index.";
            return false;
        }

        if (foundation[foundationIndex].isempty())
        {

            if ((*card).rank == "A")
            {
                return true;
            }
            else
            {
                Invalid = "Only an Ace can start a new foundation.";
                return false;
            }
        }
        else
        {

            Card* topCard;
            foundation[foundationIndex].top(topCard);
            if (topCard == nullptr)
            {
                Invalid = "Top card is null. Cannot place card.";
                return false;
            }

            if ((*card).suit != (*topCard).suit)
            {
                Invalid = "Invalid move: card must match the same suit.";
                return false;
            }
            int cardRankValue = (*card).convertRankToInt();
            int topCardRankValue = (*topCard).convertRankToInt();

            if (cardRankValue == topCardRankValue + 1)
            {

                return true;
            }
            else
            {

                Invalid = "Invalid move: card cannot be placed on top of the foundation card.";

                return false;
            }
        }
    }
    bool moveFoundationToColumn(int foundationIndex, int colIndex)
    {

        if (foundationIndex < 0 || foundationIndex >= 4)
        {
            Invalid = "Invalid foundation index.";
            return false;
        }


        if (colIndex < 0 || colIndex >= 7)
        {
            Invalid = "Invalid column index.";
            return false;
        }


        if (foundation[foundationIndex].isempty())
        {
            Invalid = "Foundation is empty.";
            return false;
        }


        Card* topCard;
        foundation[foundationIndex].top(topCard);


        if (tableau[colIndex].isempty())
        {

            if ((*topCard).rank != "K")
            {
                Invalid = "Only a King can be placed on an empty column.";
                return false;
            }
        }
        else
        {
            List<Card*>::Iterator it = tableau[colIndex].end();
            --it;

            Card* targetCard = *it;

            if (!canPlaceOnColumn(topCard, targetCard))
            {
                Invalid = "Invalid move: cannot place card on the column.";
                return false;
            }
        }
        foundation[foundationIndex].popandpush(&tableau[colIndex]);
        return true;
    }
    bool canPlaceOnColumn(Card*& movingCard, Card*& targetCard)
    {

        if (!(*movingCard).isOppositeColor(targetCard) && (*movingCard).checkIfHidden() == true && (*targetCard).checkIfHidden() == true)
        {
            return false;
        }

        int movingCardRank = (*movingCard).convertRankToInt();
        int targetCardRank = (*targetCard).convertRankToInt();


        if (movingCardRank == targetCardRank - 1)
        {
            return true;
        }

        return false;
    }
    bool moveWasteToColumn(int colIndex)
    {
        if (waste.isempty())
        {
            Invalid = "Wastepile is empty.";
            return false;
        }

        Card* topCard;
        waste.top(topCard);

        List<Card*>::Iterator it = tableau[colIndex].end();
        --it;

        Card* topColCard = *it;
        if (!tableau[colIndex].isempty())
        {

            if (!canPlaceOnColumn(topCard, topColCard))
            {
                Invalid = "Invalid move: cannot place card on the column.";
                return false;
            }
        }
        else if ((*topCard).rank != "K")
        {
            Invalid = "Only a King can be placed on an empty column.";
            return false;
        }
        waste.popandpush(&tableau[colIndex]);

        return true;
    }
    void displayGame()
    {
        Card* topCard;

        cout << "\033[3;34m" << "Stockpile" << "   " << "Wastepile" << "\t\t\t\t" << "Foundation 1" << "\t\t" << "Foundation 2" << "\t\t" << "Foundation 3" << "\t\t" << "Foundation 4" << "\033[0m" << endl;
        if (!stock.isempty())
        {
            cout << "\033[3;34m" << "  [   ] " << "\033[0m";
        }
        else
        {
            cout << "\033[3;34m" << "  Empty " << "\033[0m";
        }

        if (!waste.isempty())
        {
            cout << "  ";
            waste.top(topCard);
            cout << setw(5);
            (*topCard).displayCard1();
            cout << "   ";
        }
        else
        {
            cout << "   ";
            cout << "\033[3;34m" << "   Empty " << "\033[0m";
        }
        cout << "\t\t\t\t ";
        for (int i = 0; i < 4; ++i)
        {
            if (!foundation[i].isempty())
            {
                foundation[i].top(topCard);

                (*topCard).displayCard1();
                cout << setw(10);
                cout << "\t\t ";
            }
            else
            {
                cout << "\033[3;34m" << " empty" << "\033[0m" << "\t\t\t ";
            }
        }

        cout << "\033[3;34m" << "\n(" << stock.getSize() << " cards)  (" << waste.getSize() << " cards)" << "\033[0m";
        cout << "\t\t\t  ";

        for (int i = 0; i < 4; ++i)
        {
            cout << "\033[3;34m" << setw(7) << "(" << foundation[i].getSize() << " cards)" << "\033[0m" << setw(16);
        }


        cout << "\n\n\n\n\n\t";
        for (int i = 0; i < 7; i++)
        {
            cout << setw(15) << "\033[3;34m" << "Column " << i + 1 << "\033[0m";

        }
        cout << endl << endl;
        cout << "\t";
        for (int i = 0; i < 7; i++)
        {
            cout << "\033[3;34m" << setw(8) << "(" << tableau[i].getSize() << " cards)" << "\033[0m";
        }


        List<Card*>::Iterator it[7];
        for (int i = 0; i < 7; i++)
        {
            it[i] = tableau[i].begin();
        }

        cout << endl << endl << endl;
        while (it[0] != tableau[0].end() || it[1] != tableau[1].end() || it[2] != tableau[2].end() ||
            it[3] != tableau[3].end() || it[4] != tableau[4].end() || it[5] != tableau[5].end() ||
            it[6] != tableau[6].end())
        {

            cout << "\t\t  ";
            for (int i = 0; i < 7; i++)
            {

                if (it[i] != tableau[i].end())
                {


                    (**it[i]).displayCard1();

                    it[i]++;
                }
                else
                {
                    cout << "     ";
                }

                cout << "\t\t";

            }
            cout << endl << endl;

        }
        if (Invalid != "0")
        {
            cout << "\n\n" << Invalid << "\n\n";


            Invalid = "0";
        }
    }
    bool drawFromStockpile()
    {

        if (stock.isempty() && waste.isempty())
        {
            Invalid = "STOCKPILE AND WASTEPILE ARE EMPTY";
            return false;
        }
        if (!stock.isempty())
        {
            stock.popandpush(&waste);

        }
        else
        {
            while (!waste.isempty())
            {

                waste.popandpush(&stock);

            }

            stock.popandpush(&waste);

        }
        return true;
    }

    bool moveCardFromColToFoundation(int fromCol, int foundationIndex)
    {

        bool revealed = false;
        if (fromCol < 0 || fromCol >= 7 || foundationIndex < 0 || foundationIndex >= 4)
        {
            Invalid = "Invalid column or foundation index.";
            return false;
        }

        if (tableau[fromCol].isempty())
        {
            Invalid = "Column is empty. Cannot move card.";
            return false;
        }


        List<Card*>::Iterator it = tableau[fromCol].end();
        --it;
        Card* topCard = *it;

        if (placeOnFoundation(topCard, foundationIndex))
        {

            tableau[fromCol].takeandplacebwlistandstack(foundation[foundationIndex].getList());
            if (!tableau[fromCol].isempty())
            {
                List<Card*>::Iterator lastCardInFromCol = tableau[fromCol].end();
                --lastCardInFromCol;
                Card* lastCard = *lastCardInFromCol;
                if ((*lastCard).checkIfHidden())
                {
                    (*lastCard).revealCard();
                    revealed = true;
                }
            }
            Command cmd;
            cmd.StoreCommand('m', fromCol, foundationIndex, 1, 'c', 'f', revealed);
            commandStack.push(cmd);
            return true;
        }

        return false;
    }

    bool moveWasteToFoundation(int foundationIndex)
    {
        if (waste.isempty())
        {
            Invalid = "Wastepile is empty.";
            return false;
        }

        Card* topCard;
        waste.top(topCard);
        if (placeOnFoundation(topCard, foundationIndex))
        {
            waste.popandpush(&foundation[foundationIndex]);

            return true;
        }
        return false;
    }
    bool moveCardFromColToCol(int fromCol, int toCol, int numCards)
    {
        bool revealed = false;

        if (fromCol < 0 || fromCol >= 7 || toCol < 0 || toCol >= 7)
        {
            Invalid = "Invalid column index.";
            return false;
        }


        if (tableau[fromCol].isempty() || tableau[fromCol].getSize() < numCards)
        {
            Invalid = "Not enough cards in the source column.";
            return false;
        }


        List<Card*>::Iterator endIt = tableau[fromCol].end();
        --endIt;


        List<Card*>::Iterator startIt = tableau[fromCol].end();
        for (int i = 0; i < numCards; i++)
        {

            --startIt;
        }

        if (!tableau[toCol].isempty())
        {
            List<Card*>::Iterator targetIt = tableau[toCol].end();
            --targetIt;
            Card* targetCard = *targetIt;


            if (!canPlaceOnColumn(*startIt, targetCard))
            {
                Invalid = "Invalid move: cannot place card on the target column.";
                return false;
            }
        }
        else if ((**startIt).rank != "K")
        {
            Invalid = "Only a King can be placed on an empty column.";
            return false;
        }


        tableau[fromCol].moveSubList(startIt, endIt, tableau[toCol], numCards);
        if (!tableau[fromCol].isempty())
        {
            List<Card*>::Iterator lastCardInFromCol = tableau[fromCol].end();
            --lastCardInFromCol;
            Card* lastCard = *lastCardInFromCol;
            if ((*lastCard).checkIfHidden())
            {
                (*lastCard).revealCard();
                revealed = true;
            }
        }
        Command cmd;
        cmd.StoreCommand('m', fromCol, toCol, numCards, 'c', 'c', revealed);
        commandStack.push(cmd);

        return true;
    }
    void getInputFromUser()
    {
        string comm;
        Command cmd;
        int coltomovefrom = 0;
        int coltomoveto = 0;
        int foundationIndex = 0;
        int numofcards = 0;
        char mainCommand;
        char op1;
        char op2;
        cout << "\nEnter Command:";
        getline(cin, comm);
        mainCommand = comm[0];
        if (mainCommand == 's' || mainCommand == 'S')
        {
            if (drawFromStockpile())
            {
                cmd.StoreCommand(mainCommand);
                commandStack.push(cmd);
            }

        }
        else if (mainCommand == 'm' || mainCommand == 'M')
        {
            op1 = comm[2];
            if (op1 == 'c' || op1 == 'C')
            {
                coltomovefrom = comm[3] - '0' - 1;
                op2 = comm[5];
                if (op2 == 'c' || op2 == 'C')            
                {
                    coltomoveto = comm[6] - '0' - 1;
                    numofcards = comm[8] - '0';
                    moveCardFromColToCol(coltomovefrom, coltomoveto, numofcards);

                }
                else if (op2 == 'f' || op2 == 'F')
                {
                    foundationIndex = comm[6] - '0' - 1;
                    numofcards = comm[8] - '0';
                    if (numofcards != 1)
                    {

                        Invalid = "Only one card can be move to foundation";
                        return;
                    }
                    moveCardFromColToFoundation(coltomovefrom, foundationIndex);


                }
                else
                {
                    Invalid = "Invalid Input!";
                    return;
                }
            }
            else if (op1 == 'w' || op1 == 'W')
            {
                op2 = comm[4];
                if (op2 == 'f' || op2 == 'F')
                {
                    foundationIndex = comm[5] - '0' - 1;
                    numofcards = comm[7] - '0';
                    if (numofcards != 1)
                    {
                        Invalid = "Only one card can be move to foundation";
                        return;
                    }

                    if (moveWasteToFoundation(foundationIndex))
                    {
                        cmd.StoreCommand(mainCommand, 0, foundationIndex, numofcards, op1, op2);
                        commandStack.push(cmd);

                    }
                    else
                    {
                        Invalid = "Cannot place card on the foundation.";
                        return;
                    }
                }
                else if (op2 == 'c' || op2 == 'C')
                {
                    coltomoveto = comm[5] - '0' - 1;
                    numofcards = comm[7] - '0';
                    if (numofcards != 1)
                    {
                        Invalid = "Only one card can be move from wastepile to column";
                        return;
                    }
                    if (moveWasteToColumn(coltomoveto))
                    {
                        cmd.StoreCommand(mainCommand, 0, coltomoveto, numofcards, op1, op2);
                        commandStack.push(cmd);
                    }



                }
                else
                {
                    Invalid = "Invalid Input!";
                    return;
                }

            }
            else if (op1 == 'f' || op1 == 'F')
            {
                foundationIndex = comm[3] - '0' - 1;
                op2 = comm[5];
                if (op2 == 'c' || op2 == 'C')
                {

                    coltomoveto = comm[6] - '0' - 1;
                    numofcards = comm[8] - '0';
                    if (numofcards != 1)
                    {
                        Invalid = "Only one card can be move from foundation to column";
                        return;
                    }
                    if (moveFoundationToColumn(foundationIndex, coltomoveto))
                    {
                        cmd.StoreCommand(mainCommand, foundationIndex, coltomoveto, numofcards, op1, op2);
                        commandStack.push(cmd);
                    }



                }
                else
                {
                    Invalid = "Invalid Input!";
                    return;
                }

            }
            else
            {
                Invalid = "Invalid Input!";
                return;
            }
        }
        else if (mainCommand == 'z' || mainCommand == 'Z')
        {
            undoLastCommand();
        }
        else
        {
            Invalid = "Invalid Input!";
            return;
        }
    }
    void undoLastCommand()
    {
        if (commandStack.isempty())
        {
            Invalid = "No commands to undo.";
            return;
        }
        Command cmd;
        commandStack.pop(cmd);
        int movefrom = cmd.getMoveFrom();
        int moveto = cmd.getMoveTo();
        int numofcards = cmd.getNumOfCards();
        char mainCommand = cmd.getCommand();
        char op1 = cmd.getOperand1();
        char op2 = cmd.getOperand2();
        bool wasCardRevealed = cmd.getWasCardRevealed();
        if (mainCommand == 's' || mainCommand == 'S')
        {

            if (!waste.isempty())
            {
                waste.popandpush(&stock);

            }
            else
            {
                while (!stock.isempty())
                {
                    stock.popandpush(&waste);
                }

                waste.popandpush(&stock);
            }

            return;

        }
        else if (mainCommand == 'm' || mainCommand == 'M')
        {
            if (op1 == 'c' || op1 == 'C')
            {
                if (op2 == 'c' || op2 == 'C')
                {

                    List<Card*>::Iterator startIt = tableau[moveto].end();
                    --startIt;


                    List<Card*>::Iterator endIt = startIt;
                    for (int i = 1; i < numofcards; ++i)
                    {


                        --endIt;
                    }
                    if (wasCardRevealed && !tableau[movefrom].isempty())
                    {
                        List<Card*>::Iterator lastCardInCol = tableau[movefrom].end();
                        --lastCardInCol;
                        (**lastCardInCol).ishidden = true;
                    }

                    List<Card*>::Iterator targetIt = tableau[movefrom].end();
                    --targetIt;
                    Card* targetCard = *targetIt;

                    tableau[moveto].moveSubList(endIt, startIt, tableau[movefrom], numofcards);


                    return;
                }
                else if (op2 == 'f' || op2 == 'F')
                {


                    if (wasCardRevealed && !tableau[movefrom].isempty())
                    {
                        List<Card*>::Iterator lastCardInCol = tableau[movefrom].end();
                        --lastCardInCol;
                        (**lastCardInCol).ishidden = true;
                    }
                    foundation[moveto].popandpush(&tableau[movefrom]);
                    return;


                }

            }
            else if (op1 == 'w' || op1 == 'W')
            {

                if (op2 == 'f' || op2 == 'F')
                {

                    foundation[moveto].popandpush(&waste);
                    return;


                }
                else if (op2 == 'c' || op2 == 'C')
                {


                    tableau[moveto].takeandplacebwlistandstack(waste.getList());

                    return;

                }
            }
            else if (op1 == 'f' || op1 == 'F')
            {
                if (op2 == 'c' || op2 == 'C')
                {
                    tableau[moveto].takeandplacebwlistandstack(foundation[movefrom].getList());
                    return;

                }
            }

        }
    }
    bool isGameWon()
    {
        for (int i = 0; i < 4; i++)
        {
            Card* topCard;

            if (foundation[i].isempty())
            {
                return false;
            }

            foundation[i].top(topCard);


            if (topCard == nullptr || (*topCard).rank != "K")
            {
                return false;
            }
        }

        Invalid = "Congratulations! You have won the game!";
        return true;
    }

};

int main()
{
    Game game;
    while (1)
    {

        system("cls");

        game.displayGame();
        game.getInputFromUser();


        if (game.isGameWon())
        {
            system("cls");
            game.displayGame();

            break;
        }
    }

    return 0;
}
