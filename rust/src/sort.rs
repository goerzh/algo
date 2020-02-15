use std::slice;
use std::ptr::slice_from_raw_parts;
use std::i32;

pub fn bubble_sort(v: &mut [i32]){
    let mut i = 0;
    let mut changed = false;
    while i < v.len() {
        let mut j = 1;
        while j < v.len() - i {
            if v[j-1] > v[j] {
                let temp = v[j-1];
                v[j-1] = v[j];
                v[j] = temp;

                changed = true;
            }
            j += 1;
        }
        if !changed {break}
        i += 1;
    }
}

pub fn insert_sort(v: &mut [i32]) {
    let mut i: usize = 1;
    while i < v.len() {
        let value = v[i];
        let mut j = i;
        while j > 0 {
            if v[j-1] > value {
                v[j] = v[j-1];
            } else {
                break
            }
            j -= 1;
        }
        v[j] = value;

        i += 1;
    }
}

pub fn selection_sort(v: &mut [i32]) {
    let mut i = 0;
    while i < v.len() {
        let mut value = v[i];
        let mut index = i;
        let mut j = i + 1;
        while j < v.len() {
            if v[j] < value {
                value = v[j];
                index = j;
            }
            j += 1;
        }
        v[index] = v[i];
        v[i] = value;

        i += 1;
    }
}

pub fn merge_sort(v: &mut [i32]) {
    merge_sort_c(v, 0, v.len()-1);
}

fn merge_sort_c(v: &mut [i32], b: usize, e: usize) {
    if b >= e {return;}

    let m = (e + b) / 2;
    merge_sort_c(v, b, m);
    merge_sort_c(v, m+1, e);

    merge_guard(v, b, m, e);
}

fn merge(v: &mut [i32], b: usize, m: usize, e: usize) {
    let (mut i, mut j) = (b, m+1);
    let mut temp  = vec![];
    while i <= m && j <= e {
        if v[i] <= v[j] {
            temp.push(v[i]);
            i += 1;
        } else {
            temp.push(v[j]);
            j += 1;
        }
    }

    let mut l= i;
    let mut r= m;

    if j <= e {
        l = j;
        r = e;
    }

    while l <= r {
        temp.push(v[l]);
        l += 1;
    }

    let mut i = 0;
    while i < e-b+1 {
        v[b+i] = temp[i];
        i += 1;
    }
}

pub fn merge_guard(v: &mut [i32], b: usize, m: usize, e: usize) {
    let mut left = Vec::with_capacity(m-b+1);
    let mut right = Vec::with_capacity(e-m);

    let (mut i, mut j) = (b, m+1);
    while i <= m {
        left.push(v[i]);
        i += 1;
    }
    while j <= e {
        right.push(v[j]);
        j += 1;
    }
    left.push(i32::MAX);
    right.push(i32::MAX);

    let (mut i, mut j, mut index) = (0, 0, b);
    while index <= e  {
        if left[i] <= right[j] {
            v[index] = left[i];
            i += 1;
        } else {
            v[index] = right[j];
            j += 1;
        }
        index += 1;
    }
}

pub fn quick_sort(v: &mut [i32]) {
    quick_sort_c(v, 1, v.len());
}

fn quick_sort_c(v: &mut [i32], b: usize, e: usize) {
    if b >= e { return; }

    let m = partition(v, b, e);
    quick_sort_c(v, b, m-1);
    quick_sort_c(v, m+1, e);
}

fn partition(v: &mut [i32], b: usize, e: usize) -> usize {
    let (mut i, mut j): (usize, usize) = (b-1, b-1);
    let pivot = v[e-1];
    while j <= e-1 {
        if v[j] < pivot {
            let temp = v[j];
            v[j] = v[i];
            v[i] = temp;
            i += 1;
        }
        j += 1;
    }
    v[e-1] = v[i];
    v[i] = pivot;

    i+1
}

mod tests{
    #[test]
    pub fn test_sorts() {
        use super::*;
        let mut v = [4, 3, 2, 6, 7, 1, 5];
        bubble_sort(&mut v);
        assert_eq!(v, [1, 2, 3, 4, 5, 6, 7]);

        let mut v = [4, 3, 2, 6, 7, 1, 5];
        insert_sort(&mut v);
        assert_eq!(v, [1, 2, 3, 4, 5, 6, 7]);

        let mut v = [4, 3, 2, 6, 7, 1, 5];
        selection_sort(&mut v);
        assert_eq!(v, [1, 2, 3, 4, 5, 6, 7]);

        let mut v = [4, 3, 2, 6, 7, 1, 5];
        merge_sort(&mut v);
        assert_eq!(v, [1, 2, 3, 4, 5, 6, 7]);

        let mut v = [4, 3, 2, 6, 7, 1, 5];
        quick_sort(&mut v);
        assert_eq!(v, [1, 2, 3, 4, 5, 6, 7]);
    }

    #[test]
    pub fn benchmark() {

    }
}