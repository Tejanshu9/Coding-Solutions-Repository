class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
         unordered_set<string> wordSet(wordList.begin(), wordList.end());
    
    // If endWord is not in the wordList, no valid transformation is possible
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }
    
    // Initialize a queue for BFS, starting with the beginWord
    queue<pair<string, int>> q;  // pair of word and current transformation count (level)
    q.push({beginWord, 1});
    
    // Perform BFS
    while (!q.empty()) {
        string currentWord = q.front().first;
        int currentLevel = q.front().second;
        q.pop();
        
        // Check all possible one-letter transformations of the currentWord
        for (int i = 0; i < currentWord.size(); i++) {
            string tempWord = currentWord;
            for (char c = 'a'; c <= 'z'; c++) {
                tempWord[i] = c;
                
                // If we found the endWord, return the number of transformations
                if (tempWord == endWord) {
                    return currentLevel + 1;
                }
                
                // If the transformed word is in the wordSet, add it to the queue
                if (wordSet.find(tempWord) != wordSet.end()) {
                    q.push({tempWord, currentLevel + 1});
                    // Remove the word from wordSet to mark it as visited
                    wordSet.erase(tempWord);
                }
            }
        }
    }
    
    // If no valid transformation is found, return 0
    return 0;
}
    
};