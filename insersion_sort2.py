
def insersion_sort(arr,n):
    for i in range(1,n):
        key = arr[i]
        j = i - 1
        while (j >= 0 and arr[j] > key):
            arr[j+1] = arr[j] 
            j = j - 1
        arr[j+1] = key
    return arr

user_array = []
n = int(input("Enter the number of elements : "))

for i in range(n):
    user_array.append(int(input(f"Enter the element {i+1} : ")))

print(user_array)
print(insersion_sort(user_array,n))
