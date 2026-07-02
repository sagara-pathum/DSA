
def insersion_sort(arr,n):
    for i in range(n):
        j = i
        while (j > 0 and arr[j-1] > arr[j]):
            temp = arr[j]
            arr[j] = arr[j-1]
            arr[j-1] = temp
            j = j-1
    return arr

user_array = []
n = int(input("Enter the number of elements : "))

for i in range(n):
    user_array.append(int(input(f"Enter the element {i+1} : ")))

print(user_array)
print(insersion_sort(user_array,n))
