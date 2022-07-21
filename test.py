import numpy as np

a = np.array([
    3, 2, 4, 2, 3,
        6, 6, 4, 1, 7,
        2, 1, 7, 3, 5,
        1, 0, 4, 4, 1,
        5, 3, 0, 2, 9,
]).reshape(5, 5)

b = np.array([4, 5, 6, 3, 4])

print(np.linalg.solve(a, b))