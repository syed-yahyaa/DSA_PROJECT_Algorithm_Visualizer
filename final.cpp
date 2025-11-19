#include "raylib.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int ARRAY_SIZE = 10;
const int NUMBER_WIDTH = 30;
const int NUMBER_HEIGHT = 30;
const int START_X = 50;
const int START_Y = 300;

enum SortType { BUBBLE, INSERTION, SELECTION, QUICK, MERGE };

struct Number {
    int value;
    Vector2 pos;
    Color color;
};

void DrawArray(const vector<Number> &arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        DrawRectangle(arr[i].pos.x, arr[i].pos.y - arr[i].value * 5, NUMBER_WIDTH, arr[i].value * 5, arr[i].color);
        DrawText(to_string(arr[i].value).c_str(), arr[i].pos.x + 5, arr[i].pos.y - arr[i].value * 5 - 20, 20, WHITE);
    }
}

void Swap(Number &a, Number &b) {
    swap(a.value, b.value);
}

void BubbleSort(vector<Number> arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        bool swapped =false;
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            arr[j].color = RED;
            arr[j + 1].color = YELLOW;
            BeginDrawing();
            ClearBackground(BLACK);
            DrawArray(arr);
            EndDrawing();
            WaitTime(0.5f);

            if (arr[j].value > arr[j + 1].value) {Swap(arr[j], arr[j + 1]); swapped=true;}
            arr[j].color = BLUE;
            arr[j + 1].color = BLUE;
        }
        if(!swapped) break;
    }
    WaitTime(1.0f);
}

void InsertionSort(vector<Number> arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        Number key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].value > key.value) {
            arr[j + 1].value = arr[j].value;
            arr[j].color = RED;
            arr[j + 1].color = RED;
            BeginDrawing();
            ClearBackground(BLACK);
            DrawArray(arr);
            EndDrawing();
            WaitTime(0.5f);
            arr[j].color = BLUE;
            arr[j + 1].color = BLUE;
            j--;
        }
        arr[j + 1] = key;
    }

}

void SelectionSort(vector<Number> arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        int min_idx = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            arr[j].color = RED;
            arr[min_idx].color = GREEN;
            BeginDrawing();
            ClearBackground(BLACK);
            DrawArray(arr);
            EndDrawing();
            WaitTime(0.5f);
            if (arr[j].value < arr[min_idx].value) min_idx = j;
            arr[j].color = BLUE;
            arr[min_idx].color = BLUE;
        }
        Swap(arr[i], arr[min_idx]);
    }
    WaitTime(1.0f);
}

int Partition(vector<Number> &arr, int low, int high) {
    int pivot = arr[high].value;
    arr[high].color = GREEN;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        arr[j].color = RED;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawArray(arr);
        EndDrawing();
        WaitTime(0.5f);

        if (arr[j].value < pivot) {
            i++;
            Swap(arr[i], arr[j]);
        }
        arr[j].color = BLUE;
    }
    Swap(arr[i + 1], arr[high]);
    arr[high].color = BLUE;
    return i + 1;
}

void QuickSort(vector<Number> arr, int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
    WaitTime(1.0f);
}

void Merge(vector<Number> &arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Number> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        L[i].color = RED;
        R[j].color = RED;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawArray(arr);
        EndDrawing();
        WaitTime(0.5f);

        if (L[i].value <= R[j].value) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        arr[k].color = BLUE;
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void MergeSort(vector<Number> arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        Merge(arr, l, m, r);
    }
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Sorting Algorithm Visualizer - Numbers");

    srand(time(0));
    vector<Number> numbers(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i].value = rand() % 20 + 1;
        numbers[i].pos = {(float)START_X + i * (NUMBER_WIDTH + 5), START_Y};
        numbers[i].color = BLUE;
    }

    SortType currentSort = BUBBLE;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Press 1:Bubble 2:Insertion 3:Selection 4:Quick 5:Merge", 50, 50, 20, WHITE);
        DrawArray(numbers);

        EndDrawing();

        if (IsKeyPressed(KEY_ONE)) { BubbleSort(numbers); }
        if (IsKeyPressed(KEY_TWO)) { InsertionSort(numbers); }
        if (IsKeyPressed(KEY_THREE)) { SelectionSort(numbers); }
        if (IsKeyPressed(KEY_FOUR)) { QuickSort(numbers, 0, numbers.size() - 1); }
        if (IsKeyPressed(KEY_FIVE)) { MergeSort(numbers, 0, numbers.size() - 1); }
    }

    CloseWindow();
    return 0;
}