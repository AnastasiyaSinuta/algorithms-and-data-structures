#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <fstream>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// ����������� ����������
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// ������� ����������
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int partitionIndex = i + 1;

        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

// ������� ��� ������ �������
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<int> array(100);
    ofstream fout("array100.txt");
    /*string input;

    cout << "������� �����, ����������� ���������: " << endl;
    getline(cin, input);
    cout << endl;

    istringstream iss(input);
    int num;
    while (iss >> num) {
        array.push_back(num);
    }*/

    for (int i = 0; i < 100; i++) {
        array[i] = rand() % 2000 - 1000;
    }
    for (int i = 0; i < 100; i++) {
        fout << array[i] << " ";
    }

    vector<int> arr1 = array;
    vector<int> arr2 = array;

    // �������� ����� ���������� ����������� ����������
    auto start = high_resolution_clock::now();
    bubbleSort(arr1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "��������������� ������ (����������� ����������): " << endl;
    printArray(arr1);
    cout << "����� ���������� (����������� ����������): " << duration.count() << " �����������" << endl << endl;

    // �������� ����� ���������� ������� ����������
    start = high_resolution_clock::now();
    quickSort(arr2, 0, arr2.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "��������������� ������ (������� ����������): " << endl;
    printArray(arr2);
    cout << "����� ���������� (������� ����������): " << duration.count() << " �����������" << endl;

    return 0;
}
