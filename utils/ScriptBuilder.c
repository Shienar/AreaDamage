#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 256

int quickSortCompare(const void* e1, const void* e2)
{
    int i1 = *(const int *)e1;
    int i2 = *(const int *)e2;

    if (i1 == i2)
    {
        return 0;
    }
    else if (i1 < i2)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int main(int argc, char** argv) 
{

    FILE* input = fopen("../AOEDamage.csv", "r");
    if (input == NULL) {
        perror("Error opening input file '../AOEDamage.csv'\n");
        exit(1);
    }

    char buffer[BUFFER_LENGTH];
    int abilityID;
    char* isAOE = calloc(8, sizeof(char));

    
    //Extract all valid ability IDs into an array.
    int capacity = 256;
    int size = 0;
    int *array = calloc(capacity, sizeof(int));

    fgets(buffer, BUFFER_LENGTH, input); //Skip header

    while (fgets(buffer, BUFFER_LENGTH, input) != NULL) 
    {
        strtok(buffer, ","); //Consume abilityName
        abilityID = atoi(strtok(NULL, ",")); //AbilityID = 0 for empty / non-integer ability IDs.
        strtok(NULL, ","); //Consume category
        strtok(NULL, ","); //subcategory 1
        strtok(NULL, ","); //subcategory 2
        strtok(NULL, ","); //subcategory 3
        isAOE = strtok(NULL, ",");
        if (abilityID != 0 && strcmp("Yes", isAOE) == 0) { 
            if (size >= capacity) {
                capacity*= 2;
                array = (int*)realloc(array, capacity*sizeof(int));
            }
            array[size] = abilityID;
            size++;
        }
    }

    //Trim array.
    array = (int*)realloc(array, size*sizeof(int));

    //Sort array (ascending).
    qsort(array, size, sizeof(int), quickSortCompare);
    
    //Start printing to file.
    FILE* output = fopen("../query-script.txt", "w");
    if (output == NULL) {
        perror("Error opening output file '../query-script.txt'\n");
        exit(1);
    }

    //Print the C array into a javascript array.
    if (fprintf(output, "const areaIDs = [") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    for(int i = 0; i < size; i++)
    {
        if (i == size-1)
        {
            if (fprintf(output, "%d", array[i]) < 0) fprintf(stderr, "Error printing to file at line %d, i=%d, id=%d", __LINE__, i, array[i]);
        }
        else
        {
            if (fprintf(output, "%d, ", array[i]) < 0) fprintf(stderr, "Error printing to file at line %d, i=%d, id=%d", __LINE__, i, array[i]);
        }
    }
    if (fprintf(output, "]\n\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);

    //Create a binary search function in javascript
    /*
        //Return target index or -1
        function binarySearch(array, target) {
            let left = 0;
            let right = array.length - 1;

            while (left <= right) {
                const mid = Math.floor((left + right) / 2);

                if (array[mid] === target) {
                    return mid; 
                } else if (array[mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return -1;
        }
    */
    if (fprintf(output, "//Return target index or -1\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "function binarySearch(array, target) {\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\tlet left = 0;\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\tlet right = array.length - 1;\n\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\twhile (left <= right) {\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t\tconst mid = Math.floor((left + right) / 2);\n\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t\tif (array[mid] === target) {\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t\t\treturn mid;\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t\t} else if (array[mid] < target) {\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t\t\tleft = mid + 1;\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t\t} else {\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t\t\tright = mid - 1;\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t\t}\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t}\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\treturn -1;\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "}\n\n\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);

    //Setup pin functions.
    /*
        pinMatchesFightEvent = (event, fight) => {
            return (binarySearch(areaIDs, event.ability.id) > 0);
        }

        initializePinForFight = (fight) => {
        }
    */

    
    if (fprintf(output, "pinMatchesFightEvent = (event, fight) => {\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t//Remember to set Pin Type: Filter\n\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t//Only show AOE abilities:\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\treturn (binarySearch(areaIDs, event.ability.id) >= 0);\n\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t//Only show Non-AOE abilities:\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "\t//return (binarySearch(areaIDs, event.ability.id) < 0);\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "}\n\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "initializePinForFight = (fight) => {\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
    if (fprintf(output, "}") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);

    fclose(output);
    fclose(input);
    free(isAOE);
    isAOE = NULL;
    free(array);
    array = NULL;



    return 0;
}