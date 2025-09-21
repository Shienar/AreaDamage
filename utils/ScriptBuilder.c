#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 256

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

    //Start printing to file.
    FILE* output = fopen("../filter-expression.txt", "w");
    if (output == NULL) {
        perror("Error opening output file '../filter-expression.txt'\n");
        exit(1);
    }

    //Print 2 near-identical lines.
    for(int i = 0; i < 2; i++)
    {
        if(i == 0)
        {
            if (fprintf(output, "ability.Id IN (") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
        }
        else
        {
            if (fprintf(output, "ability.Id NOT IN (") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
        }

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
        
        if (fprintf(output, ")") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
        if (i == 0)
        {
            if (fprintf(output, "\n\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);
        }
    }
    
    fclose(output);
    fclose(input);
    free(isAOE);
    isAOE = NULL;
    free(array);
    array = NULL;



    return 0;
}