#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<random>

// The sorted range is [left, right] (two sides are both closed)

int partition(std::vector<int>& arr, int left, int right) {
    int pivot = arr[left];
    while (left < right) {
        while (left < right && arr[right] > pivot)  right--;
        arr[left] = arr[right];
        while (left < right && arr[left] < pivot)   left++;
        arr[right] = arr[left];
    }
    arr[left] = pivot;
    return left;
}

void quickSort(std::vector<int>& arr, int left, int right) {
    if (left >= right)  return;
    int idx = partition(arr, left, right);
    quickSort(arr, left, idx - 1);
    quickSort(arr, idx + 1, right);
}

std::vector<int>& generateRandom(std::vector<int>& arr, int size) {
    std::set<int> s;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 1000);
    while (s.size() < size) s.insert(distribution(generator));
    arr = std::vector<int>(s.begin(), s.end());
    return arr;
}

int main() {
    std::vector<int> myvec, stlvec;
    generateRandom(myvec, 100);
    stlvec = myvec;

    quickSort(myvec, 0, myvec.size()-1);
    // sort(stlvec.begin(), stlvec.end());

    bool sortRight = true;
    for (int i = 0; sortRight && i < myvec.size() - 1; i++) {
        sortRight &= (myvec[i] < myvec[i+1]);
    }
    printf("\n");
    
    if (sortRight)  std::cout << "Your quick sort works well." << std::endl;
    else            std::cout << "Your qucik sort is wrong." << std::endl;
    return 0;
}