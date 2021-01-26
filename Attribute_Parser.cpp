#include<iostream>
#include <sstream>
#include<map>
#include <vector>

using namespace std;

enum next_PosLvl{
    POSITION = 1,
    LEVEL = 0
};

struct tag_node{
    string tag;
    map<string, string> m;
    tag_node* next_lvl = NULL ;
    tag_node* next_pos = NULL ;
};

tag_node* search_node(tag_node* base_node, string tag_to_find);
tag_node* Lateral_Search(tag_node* base_node, string tag_to_find);

// Add function ---------------------------------------------------------
void add(tag_node* node, tag_node* to_add, string prev_tag, next_PosLvl PosLvl){
    tag_node* curr_node = search_node(node, prev_tag);
    
    if(PosLvl==POSITION)
        curr_node->next_pos = to_add;
    if(PosLvl==LEVEL)
        curr_node->next_lvl = to_add;
}

// Check function ---------------------------------------------------------
void check(tag_node* b_node, vector<string> tag_seq, string key) {
    tag_node* it_node = Lateral_Search(b_node->next_lvl, tag_seq[0]);

    if (it_node == NULL) {
        cout << "Not Found!\n";
        return;
    }

    int i = 0;
    if (tag_seq.size() > 1) {
        while (i < tag_seq.size() - 1) {
            it_node = Lateral_Search(it_node, tag_seq[i]);
            if (it_node == NULL)
                break;            
            else if (!it_node->tag.compare(tag_seq[i]))
                it_node = it_node->next_lvl;
            else
                cout << "Not Found!\n";
            i++;
        }

        it_node = Lateral_Search(it_node, tag_seq[i]);
        if (it_node == NULL) {
            cout << "Not Found!\n";    return;
        }
    }
    if (!it_node->tag.compare(tag_seq[i]) && it_node->m.find(key) != it_node->m.end())
        cout << it_node->m[key] << "\n";
    else
        cout << "Not Found!\n";

}

// Search function ---------------------------------------------------------
tag_node* search_node(tag_node* base_node, string tag_to_find) {
    // return the matching node
    if (!base_node->tag.compare(tag_to_find))return base_node;

    // call recursively the search method on both dimentions: vertical and horizontal
    if (base_node->next_lvl != NULL)
        if (search_node(base_node->next_lvl, tag_to_find) != NULL)return search_node(base_node->next_lvl, tag_to_find);
    if (base_node->next_pos != NULL)
        if (search_node(base_node->next_pos, tag_to_find) != NULL)return search_node(base_node->next_pos, tag_to_find);
    return NULL;
}

// Lateral_Search function ---------------------------------------------------------
tag_node* Lateral_Search(tag_node* node, string tag_to_find) {

    if (node == NULL)return NULL;

    // return current node if already match with the target
    if (!node->tag.compare(tag_to_find))return node;

    // search lateraly (the same level)
    while (node->next_pos != NULL) {
        node = node->next_pos;
        if (!node->tag.compare(tag_to_find))return node;
    }
    return NULL;
}

// string splitting functions
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}




// Implementation function
int main() {

    int N, Q;
    string s[20];
    string q[22];
    cin >> N ;
    cin >> Q ; 
    string l, key, val;
    
    string tag_name = "base_name";
    string prev_tag = tag_name;
    pair<string, int> closing_tag;
    
    tag_node base_node;
    base_node.tag = tag_name;
    
    
    getline(cin, l);
    for (int i=0 ; i < N ; i++ )
        getline(cin,s[i]);
     
    for (int i=0 ; i < Q ; i++ )
        getline(cin,q[i]);
        
    // Constructing the binary tree
    for(int i=0; i<N; i++){        
        // create a new node
        stringstream ss(s[i]);
        string sss;
        tag_node* new_node = new tag_node();        
        while(ss>>l){
            
            // case of empty node
            if(l[0]=='<' && l[1]!='/' && l[l.size()-1]=='>') {
                tag_name = l.substr(1, l.size()-2);
                new_node->tag = tag_name;
                l="\"";
            }
            
            // case of a normal tag name
            else if(l[0]=='<' && l[1]!='/'){
                tag_name = l.substr(1, l.size()-1);    
            }
            
            // add a key and a value to the node
            else if(l[0]!='<' && l[0]!='='){
                key = l;
                // read "=" then the value 
                ss>>l; ss>>l;
                l[l.size()-1]=='\"' ? val = l.substr(1, l.size()-2) : val = l.substr(1, l.size()-3) ;
                new_node->tag = tag_name;
                new_node->m[key]= val;        
            }
            
            // case of a closing tag
            else{
                closing_tag = make_pair(l.substr(2, l.size()-3), 1);
            }            
        }
        
        // insert new node in next position
        if(closing_tag.second && l[0]=='\"'){                
            add(&base_node, new_node, closing_tag.first, POSITION);        
            closing_tag = make_pair(tag_name, 0);
            prev_tag = tag_name;
        }
        
        // insert new node in next level
        else if(l[1]!='/'){                                    
            add(&base_node, new_node, prev_tag, LEVEL);    
            prev_tag = tag_name;
        }
    }
    
    // Queries
    for(int i=0; i<Q; i++){
        stringstream ss(q[i]);
        while(ss>>l){
            vector<string> tag_sq = split(l, '.');
            
            key = tag_sq[tag_sq.size()-1].substr(tag_sq[tag_sq.size()-1].find('~')+1, tag_sq[tag_sq.size()-1].size());
            tag_sq[tag_sq.size()-1] = tag_sq[tag_sq.size()-1].substr(0, tag_sq[tag_sq.size()-1].find('~'));
            check(&base_node, tag_sq, key);            
        }
    }
    return 0 ;
}
