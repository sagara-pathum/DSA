def selection_sort(arr, n):
    for i in range(n-1):
        min_idx = i;
        
        for j in range (i,n):
            if (arr[j] < arr[min_idx]):
                min_idx = j
        temp = arr[i]
        arr[i] = arr[min_idx]
        arr[min_idx] = temp
    return arr



user_array = []
n = int(input("Enter the number of elements : "))

for i in range(n):
    user_array.append(int(input(f"Enter the element {i+1} : ")))

print(user_array)
print(selection_sort(user_array,n))
