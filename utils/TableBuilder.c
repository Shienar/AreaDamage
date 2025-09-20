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

    FILE* output = fopen("../table.lua", "w");
    if (output == NULL) {
        perror("Error opening output file '../table.lua'\n");
        fclose(input);
        exit(1);
    }

    char buffer[BUFFER_LENGTH];


    char* abilityName = calloc(32, sizeof(char));
    int abilityID;
    char* category = calloc(32, sizeof(char));
    char* subcategory1 = calloc(32, sizeof(char));
    char* subcategory2 = calloc(32, sizeof(char));
    char* subcategory3 = calloc(32, sizeof(char));
    char* isAOE = calloc(8, sizeof(char));
    char* notes = calloc(64, sizeof(char));
    char* patch = calloc(8, sizeof(char));

    char* currentCategory = calloc(32, sizeof(char));
    char* currentSubcategory1 = calloc(32, sizeof(char));
    char* currentSubcategory2 = calloc(32, sizeof(char));
    char* currentSubcategory3 = calloc(32, sizeof(char));

    char* tabs = calloc(4, sizeof(char));

    if (fprintf(output, "table = {\n") < 0) fprintf(stderr, "Error printing to file at line %d", __LINE__);

    fgets(buffer, BUFFER_LENGTH, input); //Skip header.
    while (fgets(buffer, BUFFER_LENGTH, input) != NULL) 
    {
        //This breaks if there are two consecutive commas in a line.
        abilityName = strtok(buffer, ",");
        abilityID = atoi(strtok(NULL, ","));
        category = strtok(NULL, ",");
        subcategory1 = strtok(NULL, ",");
        subcategory2 = strtok(NULL, ",");
        subcategory3 = strtok(NULL, ",");
        isAOE = strtok(NULL, ",");
        notes = strtok(NULL, ",");
        patch = strtok(NULL, ",");

        short patch_length = strlen(patch);
        if (patch_length > 0 && patch[patch_length - 1] == '\n')
        {
            patch[patch_length - 1] = '\0';
        }

        if (strcmp("Yes", isAOE) == 0)
        {
            if (strcmp(category, currentCategory) != 0 || 
                strcmp(subcategory1, currentSubcategory1) != 0 ||
                strcmp(subcategory2, currentSubcategory2) != 0 ||
                strcmp(subcategory3, currentSubcategory3) != 0)
            {
                strncpy(currentCategory, category, 32);
                strncpy(currentSubcategory1, subcategory1, 32);
                strncpy(currentSubcategory2, subcategory2, 32);
                strncpy(currentSubcategory3, subcategory3, 32);
                
                if (strcmp(subcategory3, "-") != 0)
                {
                    if (fprintf(output, "\n\t-- CATEGORY: %s>%s>%s>%s\n", currentCategory, currentSubcategory1, currentSubcategory2, currentSubcategory3) < 0) fprintf(stderr, "Error printing to file at line %d, id = %d", __LINE__, abilityID);
                }
                else if (strcmp(subcategory2, "-") != 0)
                {
                    if (fprintf(output, "\n\t-- CATEGORY: %s>%s>%s\n", currentCategory, currentSubcategory1, currentSubcategory2) < 0) fprintf(stderr, "Error printing to file at line %d, id = %d", __LINE__, abilityID);
                }
                else
                {
                    if (fprintf(output, "\n\t-- CATEGORY: %s>%s\n", currentCategory, currentSubcategory1) < 0) fprintf(stderr, "Error printing to file at line %d, id = %d", __LINE__, abilityID);
                }
            }

            if (abilityID < 100000) {
                tabs = "\t\t\t";
            }
            else
            {
                tabs = "\t\t";
            }

            if (strcmp(notes, "-") != 0)
            {
                if (fprintf(output, "\t[%d] = true,%s-- %s (%s) | Last Checked: %s\n", abilityID, tabs, abilityName, notes, patch) < 0)  fprintf(stderr, "Error printing to file at line %d, id = %d", __LINE__, abilityID);
            }
            else
            {
                if (fprintf(output, "\t[%d] = true,%s-- %s | Last Checked: %s\n", abilityID, tabs, abilityName, patch) < 0)  fprintf(stderr, "Error printing to file at line %d, id = %d", __LINE__, abilityID);
            }
        }
    }

    if (fprintf(output, "\n}") < 0)  fprintf(stderr, "Error printing to file at line %d", __LINE__);

    fclose(output);
    fclose(input);

    free(abilityName);
    free(category);
    free(subcategory1);
    free(subcategory2);
    free(subcategory3);
    free(isAOE);
    free(notes);
    free(patch);

    free(currentCategory);
    free(currentSubcategory1);
    free(currentSubcategory2);
    free(currentSubcategory3);

    free(tabs);

    abilityName = NULL;
    category = NULL;
    subcategory1 = NULL;
    subcategory2 = NULL;
    subcategory3 = NULL;
    isAOE = NULL;
    notes = NULL;
    patch = NULL;

    currentCategory = NULL;
    currentSubcategory1 = NULL;
    currentSubcategory2 = NULL;
    currentSubcategory3 = NULL;

    tabs = NULL;

    return 0;
}