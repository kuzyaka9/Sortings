##
#  @file graphics.py
#  @brief Файл, который строит графики о времени выполнения сортировки массивов
#


#- @cond
import matplotlib.pyplot as plt

file = open("timestamps.txt", "r")
lines = file.readlines()

array_sizes = []
bubble_time = []
insert_time = []
qsort_time = []

for i in range(len(lines)):
    if i%4 == 0:
        array_sizes.append(int(lines[i]))
    elif i%4 == 1:
        bubble_time.append(int(lines[i]))
    elif i%4 == 2:
        insert_time.append(int(lines[i]))
    else:
        qsort_time.append(int(lines[i]))


plt.plot(array_sizes, bubble_time, ':o', label="Bubble_sort")
plt.plot(array_sizes, insert_time, ':o', label="Insert_sort")
plt.plot(array_sizes, qsort_time, ':o', label="Quicksort")
plt.legend()
plt.show()
#- @encond