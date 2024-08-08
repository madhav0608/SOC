#include "trie.h"
#include <iostream>

Trie::Trie()
{
	root = NULL;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
		
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	return false;
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	return false;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	// found a std::string in Trie with the given prefix
	bool flag = false;

	TrieNode *A = root, *B;
	int i = 0, n = 0;
	while(currPrefix[i] != 0) {
		n = CHAR_TO_INDEX(currPrefix[i]);
		if(A->children[n] == NULL){
			break;
		}
		A = A->children[n];
		i++;
	}

	std::string arr = currPrefix,arr_prime;
	if(A->isWordEnd == true){
		std::cout << arr << std::endl;
	}

	for(int i = 0; i < ALPHABET_SIZE; i++) {
		if(A->children[i] != NULL) flag = true;
	}
	if( flag == false) {
		return;
	}

	for(int i = 0; i < ALPHABET_SIZE; i++) {
		if(A->children[i] != NULL) {
			arr_prime = arr + char(i + (int)'a');
			suggestionsRec(root,arr_prime);
		}
	}

}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	if(root == NULL) return -1;

	int n = CHAR_TO_INDEX(query[0]);
	if(root->children[n] == NULL) return 0;

	TrieNode *A = root, *B;
	int i = 0; n = 0;
	while(query[i] != 0) {
		n = CHAR_TO_INDEX(query[i]);
		if(A->children[n] == NULL){
			break;
		}
		A = A->children[n];
		i++;
	}
	if(i != query.size()) return 0;

	suggestionsRec(root,query);
	return 1;
}
