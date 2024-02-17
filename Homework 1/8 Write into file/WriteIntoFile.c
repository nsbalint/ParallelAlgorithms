#include <stdio.h>

void writeIntegers(const char *filename, int arr[], int size)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error while opening file!\n");
        return;
    }
    for (int i = 0; i < size; ++i)
    {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

void writeLongs(const char *filename, long arr[], int size)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error while opening file!\n");
        return;
    }
    for (int i = 0; i < size; ++i)
    {
        fprintf(file, "%ld\n", arr[i]);
    }
    fclose(file);
}

void writeFloats(const char *filename, float arr[], int size)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error while opening file!\n");
        return;
    }
    for (int i = 0; i < size; ++i)
    {
        fprintf(file, "%f\n", arr[i]);
    }
    fclose(file);
}

long getFileSize(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error while opening file!\n");
        return -1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

int main()
{
    int intArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    long longArr[] = {100000000, 200000000, 300000000, 400000000, 500000000, 600000000, 700000000};
    float floatArr[] = {3.14, 2.718, 1.618, 6.12, 24.255, 123.233};

    writeIntegers("integers.txt", intArr, sizeof(intArr) / sizeof(int));
    writeLongs("longs.txt", longArr, sizeof(longArr) / sizeof(long));
    writeFloats("floats.txt", floatArr, sizeof(floatArr) / sizeof(float));

    long intFileSize = getFileSize("integers.txt");
    long longFileSize = getFileSize("longs.txt");
    long floatFileSize = getFileSize("floats.txt");

    printf("Size of integers.txt: %ld byte\n", intFileSize);
    printf("Size of longs.txt: %ld byte\n", longFileSize);
    printf("Size of floats.txt: %ld byte\n", floatFileSize);

    return 0;
}
