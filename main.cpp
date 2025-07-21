#include <iostream>
#include <string>
#include <functional>
#include <map>
using namespace std;

//  -----------------MAIN THING-------------------
map<string, int> addressToBalance;
//  -----------------MAIN THING-------------------

class Transaction
{
private:
    string from;
    string to;
    int amount;
    bool isOnChain;

public:
    Transaction(string _from, string _to, int _amount)
    {

        from = _from;
        to = _to;
        amount = _amount;
        isOnChain = false;
    }
    bool transfer()
    {
        if (addressToBalance[from] >= amount)
        {
            addressToBalance[from] -= amount;
            addressToBalance[to] += amount;
            isOnChain = true;
            cout << "The address: " << from << " sent: " << amount << " to: " << to << endl;

            return true;
        }
        return false;
    }

    string getFrom()
    {
        return from;
    }
    string getTo()
    {
        return to;
    }
    int getAmount()
    {
        return amount;
    }
};
class Block
{
private:
    size_t hash;
    size_t prevHash;
    string name;
    int id;
    vector<Transaction> txns;

public:
    Block(string _name, int _id, size_t _prevHash, vector<Transaction> &_txnsInProcessing)
    {
        name = _name;
        id = _id;
        prevHash = _prevHash;
        txns = _txnsInProcessing;
        hash = calculateHash(_name, _id, _prevHash, _txnsInProcessing);
    }

    size_t calculateHash(string _name, int _id, size_t _prevHash, vector<Transaction> &_txnsInProcessing)
    {
        std::hash<string> hashString;
        std::hash<int> hashInt;
        std::hash<size_t> hashSizeT;

        size_t h1 = hashString(_name);
        size_t h2 = hashInt(_id);
        size_t h3 = hashSizeT(_prevHash);

        size_t h4_to;
        size_t h4_from;
        size_t h4_amount;

        size_t h4 = 0;

        for (int i = 0; i < _txnsInProcessing.size(); i++)
        {
            h4_to = hashString(_txnsInProcessing[i].getTo());
            h4_from = hashString(_txnsInProcessing[i].getFrom());
            h4_amount = hashInt(_txnsInProcessing[i].getAmount());

            h4 ^= h4_to + 0x9e3779b9 + (h4 << 6) + (h4 >> 2);
            h4 ^= h4_from + 0x9e3779b9 + (h4 << 6) + (h4 >> 2);
            h4 ^= h4_amount + 0x9e3779b9 + (h4 << 6) + (h4 >> 2);
        }

        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }

    void showTransactions()
    {
        if (txns.empty())
        {
            cout << "  No transactions in this block." << endl;
            return;
        }

        cout << "  Transactions:" << endl;
        for (int i = 0; i < txns.size(); ++i)
        {
            cout << "    - From: " << txns[i].getFrom()
                 << " | To: " << txns[i].getTo()
                 << " | Amount: " << txns[i].getAmount() << endl;
        }
    }

    void showBlock()
    {
        cout << "Block id: " << id << " name: " << name << " hash: " << hash << " PrevHash: " << prevHash << endl;
    }
    size_t getHash()
    {
        return hash;
    }
    size_t getPrevHash()
    {
        return prevHash;
    }
};

void createBlock(string _name, int _id, vector<Block> &blockChain, vector<Transaction> &_txnsInProcessing)
{
    for (int i = 0; i < _txnsInProcessing.size(); i++)
    {
        if (!_txnsInProcessing[i].transfer())
        {
            cout << "Error, invalid trxn pusing into the chain" << endl;
        }
    }
    Block block(_name, _id, blockChain.back().getHash(), _txnsInProcessing);
    _txnsInProcessing.clear();
    blockChain.push_back(block);
}

void showBlockChain(vector<Block> &blockChain)
{
    for (int i = 0; i < blockChain.size(); i++)
    {
        cout << "========================================================================================================" << endl;
        blockChain[i].showBlock();
        blockChain[i].showTransactions();
        cout << "========================================================================================================" << endl;

        // Print chain connector unless it's the last block
        if (i != blockChain.size() - 1)
        {
            cout << "                                                  ||                                                 " << endl;
            cout << "                                                  ||                                                 " << endl;
            cout << "                                                  ||                                                 " << endl;
            cout << "                                                  ||                                                 " << endl;
        }
    }
}

bool checkBlockChain(vector<Block> &blockChain)
{

    for (int i = 0; i < blockChain.size() - 1; i++)
    {

        if (blockChain[i].getHash() != blockChain[i + 1].getPrevHash())
        {
            cout << "Mismatch at block " << i << ": "
                 << blockChain[i].getHash() << " != "
                 << blockChain[i + 1].getPrevHash() << endl;
            return false;
        }
    }

    return true;
}

void transferMoney(string _from, string _to, int _amount, vector<Transaction> &_txnsInProcessing)
{
    Transaction txn(_from, _to, _amount);
    _txnsInProcessing.push_back(txn);
}

void createAddress(string _address)
{
    addressToBalance[_address] = 0;
}

void showBalances()
{
    cout << addressToBalance["admin"] << endl;
    cout << addressToBalance["user2"] << endl;
}

int main()
{

    addressToBalance["admin"] = 1000;

    vector<Block> blockChain;
    vector<Transaction> txnsInProcessing;

    Block block1("Matvey", 1, 0, txnsInProcessing);

    blockChain.push_back(block1);

    createAddress("user2");

    transferMoney("admin", "user2", 30, txnsInProcessing);

    createBlock("Satoshi", 2, blockChain, txnsInProcessing);

    showBlockChain(blockChain);

    bool isRun = true;

    while (isRun)
    {
        int choice;
        cout << "\n============================\n";
        cout << "Select an option:\n";
        cout << "1. Create address\n";
        cout << "2. Show balances\n";
        cout << "3. Make transaction\n";
        cout << "4. Create block\n";
        cout << "5. Show blockchain\n";
        cout << "6. Check blockchain integrity\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string address;
            cout << "Enter new address name: ";
            cin >> address;
            createAddress(address);
            break;
        }
        case 2:
            showBalances();
            break;
        case 3:
        {
            string from, to;
            int amount;
            cout << "From: ";
            cin >> from;
            cout << "To: ";
            cin >> to;
            cout << "Amount: ";
            cin >> amount;
            transferMoney(from, to, amount, txnsInProcessing);
            break;
        }
        case 4:
        {
            string blockName;
            int blockId;
            cout << "Block name: ";
            cin >> blockName;
            cout << "Block id: ";
            cin >> blockId;
            createBlock(blockName, blockId, blockChain, txnsInProcessing);
            break;
        }
        case 5:
            showBlockChain(blockChain);
            break;
        case 6:
            if (checkBlockChain(blockChain))
                cout << "Blockchain is valid.\n";
            else
                cout << "Blockchain integrity check failed.\n";
            break;
        case 0:
            isRun = false;
            break;
        default:
            cout << "Invalid option.\n";
            break;
        }
    }

    return 0;
}