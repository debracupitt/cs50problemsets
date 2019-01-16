/**
 * Implements a dictionary's functionality.
 * Using TRIE
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Constants
#define ALPHABET 27

// TRIE node
typedef struct node
{
    struct node *children[ALPHABET];
    bool is_word;
} node;

// prototypes
node *create_node();
void free_node(node *n);
int get_index(char c);

// Create global variables
node *root;
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Create a pointer to traverse the dictionary
    node *current_level = root;
    // Iterate through each letter in input word
    for (int w = 0; w < strlen(word); w++)
    {
        // Go to corresponding element in children
        int word_index = get_index(word[w]);

        // If NULL, word is misspelled
        if (current_level -> children[word_index] == NULL)
        {
            return false;
        }

        // If not NULL, move to next letter
        current_level = current_level -> children[word_index];
    }

    return current_level -> is_word;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Reset word count to 0
    word_count = 0;

    // Create root TRIE node and check for NULL
    root = create_node();
    if (root == NULL)
    {
        fprintf(stderr, "Usage: not enough memory space!\n");
        return false;
    }

    // Create a pointer and point to root of trie
    node *current_level = root;

    // Open dictioary
    FILE *file_d = fopen(dictionary, "r");
    if (file_d == NULL)
    {
        fprintf(stderr, "Could not open dictionary\n");
        return false;
    }

    // Store each word in dictionary
    for (int c = fgetc(file_d); c != EOF; c = fgetc(file_d))
    {
        // determine the position of the character in the node's children array
        int index = get_index(c);

        // if at end of word
        if (c == '\n')
        {
            // set is_word to true
            current_level -> is_word = true;
            // add one to word count
            word_count++;
            // reset current_level to root for entering the next word
            current_level = root;
            // Forces the next iteration of the loop, skip code below
            continue;
        }

        // If children[i] is NULL, malloc a new node, have children[i] point to it
        if (current_level -> children[index] == NULL)
        {
            // create new node at children[index] and make current_level pointer point to this new node
            current_level -> children[index] = create_node();

            // if node is still NULL, there was an error
            if (current_level -> children[index] == NULL)
            {
                fclose(file_d);
                fprintf(stderr, "Not enough memory space for new node.\n");
                return false;
            }
        }

        // if not NULL, move to new node and continue
        current_level = current_level -> children[index];
    }

    fclose(file_d);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
  free_node(root);
  return true;
}

// Returns a new node with all children values set to NULL and is_word set to false
node *create_node()
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
        return NULL;

    for (int a = 0; a < 27; a++)
    {
        n -> children[a] = NULL;
    }

    n -> is_word = false;

    return n;
}

// Recurses through entire trie and frees node each time NULL is reached
void free_node(node *level)
{
  for (int i = 0; i < 27; i++)
  {
    if (level -> children[i] != NULL)
      free_node(level -> children[i]);
  }
  free(level);
}

// Returns the index for children[index] of c
int get_index(char c)
{
    int index;

    // if 'c' is alpha
    if (isalpha(c))
    {
        if (isupper(c))
        {
            index = c - 65;
        }
        if (islower(c))
        {
            index = c - 97;
        }
    }

    // if 'c' is an apostrophe
    else if (c == '\'')
    {
        index = 26;
    }

    // if 'c' is a new line
    else if (c == '\n')
    {
        index = 100;
    }

    else
    {
        index = 200;
    }

    return index;
}