
class TrieNode{
    private:
        TrieNode* children[26];
        bool endOfWord;
    public:
        TrieNode();
        friend class Trie;
};
class Trie{
    private:
        TrieNode* prefixRoot;
        int chCounter;
        
        bool duplicate;
    public:
        TrieNode* root;
        int numOfWords;
        Trie();
        ~Trie();
        void insert(std::string word);
        bool search(std::string word);
        bool erase(TrieNode*& currentNode, std::string word);
        bool hasChild(TrieNode* currentNode);
        bool empty();
        void spellCheck(std::string word);
        void suggestionPrinter(TrieNode* currentNode,int position, char ch[], std::string word);
        void print(TrieNode* currentNode, int position, char word[]);
        void clear(TrieNode* currentNode);
        void size();
};
class illegal_exception{
    public:
        void error(){
            std::cout << "illegal argument" <<std::endl;
        }
};