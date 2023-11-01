long long mergeAndCount(vector<long long>& arr, long long l, long long m, long long r) {
    vector<long long> temp(r - l + 1);
    long long invCount = 0;
    long long i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else{
            temp[k++] = arr[j++];
            invCount += m - i + 1;}
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (long long p = 0; p < temp.size(); p++) arr[l + p] = temp[p];

    return invCount;
}

long long mergeSortAndCount(vector<long long>& arr, long long l, long long r) {
    long long invCount = 0;
    if (l < r) {
        long long m = l + (r - l) / 2;
        invCount += mergeSortAndCount(arr, l, m);
        invCount += mergeSortAndCount(arr, m + 1, r);
        invCount += mergeAndCount(arr, l, m, r);
    }
    return invCount;
}