use std::intrinsics::{fabsf64, needs_drop};

const PRECISION: f64 = 0.00001;

pub fn sqrt(input: i32) -> f64 {
    let mut left: f64 = 0.0;
    let mut right: f64 = input as f64;
    let mut mid: f64 = 0.0;
    unsafe {
        while fabsf64(mid*mid - input as f64) > PRECISION {
            if mid*mid < input as f64 {
                left = mid;
            } else {
                right = mid;
            }
            mid = left + ((right - left)/2.0);
        }
    }
    mid
}

pub fn find_first_number(nums: Vec<i32>, target: i32) -> i32{
    let mut low = 0;
    let mut high = nums.len() - 1;
    let mut mid = 0;

    while low <= high {
        mid = low + ((high - low) >> 1);
        if nums[mid] > target {
            high = mid - 1;
        } else if nums[mid] < target{
            low = mid + 1;
        } else {
            if mid == 0 || nums[mid-1] != target {
                return mid as i32;
            } else {
                high = mid - 1;
            }
        }
    }
    -1
}

pub fn find_first_number_easy(nums: Vec<i32>, target: i32) -> i32{
    let mut low = 0;
    let mut high = nums.len() - 1;
    let mut mid = 0;

    while low <= high {
        mid = low + ((high - low) >> 1);
        if nums[mid] >= target {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if low < nums.len() && nums[low] == target {
        low as i32
    } else {
        -1
    }
}

pub fn find_last_number(nums: Vec<i32>, target: i32) -> i32{
    let mut low = 0;
    let mut high = nums.len() - 1;
    let mut mid = 0;

    while low <= high {
        mid = low + ((high - low) >> 1);
        if nums[mid] > target {
            high = mid - 1;
        } else if nums[mid] < target{
            low = mid + 1;
        } else {
            if mid == nums.len()-1 || nums[mid+1] != target {
                return mid as i32;
            } else {
                low = mid + 1;
            }
        }
    }
    -1
}

pub fn find_last_number_easy(nums: Vec<i32>, target: i32) -> i32{
    let mut low = 0;
    let mut high = nums.len() - 1;
    let mut mid = 0;

    while low <= high {
        mid = low + ((high - low) >> 1);
        if nums[mid] > target {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if high < nums.len() && nums[high] == target {
        high as i32
    } else {
        -1
    }
}

pub fn find_first_lt_number(nums: Vec<i32>, target: i32) -> i32{
    let mut low = 0;
    let mut high = nums.len() - 1;
    let mut mid = 0;

    while low <= high {
        mid = low + ((high - low) >> 1);
        if nums[mid] > target {
            high = mid - 1;
            if mid == 0 || nums[mid-1] <= target {
                return mid as i32;
            } else {
                high = mid - 1;
            }
        } else {
            low = mid + 1;
        }
    }
    -1
}

pub fn find_last_le_number(nums: Vec<i32>, target: i32) -> i32{
    let mut low = 0;
    let mut high = nums.len() - 1;
    let mut mid = 0;

    while low <= high {
        mid = low + ((high - low) >> 1);
        if nums[mid] >= target {
            high = mid - 1;
        } else {
            if mid == nums.len() || nums[mid+1] >= target {
                return mid as i32;
            } else {
                low = mid + 1;
            }
        }
    }
    -1
}

pub fn search_in_a_rotated_sorted_array(nums: Vec<i32>, target: i32) -> i32 {
    if nums.len() <= 0 {
        return -1;
    }
    let mut left = 0;
    let mut right = nums.len() - 1;
    let mut mid = 0;

    while left <= right {
        mid = left + ((right - left) >> 1);
        if nums[mid] == target {
            return mid as i32;
        }
        if nums[left] < nums[mid] {
            if nums[mid] > target && nums[left] <= target {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if nums[mid] < target && nums[right] >= target {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    -1
}

pub fn search_first_in_a_rotated_sorted_array_with_dup(nums: Vec<i32>, target: i32) -> i32 {
    if nums.len() <= 0 {
        return -1;
    }
    let mut left = 0;
    let mut right = nums.len() - 1;
    let mut mid = 0;

    while left <= right {
        mid = left + ((right - left) >> 1);
        if nums[mid] == target {
            if nums[0] == target {
                return 0;
            } else if nums[mid-1] != target {
                return mid as i32;
            } else {
                right = mid - 1;
                continue
            }
        }

        if nums[left] < nums[mid] {
            if nums[mid] > target && nums[left] <= target {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if nums[mid] < target && nums[right] >= target {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    -1
}

mod tests {
    use super::*;
    #[test]
    pub fn test_sqrt() {
        println!("{:?}", sqrt(2));
    }

    #[test]
    pub fn test_find_first_number() {
        assert_eq!(find_first_number(vec![1,2,3,4,4,4,5,6], 4), 3);
        assert_eq!(find_first_number_easy(vec![1,2,3,4,4,4,5,6], 4), 3);
    }

    #[test]
    pub fn test_find_last_number() {
        assert_eq!(find_last_number(vec![1,2,3,4,4,4,5,6], 4), 5);
        assert_eq!(find_last_number_easy(vec![1,2,3,4,4,4,5,6], 4), 5);
    }

    #[test]
    pub fn test_find_first_lt_number() {
        assert_eq!(find_first_lt_number(vec![1,2,3,4,4,4,5,6], 4), 6);
    }

    #[test]
    pub fn test_find_last_le_number() {
        assert_eq!(find_last_le_number(vec![1,2,3,4,4,4,5,6], 4), 2);
    }

    #[test]
    pub fn test_search_in_a_rotated_sorted_array() {
        assert_eq!(search_in_a_rotated_sorted_array(vec![4,5,6,1,2,3], 2), 4);
    }

    #[test]
    pub fn test_search_in_a_rotated_sorted_array_with_dup() {
        assert_eq!(search_first_in_a_rotated_sorted_array_with_dup(vec![4,5,6,1,2,2,3], 2), 4);
    }
}