
def bubble_sort(arr,n):
    while(n > 0):
        k = n
        for i in range(1,k):
            if arr[i] < arr[i-1]:
                temp = arr[i]
                arr[i] = arr[i-1]
                arr[i-1] = temp
        n = n -1
    return arr

n = int(input("Number of element : "))
user_arr = []

for i in range(n):
    user_arr.append(int(input(f"Enter the number {i+1} : ")))

print(user_arr)
print(bubble_sort(user_arr,n))
