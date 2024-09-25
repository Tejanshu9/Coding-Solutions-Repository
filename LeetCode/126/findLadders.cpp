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
        
        path.pop_back(); 
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string,unordered_set<string>>adj; 
        unordered_set<string> dict(wordList.begin(), wordList.end()); 
         if(!dict.count(endWord) || dict.empty()) return ans;
		
        queue<string>q;  
        q.push(beginWord);
        unordered_map<string,int>visited;
        visited[beginWord] = 0; 
        while(!q.empty()){
            string curr = q.front();
            q.pop();
            string temp = curr;
            
            for(int i = 0; i < curr.size(); i++){ 
                for(char c = 'a'; c <= 'z'; c++){ 
                    if(temp[i] == c) continue;  
                    temp[i] = c;
                    
                    if(dict.count(temp) > 0){ 
                        if(visited.count(temp) == 0){ 
                            visited[temp] = visited[curr] + 1;
                            q.push(temp);
                            adj[temp].insert(curr);
                        }
                        else if(visited[temp] == visited[curr] + 1) 
                            adj[temp].insert(curr);    
                    }
                }
            }
        }
       
       if (!adj.count(endWord)) return ans;
        DFS(endWord, beginWord, adj);
        return ans;
    }
};
