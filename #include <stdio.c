#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count; // To store the count of occurrences
};

// Initialize a TrieNode
struct TrieNode *initializeNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            node->children[i] = NULL;
    }
    return node;
}

// Inserts the word into the trie
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *crawler = root;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (!crawler->children[index])
            crawler->children[index] = initializeNode();
        crawler = crawler->children[index];
    }
    crawler->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode *crawler = root;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (!crawler->children[index])
            return 0; // Word not found
        crawler = crawler->children[index];
    }
    return crawler->count;
}

// Deallocate the trie structure
void deallocateTrie(struct TrieNode *root) {
    if (root) {
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            if (root->children[i])
                deallocateTrie(root->children[i]);
        free(root);
    }
}

// Initializes a trie structure
struct TrieNode *createTrie() {
    return initializeNode();
}

// Reads the dictionary file and returns the number of words
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    int count = 0;
    char word[100]; // Assuming maximum word length is 99
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = strdup(word);
        count++;
    }
    fclose(file);
    return count;
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
        printf("%s\n", inWords[i]);

    // Create and populate the trie
    struct TrieNode *root = createTrie();
    for (int i = 0; i < numWords; i++)
        insert(root, inWords[i]);

    // Test the trie with sample words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));

    // Deallocate the trie
    deallocateTrie(root);
    
    return 0;
}
