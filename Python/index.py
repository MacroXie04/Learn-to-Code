import numpy as np
import multiprocessing as mp
import time

def fill_rand(length, seed=2531):
    """Generate an array of random numbers using a simple LCG algorithm."""
    RAND_MULT = 1366
    RAND_ADD = 150889
    RAND_MOD = 714025
    randy = seed
    a = np.zeros(length, dtype=np.float64)
    
    for i in range(length):
        randy = (RAND_MULT * randy + RAND_ADD) % RAND_MOD
        a[i] = randy / RAND_MOD
    
    return a

def sum_array_parallel(a, num_threads):
    """Sum an array in parallel using multiprocessing."""
    def worker(sub_array, result_queue):
        result_queue.put(np.sum(sub_array))
    
    chunk_size = len(a) // num_threads
    processes = []
    result_queue = mp.Queue()
    
    for i in range(num_threads):
        start_idx = i * chunk_size
        end_idx = None if i == num_threads - 1 else (i + 1) * chunk_size
        p = mp.Process(target=worker, args=(a[start_idx:end_idx], result_queue))
        processes.append(p)
        p.start()
    
    for p in processes:
        p.join()
    
    total_sum = sum(result_queue.get() for _ in range(num_threads))
    return total_sum

def test_performance(N, thread_counts):
    """Test sum_array_parallel with different thread counts and measure performance."""
    A = fill_rand(N)
    
    for num_threads in thread_counts:
        start_time = time.time()
        sum_result = sum_array_parallel(A, num_threads)
        elapsed_time = time.time() - start_time
        print(f"For {num_threads} threads, sum is {sum_result:.6f}, time taken: {elapsed_time:.6f} seconds")

if __name__ == "__main__":
    N = 100000000  # Reduce N for practical execution in Python
    thread_counts = [2, 4, 8, 16]
    test_performance(N, thread_counts)
