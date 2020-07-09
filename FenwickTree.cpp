#include<iostream>
#include<vector>
#include<climits>

class FenwickTree {
public:
    FenwickTree(const std::vector<int>& arr) : sums_(arr.size() + 1, 0) {
        for (int i = 0; i < arr.size(); i++)
            update(i + 1, arr[i]);
    }
    void update(int i, int delta) {
        while (i < sums_.size()) {
            sums_[i] += delta;
            i += lowbit(i);
        }
    }

    // 返回arr[0...i]之和
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += sums_[i];
            i -= lowbit(i);
        }
        return sum;
    }

    // 返回arr[i...j]之和
    int query(int i, int j) {
        if (j > i)  return query(j + 1) - query(i);
        return INT_MIN;
    }

private:
    static inline int lowbit(int x) { return x & (-x); }
    std::vector<int> sums_;
};

int main() {
    std::vector<int> arr{1, 2, 3, 4, 5, 6};
    FenwickTree bit(arr);
    int i1 = 0, j1 = 3;
    int i2 = 2, j2 = 4;
    int delta = 3;
    printf("Sum of [%d...%d] is\t%d\n", i1, j1, bit.query(i1, j1));
    printf("Sum of [%d...%d] is\t%d\n", i2, j2, bit.query(i2, j2));
    bit.update(2, delta);
    printf("Sum of [%d...%d] is\t%d\n", i1, j1, bit.query(i1, j1));
    printf("Sum of [%d...%d] is\t%d\n", i2, j2, bit.query(i2, j2));
}