#include <iostream>
#include <string>
#include <functional>
using namespace std;

class Block
{
private:
    size_t hash;
    size_t prevHash;
    string name;
    int id;

public:
    Block(string _name, int _id, size_t _prevHash)
    {
        name = _name;
        id = _id;
        prevHash = _prevHash;
        hash = calculateHash(_name, _id, _prevHash);
    }

    size_t calculateHash(string _name, int _id, size_t _prevHash = 0)
    {
        std::hash<std::string> hashString;
        std::hash<int> hashInt;
        std::hash<size_t> hashSizeT;

        size_t h1 = hashString(_name);
        size_t h2 = hashInt(_id);
        size_t h3 = hashSizeT(_prevHash);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
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

void createBlock(string _name, int _id, vector<Block> &blockChain)
{
    Block block(_name, _id, blockChain.back().getHash());
    blockChain.push_back(block);
}

void showBlockChain(vector<Block> &blockChain)
{
    for (int i = 0; i < blockChain.size(); i++)
    {
        cout << "========================================================================================================" << endl;
        blockChain[i].showBlock();
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

int main()
{
    vector<Block> blockChain;
    Block block1("Matvey", 1, 0);

    blockChain.push_back(block1);

    createBlock("Satoshi", 2, blockChain);

    createBlock("Keramika", 52, blockChain);

    createBlock("Gojo Satoru", 63, blockChain);

    createBlock("Lipton", -1, blockChain);

    cout << checkBlockChain(blockChain) << endl;

    showBlockChain(blockChain);

    return 0;
}