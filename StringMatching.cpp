int StringMatching() {                                           //iterate through the dictionary and exclude dictionary words ending with N, Tra(n)
    string dictionary_file_name = "dictionary.txt";
    unordered_set<string> dictionary;
    fstream file;
    file.open(dictionary_file_name, ios::in);

    if (file.is_open()) {
        string inWord;
        char lastLetter = 'n';

        while (file >> inWord) {                        //inserting into unordered set, gives a good average-case runtime for insert
            if (inWord.back() != lastLetter) {
                dictionary.insert(inWord); 
            }
        }
    }

    file.close();

    Trie trie_tree;
    for (const string& inWord : dictionary) {
        trie_tree.insert(inWord);                       //insert word into a trie
    }

    fstream input_file; 
    string read_file_name = "BigData.txt";
    input_file.open(read_file_name, ios::in);


    int palindrome = 0;                                 //detect palindrome, iterate through trie to string match
    string line;
    while (getline(input_file, line)) {
        for (int i = 0; i < line.length(); i++) {
            shared_ptr<TrieNode> node = trie_tree.getRoot();
            for (int j = i; j < line.length(); j++) {
                char currentChar = line[j];
                if (node->children.find(currentChar) == node->children.end()) {
                    break; 
                }
                node = node->children[currentChar];
                if (node->fullWord) {
                    palindrome++; 
                }
            }
        }
    }
    return palindrome;
}
