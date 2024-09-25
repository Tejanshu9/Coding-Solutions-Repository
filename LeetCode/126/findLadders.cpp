class Solution {
public:
    vector<vector<string>> ans;
    vector<string> path;
    void DFS(string &beginWord, string &endWord, unordered_map<string, unordered_set<string>>&adj){
        if(beginWord == endWord){
            path.push_back(endWord);
            reverse(begin(path),end(path));
            ans.push_back(path);
            reverse(begin(path),end(path));
            path.pop_back();
            return;
        }
        for(auto x : adj[beginWord])
            DFS(x, endWord, adj);
        
        path.pop_back(); //pop current word to backtrack
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string,unordered_set<string>>adj; //adjacency list
        unordered_set<string> dict(wordList.begin(), wordList.end()); //insert all the strings in set
         if(!dict.count(endWord) || dict.empty()) return ans;
		//step-1 => Find min depth using BFS
        queue<string>q;  //for BFS Traversal
        q.push(beginWord);
        unordered_map<string,int>visited;
        visited[beginWord] = 0; //start node will always at level 0
        
        while(!q.empty()){
            string curr = q.front();
            q.pop();
            string temp = curr;
            
            for(int i = 0; i < curr.size(); i++){ //check all characters
                for(char c = 'a'; c <= 'z'; c++){ //try all possible 26 letters
                    if(temp[i] == c) continue;  //skip if letter is same as original word
                    temp[i] = c;
                    
                    if(dict.count(temp) > 0){ // check if new word is present in wordList
                        if(visited.count(temp) == 0){ //check if new word was already visited
                            visited[temp] = visited[curr] + 1;
                            q.push(temp);
                            adj[temp].insert(curr);
                        }
                        else if(visited[temp] == visited[curr] + 1) //if already visited and new word is child
                            adj[temp].insert(curr);    
                    }
                }
            }
        }
       // step-2 => find all min depth possible paths using DFS
       if (!adj.count(endWord)) return ans;
        DFS(endWord, beginWord, adj);
        return ans;
    }
};