// Assignment 01: 2Sum and Complexity
// CS 210
//
// Given an integer vector `nums` and an integer `target`, return the
// indices of two different elements whose values add to `target`.
// Exactly one valid pair is assumed to exist.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <string>

// ---------------------------------------------------------------------
// Approach 1: Brute force (nested loops, no hash table).
// For every pair (i, j) with i < j, check whether nums[i] + nums[j]
// equals target. Stops at the first match, which is fine here because
// the assignment guarantees exactly one valid pair exists.
// ---------------------------------------------------------------------
std::pair<int, int> twoSumBruteForce(const std::vector<int>& nums, int target) {
    int n = static_cast<int>(nums.size());
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    // No valid pair found (shouldn't happen given the assignment's guarantee).
    return {-1, -1};
}

// ---------------------------------------------------------------------
// Approach 2: Hash-based lookup, single pass.
// While scanning left to right, we ask "have I already seen the value
// that completes this pair?" before inserting the current value. That
// ordering also naturally prevents using the same element twice.
// Expected O(1) per lookup/insert with unordered_map, so overall
// expected O(n) time.
// ---------------------------------------------------------------------
std::pair<int, int> twoSumHash(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen; // value -> index
    int n = static_cast<int>(nums.size());
    for (int i = 0; i < n; ++i) {
        int complement = target - nums[i];
        auto it = seen.find(complement);
        if (it != seen.end()) {
            return {it->second, i};
        }
        seen[nums[i]] = i;
    }
    // No valid pair found (shouldn't happen given the assignment's guarantee).
    return {-1, -1};
}

// ---------------------------------------------------------------------
// Test harness
// ---------------------------------------------------------------------
void runCase(const std::string& label, const std::vector<int>& nums, int target) {
    std::cout << "=== " << label << " ===\n";
    std::cout << "target = " << target << "\n";

    std::pair<int, int> bf = twoSumBruteForce(nums, target);
    std::pair<int, int> hs = twoSumHash(nums, target);

    auto report = [&](const std::string& name, std::pair<int, int> result) {
        bool inRange = result.first >= 0 && result.second >= 0 &&
                       result.first < static_cast<int>(nums.size()) &&
                       result.second < static_cast<int>(nums.size());
        bool distinct = result.first != result.second;
        int sum = inRange ? nums[result.first] + nums[result.second] : 0;
        bool valid = inRange && distinct && sum == target;

        std::cout << "  " << name << ": indices = (" << result.first << ", "
                  << result.second << ")";
        if (inRange) {
            std::cout << ", values = (" << nums[result.first] << ", "
                       << nums[result.second] << "), sum = " << sum;
        }
        std::cout << ", valid = " << (valid ? "true" : "false") << "\n";
    };

    report("twoSumBruteForce", bf);
    report("twoSumHash      ", hs);
    std::cout << "\n";
}

int main() {
    // Required test case from the assignment.
    runCase("Required case",
             {15, 4, 18, 8, 19, 22, 24, 59, 59, 20, 18, 12, 36, 42, 9}, 24);

    // Additional case 1: negative numbers, target 0.
    runCase("Negative numbers, target 0", {-3, 4, 3, 90}, 0);

    // Additional case 2: the matching pair is a repeated value.
    runCase("Duplicate values as the pair", {3, 3, 7, 11}, 6);

    // Additional case 3: the matching pair sits at the very end.
    runCase("Pair at the end of the array", {1, 2, 3, 4, 5}, 9);

    // Additional case 4: negative target.
    runCase("Negative target", {5, -2, 10, -7, 1}, -9);

    return 0;
}
