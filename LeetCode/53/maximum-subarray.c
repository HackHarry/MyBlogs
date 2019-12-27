int maxSubArray(int* nums, int numsSize) {
    for(int i = 1; i < numsSize; i++) {
        nums[i] += nums[i-1];
    }
    int max = nums[0];
    for(int i = 1; i < numsSize; i++) {
        if(max < nums[i]) max = nums[i];
    }
    for(int i = 0; i < numsSize-1; i++) {
        for(int j = i+1; j < numsSize; j++) {
            if(nums[j]-nums[i] > max) max = nums[j] - nums[i];
        }
    }
    return max;
}

----------------------------------------------------

int maxSubArray(int* nums, int numsSize) {
    int res=nums[0];
    int sum=0;
    for(int i=0;i<numsSize;i++)
    {
        if(sum>0)
            sum+=nums[i];
        else
            sum=nums[i];
        res=res>sum?res:sum;
    }
    return res;
}