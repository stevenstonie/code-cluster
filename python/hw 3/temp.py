# from timeit import timeit
import numpy as np
# from numba import jit

def min_max_scale(a: np.ndarray)->tuple():
    """finds the min and max of 'a'. creates 'b', scaled between 0 and 1 based on 'a' and returns a tuple of 'b', min(a) and max(a)."""
    minimum, maximum=a.min(), a.max()
    b=(a-minimum)/(maximum-minimum)
    return b, minimum, maximum

def check_scaling(y: np.ndarray, eps: float = 1e-5)->bool:
    """returns true if the elem of the array are between 0 and 1"""
    assert eps > 0
    return -eps < y.min() and y.max() < 1 + eps

def inverse_min_max_scale(y: np.ndarray, MIN: float, MAX: float): # de adnotat, docstring
    assert MAX > MIN
    return y * (MAX - MIN) + MIN

if __name__ =='__main__':
    m, n = 100, 200
    a = np.random.randn(m, n)
    print(a, "\n\n")
    assert check_scaling(min_max_scale(a)[0])
    b, MIN, MAX = min_max_scale(a)
    print(b)
    assert np.allclose(a, inverse_min_max_scale(b, MIN, MAX))