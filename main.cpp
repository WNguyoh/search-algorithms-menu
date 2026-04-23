#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int linearSearch(const vector<int>& arr, int key) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

int binarySearch(const vector<int>& arr, int key) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int hashSearch(const unordered_map<int, int>& hashTable, int key) {
    auto it = hashTable.find(key);
    if (it != hashTable.end())
        return it->second;
    return -1;
}

int main() {
    int n, key;
    char choice;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> sortedArr = arr;
    sort(sortedArr.begin(), sortedArr.end());

    unordered_map<int, int> hashTable;
    for (int i = 0; i < arr.size(); i++) {
        hashTable[arr[i]] = i;
    }

    double linearTime = 0, binaryTime = 0, hashTime = 0;

    do {
        cout << "\n===== MENU =====\n";
        cout << "a. Linear Search\n";
        cout << "b. Binary Search\n";
        cout << "c. Hashing\n";
        cout << "d. Compare all search times\n";
        cout << "e. Exit\n";
        cout << "Make your choice: ";
        cin >> choice;

        if (choice == 'a' || choice == 'b' || choice == 'c') {
            cout << "Enter element to search: ";
            cin >> key;
        }

        if (choice == 'a') {
            auto time1 = high_resolution_clock::now();
            int pos = linearSearch(arr, key);
            auto time2 = high_resolution_clock::now();

            linearTime = duration<double, micro>(time2 - time1).count();

            cout << "\nLinear Search\n";
            cout << "Time 1 recorded\n";
            cout << "Time 2 recorded\n";
            cout << "Time taken = Time 2 - Time 1 = " << fixed << setprecision(2) << linearTime << " microseconds\n";

            if (pos != -1)
                cout << "Element found at index " << pos << endl;
            else
                cout << "Element not found\n";
        }
        else if (choice == 'b') {
            auto time1 = high_resolution_clock::now();
            int pos = binarySearch(sortedArr, key);
            auto time2 = high_resolution_clock::now();

            binaryTime = duration<double, micro>(time2 - time1).count();

            cout << "\nBinary Search\n";
            cout << "Sorted array used for binary search.\n";
            cout << "Time 1 recorded\n";
            cout << "Time 2 recorded\n";
            cout << "Time taken = Time 2 - Time 1 = " << fixed << setprecision(2) << binaryTime << " microseconds\n";

            if (pos != -1)
                cout << "Element found at index " << pos << " in sorted array\n";
            else
                cout << "Element not found\n";
        }
        else if (choice == 'c') {
            auto time1 = high_resolution_clock::now();
            int pos = hashSearch(hashTable, key);
            auto time2 = high_resolution_clock::now();

            hashTime = duration<double, micro>(time2 - time1).count();

            cout << "\nHashing Search\n";
            cout << "Time 1 recorded\n";
            cout << "Time 2 recorded\n";
            cout << "Time taken = Time 2 - Time 1 = " << fixed << setprecision(2) << hashTime << " microseconds\n";

            if (pos != -1)
                cout << "Element found at index " << pos << endl;
            else
                cout << "Element not found\n";
        }
        else if (choice == 'd') {
            cout << "\n===== Comparison of Search Times =====\n";
            cout << "Linear Search Time : " << fixed << setprecision(2) << linearTime << " microseconds\n";
            cout << "Binary Search Time : " << fixed << setprecision(2) << binaryTime << " microseconds\n";
            cout << "Hashing Search Time: " << fixed << setprecision(2) << hashTime << " microseconds\n";

            if (linearTime == 0 || binaryTime == 0 || hashTime == 0) {
                cout << "Run all three searches first before making a full comparison.\n";
            } else {
                if (linearTime <= binaryTime && linearTime <= hashTime)
                    cout << "Fastest: Linear Search\n";
                else if (binaryTime <= linearTime && binaryTime <= hashTime)
                    cout << "Fastest: Binary Search\n";
                else
                    cout << "Fastest: Hashing\n";
            }
        }
        else if (choice == 'e') {
            cout << "Exiting program...\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 'e');

    return 0;
}
