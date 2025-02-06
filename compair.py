def read_number_from_file(file_path):
    with open(file_path, 'r') as file:
        number = file.read().strip()
    return number

def find_first_difference(file1, file2):
    number1 = read_number_from_file(file1)
    number2 = read_number_from_file(file2)

    length1 = len(number1)
    length2 = len(number2)
    min_length = min(length1, length2)

    for i in range(min_length):
        if number1[i] != number2[i]:
            print(f"The numbers differ at digit position {i+1}.")
            print(f"Digit in {file1}: {number1[i]}")
            print(f"Digit in {file2}: {number2[i]}")
            return

    if length1 != length2:
        print(f"The numbers are identical up to position {min_length}.")
        print(f"However, the lengths of the numbers differ.")
        print(f"Length of number in {file1}: {length1}")
        print(f"Length of number in {file2}: {length2}")
    else:
        print("The numbers are identical.")

if __name__ == "__main__":
    file1 = 'output.txt'
    file2 = 'truepi.txt'
    find_first_difference(file1, file2)
