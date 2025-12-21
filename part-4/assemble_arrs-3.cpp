#include <vector>
#include <iostream>

// Введите элементы первого массива: 1 3 5 7 9
// Введите элементы второго массива: 2 4 6 8 10
// Массив-результат: 1 2 3 4 5 6 7 8 9 10
void assemble_arrs(const std::vector<int> &arr1, const std::vector<int> &arr2, std::vector<int> &res) {
    const int n1 = arr1.size();
    const int n2 = arr2.size();
    res.resize(n1 + n2);
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            res[k++] = arr1[i++];
        } else {
            res[k++] = arr2[j++];
        }
    }

    while (i < n1) {
        res[k++] = arr1[i++];
    }

    while (j < n2) {
        res[k++] = arr2[j++];
    }
}

int main(int argc, char *argv[]) {
    std::vector<int> arr1{1, 3, 5, 7, 9};
    std::vector<int> arr2{2, 4, 6, 8, 10};
    std::vector<int> res;

    assemble_arrs(arr1, arr2, res);

    std::cout << "sorted array: " << std::endl;
    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;

}