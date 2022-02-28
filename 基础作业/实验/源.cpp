#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#define in_filename "mergesort.in"
#define out_filename "mergesort.out"

class Merge {
public:
    static void sort(std::vector<int>& nums) {
        int n = nums.size();
        for (int size = 1; size < n; size *= 2) {
            for (int low = 0; low < n - size; low += 2 * size) {
                merge(nums, low, low + size - 1, std::min(n - 1, low + size * 2 - 1));
            }
        }
    }
private:
    static void merge(std::vector<int>& nums, int l, int m, int r) {
        int n = nums.size();
        std::vector<int> temp(n);
        int i = l, j = m + 1;
        for (int k = l; k <= r; ++k)
            temp[k] = nums[k];
        for (int k = l; k <= r; ++k) {
            if (k > m)    nums[k++] = temp[j++];
            else if (k > r)    nums[k++] = temp[i++];
            else if (temp[i] < temp[j])    nums[k++] = temp[i++];
            else    nums[k++] = temp[j++];
        }
    }
};

int main(void) {
    std::ifstream input(in_filename);
    std::ofstream output(out_filename);
    if (input.fail()) {
        output << "输入文件打开失败!" << std::endl;
    }
    else {
        std::vector<int> nums;
        std::string line;
        std::istringstream record(line);
        getline(input, line);
        std::string num;
        record >> num;
        int n = stoi(num);
        getline(input, line);
        std::cout << line << std::endl;
        for (int i = 0; i < n; ++i) {
            std::string temp;
            record >> temp;
            std::cout << temp << " ";
            nums.emplace_back(std::stoi(temp));
        }
        Merge::sort(nums);
        for (int i = 0; i < n; ++i) {
            output << nums[i];
            if (i < n - 1)     output << " ";
        }
        input.close();
    }
    output.close();
    return 0;
}