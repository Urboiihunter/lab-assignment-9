#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order;
};

// Fill out this structure
struct HashType
{
    struct RecordType* head; // Pointer to the head of the linked list
};

#define HASH_SIZE 10

// Compute the hash function
int hash(int x)
{
    return x % HASH_SIZE;
}

// Function to insert a record into the hash table
void insertRecord(struct HashType* hashTable, struct RecordType record)
{
    int index = hash(record.id);

    // Create a new node for the record
    struct RecordType* newRecord = (struct RecordType*)malloc(sizeof(struct RecordType));
    newRecord->id = record.id;
    newRecord->name = record.name;
    newRecord->order = record.order;

    // If the slot is empty, insert the record as the head of the linked list
    if (hashTable[index].head == NULL)
    {
        hashTable[index].head = newRecord;
        newRecord->next = NULL;
    }
    else
    {
        // If the slot is not empty, append the record to the linked list
        newRecord->next = hashTable[index].head;
        hashTable[index].head = newRecord;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* hashTable, int hashSz)
{
    int i;
    for (i = 0; i < hashSz; ++i)
    {
        printf("index %d -> ", i);
        struct RecordType* current = hashTable[i].head;
        while (current != NULL)
        {
            printf("%d %c %d -> ", current->id, current->name, current->order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;
    int i;

    recordSz = parseData("input.txt", &pRecords);

    // Your hash implementation
    struct HashType hashTable[HASH_SIZE];

    // Initialize hash table
    for (i = 0; i < HASH_SIZE; i++)
    {
        hashTable[i].head = NULL;
    }

    // Insert records into the hash table
    for (i = 0; i < recordSz; i++)
    {
        insertRecord(hashTable, pRecords[i]);
    }

    // Display records in the hash table
    displayRecordsInHash(hashTable, HASH_SIZE);

    // Free allocated memory for the records
    free(pRecords);

    return 0;
}
