// Palindorm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


struct node
{
    int number;
    int childCount;
    int visitIndex;
    node** child;
    node* parent;
};


bool checkContainElementInArray(int* checkArray, int size, int element)
{
    for (int i = 0; i < size; i++)
    {
        if (element == checkArray[i])
            return true;
    }

    return false;
}


int main()
{
    int a, b;
    int **graph = NULL;
    FILE *file = fopen("input.txt", "r");

    if (file == NULL)
    {
        std::cout << "No File\n";

        return 0;
    }

    fscanf(file, "%d %d", &a, &b);
    graph = new int* [b + 1];

    for (int i = 0; i <= b; i++)
        graph[i] = new int[2];

    graph[0][0] = a;
    graph[0][1] = b;

    for (int i = 1; i <= graph[0][1]; i++)
    {
        fscanf(file, "%d %d", &a, &b);
        graph[i][0] = a;
        graph[i][1] = b;
    }

    fclose(file);

    /*int graph[][2] = { {22, 28}, {13, 8}, {8, 1}, {1, 22}, {1, 12}, {1, 14}, {13, 18}, {13, 4},
                                {4, 20}, {20, 7}, {13, 15}, {15, 3}, {15, 9}, {9, 16}, {9, 19},
                                {22, 5}, {12, 5}, {14, 5}, {5, 11}, {11, 6}, {18, 6}, {7, 10},
                                {10, 17}, {17, 6}, {3, 21}, {21, 6}, {16, 2}, {19, 2}, {2, 21} };*/
    node* tree = NULL, * search = NULL;
    bool isGraph = false;

    std::cout << "Hello World!\n";

    for (int i = 1; i <= graph[0][1]; i++)
    {
        if (i == 1)
        {
            tree = new node;
            tree->number = graph[i][0];
            tree->child = new node * [graph[0][0]];
            tree->parent = NULL;
            tree->childCount = 0;
            tree->visitIndex = 0;

            node* leaf = new node;

            leaf->number = graph[i][1];
            leaf->child = NULL;
            leaf->childCount = 0;
            leaf->parent = tree;
            tree->child[tree->childCount] = leaf;
            tree->childCount++;
        }
        else
        {
            search = tree;

            do
            {
                if (search->number == graph[i][0])
                {
                    if (search->parent != NULL)
                        search->parent->visitIndex = 0;
                    else
                        search->visitIndex = 0;

                    break;
                }

                if (search->child != NULL)
                {
                    if (search->visitIndex < search->childCount)
                        search = search->child[search->visitIndex];
                    else
                    {
                        if (search->parent != NULL)
                        {
                            search->visitIndex = 0;
                            search = search->parent;
                            search->visitIndex++;
                        }
                        else
                            search->visitIndex++;
                    }
                }
                else
                {
                    search = search->parent;
                    search->visitIndex++;
                }
            } while (search != NULL);

            if (search->child == NULL)
            {
                search->child = new node * [graph[0][0]];
                search->childCount = 0;
            }

            node* leaf = new node;

            leaf->number = graph[i][1];
            leaf->child = NULL;
            leaf->childCount = 0;
            leaf->parent = search;
            search->child[search->childCount] = leaf;
            search->childCount++;
            search->visitIndex = 0;

            if (i == graph[0][1])
            {
                if (leaf->number == tree->number)
                    isGraph = false;
                else
                    isGraph = true;
            }
        }
    }

    std::vector<int> leaves, tArrayTemp, sArrayTemp;
    std::vector<int> tArray, sArray;

    for (int i = 1; i <= graph[0][1] / 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (!checkContainElementInArray(tArrayTemp.data(), (int)tArrayTemp.size(), graph[i][j]))
                tArrayTemp.push_back(graph[i][j]);
        }
    }

    for (int i = graph[0][1] / 2 + 1; i <= graph[0][1]; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (!checkContainElementInArray(sArrayTemp.data(), (int)sArrayTemp.size(), graph[i][j]))
                sArrayTemp.push_back(graph[i][j]);
        }
    }

    if ((!isGraph && graph[0][1] % 2 != 0) && tArrayTemp.size() != sArrayTemp.size())
    {
        std::cout << "No\n";

        return 0;
    }

    for (int i = 0; i < (int)tArrayTemp.size(); i++)
    {
        if (checkContainElementInArray(sArrayTemp.data(), (int)sArrayTemp.size(), tArrayTemp[i]))
            leaves.push_back(tArrayTemp[i]);
    }

    if (leaves.size() == tArrayTemp.size())
    {
        std::cout << "No\n";

        return 0;
    }

    std::cout << "Yes\n\n";

    for (int i = 0; i < (int)tArrayTemp.size(); i++)
    {
        search = tree;

        do
        {
            if (search->number == tArrayTemp[i])
            {
                if (search->parent != NULL)
                    search->parent->visitIndex = 0;
                else
                    search->visitIndex = 0;

                break;
            }

            if (search->child != NULL)
            {
                if (search->visitIndex < search->childCount)
                    search = search->child[search->visitIndex];
                else
                {
                    if (search->parent != NULL)
                    {
                        search->visitIndex = 0;
                        search = search->parent;
                        search->visitIndex++;
                    }
                    else
                        search->visitIndex++;
                }
            }
            else if (search->child == NULL || checkContainElementInArray(leaves.data(), (int)leaves.size(), search->number))
            {
                search = search->parent;
                search->visitIndex++;
            }
        } while (search != NULL);

        tArray.push_back(search->number);
        search->visitIndex = 0;

        while (search != NULL)
        {
            search->visitIndex = 0;
            search = search->parent;
        }
    }

    for (int i = 0; i < (int)leaves.size(); i++)
    {
        search = tree;

        do
        {
            if (search->number == leaves[i])
            {
                if (search->parent != NULL)
                    search->parent->visitIndex = 0;
                else
                    search->visitIndex = 0;

                break;
            }

            if (search->child != NULL)
            {
                if (search->visitIndex < search->childCount)
                    search = search->child[search->visitIndex];
                else
                {
                    if (search->parent != NULL)
                    {
                        search->visitIndex = 0;
                        search = search->parent;
                        search->visitIndex++;
                    }
                    else
                        search->visitIndex++;
                }
            }
            else
            {
                search = search->parent;
                search->visitIndex++;
            }
        } while (search != NULL);

        while (search != NULL)
        {
            if (!checkContainElementInArray(sArray.data(), (int)sArray.size(), search->number))
                sArray.push_back(search->number);

            if (search->child != NULL)
                search = search->child[0];
            else
                break;
        }
    }

    std::cout << "NB: Nodes of T tree are: ";

    for (int i = 0; i < (int)tArray.size(); i++)
    {
        std::cout << tArray[i];

        if (i == (int)tArray.size() - 1)
            std::cout << ".\n";
        else
            std::cout << ", ";
    }

    std::cout << "Nodes of S tree are: ";

    for (int i = 0; i < (int)sArray.size(); i++)
    {
        std::cout << sArray[i];

        if (i == (int)sArray.size() - 1)
            std::cout << ".\n";
        else
            std::cout << ", ";
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
