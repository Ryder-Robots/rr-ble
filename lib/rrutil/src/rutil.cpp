#include "rrutil.hpp"

// Assumes String results[] has at least maxParts elements
int rrobot::split_string(const String& input, char delimiter, String results[], int maxParts) {
    int partCount = 0;
    int start = 0;
    int end = 0;

    while (end >= 0 && partCount < maxParts) {
        end = input.indexOf(delimiter, start);
        if (end == -1) {
            // Last part
            results[partCount++] = input.substring(start);
            break;
        } else {
            results[partCount++] = input.substring(start, end);
            start = end + 1;
        }
    }
    return partCount;
}

int rrobot::binary_search(const int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}