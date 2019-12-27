int removeElement(int* nums, int numsSize, int val) {
    int temp = 0;
    for(int i = 0; i < numsSize; i++) {
        if(nums[i] != val) nums[temp++] = nums[i];
    }
    return temp;
}