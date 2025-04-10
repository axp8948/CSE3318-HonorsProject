// UPPER LEVEL STRATEGY:

// First read the input file
// Create a data structure (maybe linked list) to represent the data in a graph like manner
// Implement the Dijskstra's Algorithm and find the shortest path

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXINPUT 100

// DATA REPRESENTATION (Using Linked List and array)

// A city can have multiple neighbors, so define the struct for city, and define struct for neighboring nodes

// Define the neighbor node
typedef struct NeighborNode
{
    int cityIndex; // index of connected city
    int distance; // distance to that city from original city
    struct NeighborNode* nextCity; // pointer to the next neighbor
} NeighborNode;

// Define the city node
typedef struct City
{
    char name[100]; // name of city
    NeighborNode *NeighborHead; // neighbors 
} City;

// HELPER FUNCTIONS


// Function to print the graph
void printGraph(City* cities, int cityCount) {
    for (int i = 0; i < cityCount; i++) {
        printf("City: %s\n", cities[i].name);
        NeighborNode* current = cities[i].NeighborHead;
        while (current != NULL) {
            printf("  -> %s (Distance: %d)\n", cities[current->cityIndex].name, current->distance);
            current = current->nextCity;
        }
        printf("\n");
    }
}

// Function to find the index of city (if it exists)

int findCityIndex(City** cities, int *cityCount, int *cityCapacity, char city [])
{
    for (int i = 0; i < *cityCount; i++)
    {
        if (strcmp((*cities)[i].name, city) == 0)
        {
            return i;
        }
    }

    if (*cityCount == *cityCapacity)
    {
        *cityCapacity = (*cityCapacity) * 2; // Less Amortized cost
        *cities = realloc(*cities, (*cityCapacity)*sizeof(City));
    }


    // If city is not already in the list, add it
    
    strcpy((*cities)[*cityCount].name, city);  
    (*cities)[*cityCount].NeighborHead = NULL; 
    (*cityCount)++; 
    return (*cityCount - 1);  
}

// Function to build Graph

void buildGraph(City * cities, int sourceCityIndex, int destinationCityIndex, int distance)
{
    NeighborNode *newNode = malloc(sizeof(NeighborNode));
    newNode -> cityIndex = destinationCityIndex;
    newNode -> distance = distance;
    newNode -> nextCity = cities[sourceCityIndex].NeighborHead; // Adding on the first of the list, need not to traverse the list // less time
    cities[sourceCityIndex].NeighborHead = newNode; // make the neighborhead point to the newl neighbor city

}

void dijkstraAlgorithm(City *cities, int sourceCityIndex, int destinationCityIndex, int cityCount)
{
    // To keep track of distances and visited nodes
    int visited [cityCount];
    int distance [cityCount];
    int pathTracker [cityCount];

    // Initialize the above array with an initial value
    for (int i = 0; i < cityCount; i++)
    {
        visited[i] = 0;
        distance [i] = INT32_MAX;
        pathTracker[i] = 0;
    }

    // Perform the dijsktra algorithm
    for (int i = 0; i < cityCount; i++)
    {
        // set the initial distance for the source city as 0
        distance[sourceCityIndex] = 0;
        
    }
}



int main(int argc, char** argv)
{
    // Get the filename and open it in read mode
    FILE *inputFile;
    char fileName[100];
    char source[100];
    char destination[100];

    printf("Enter filename: ");
    scanf("%s", fileName);

    printf("\n");

    printf("Enter origin city: ");
    scanf("%s", source);

    printf("\n");

    printf("Enter destination city: ");
    scanf("%s", destination);

    printf("\n\n");

    
    inputFile = fopen(fileName, "r");


    // DEBUG CODE:
    // char fileLine [100];

    // while(fgets(fileLine, sizeof(fileLine), inputFile))
    // {
    //     printf("%s", fileLine);
    //     printf("\n");
    // }

    // Error message if the file could not be opened!

    if (inputFile == NULL)
    {
        printf("Could not open the file \n");
        return -1;
    }


    // Since we do not know the counts of cities, use malloac


    // Since Dijkstra's algorithm requires frequent access to the city, better to use dynamic array than the linked list to represent the city map

    City *cities = malloc(10 * sizeof(City)); // For initiataion
    int cityCount = 0;
    int cityCapacity = 10; // Initial city count


    // Read input file and build the graph using the helper function

    char sourceCity[MAXINPUT];
    char destinationCity[MAXINPUT];

    int distance;

    while(1)
    {
        fscanf(inputFile, "%s %s %d", sourceCity, destinationCity, &distance);
        if (strcmp(sourceCity, "END") == 0 && strcmp(destinationCity, "OF") == 0)
        {
            break;
        }

        // Find the index of city if it already exists otherwise add to new position
        int sourceCityIndex = findCityIndex(&cities, &cityCount, &cityCapacity, sourceCity);
        
        int destinationCityIndex = findCityIndex(&cities, &cityCount, &cityCapacity, destinationCity);

        // add the info to the graph
        buildGraph(cities, sourceCityIndex, destinationCityIndex, distance);
    }

    printGraph(cities, cityCount);












    // CLEANUPS
    fclose(inputFile); // Close the file after the end of operation
    free(cities);




}