import numpy as np

def generate_random_matrix(size):
    return np.random.randint(-1e7, 1e7, size=(size, size))

def multiply_matrices(matrix1, matrix2):
    return np.dot(matrix1, matrix2)

def main():
    size = 5
    matrix1 = generate_random_matrix(size)
    matrix2 = generate_random_matrix(size)
    
    result = multiply_matrices(matrix1, matrix2)
    
    with open("Arquivos/output.txt", "w") as f:
        for row in matrix1:
            f.write(" ".join(map(str, row)) + "\n")
        f.write("\n")
        
        for row in matrix2:
            f.write(" ".join(map(str, row)) + "\n")
        f.write("\n")

        for row in result:
            f.write(" ".join(map(str, row)) + "\n")

if __name__ == "__main__":
    main()