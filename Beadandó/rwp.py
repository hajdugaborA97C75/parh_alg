import random
import math
import threading
import time

RADIUS = 10000.0
NUM_THREADS = 5

def simulate_steps():
    x = 0.0
    y = 0.0
    steps = 0

    while math.sqrt(x * x + y * y) < RADIUS:
        angle = random.uniform(0, 2 * math.pi)
        x += math.cos(angle)
        y += math.sin(angle)
        steps += 1

    return steps

def thread_function():
    steps = simulate_steps()
    thread_id = threading.get_ident()
    f = open("python.csv", "a")
    f.write(f"{steps},")
    f.close()

def main():
    threads = []

    start_time = time.time()

    for _ in range(NUM_THREADS):
        thread = threading.Thread(target=thread_function)
        thread.start()
        threads.append(thread)

    for thread in threads:
        thread.join()
    
    end_time = time.time()
    execution_time = end_time - start_time

    f = open("python.csv", "a")
    f.write(f"{int(RADIUS)},{execution_time:.2f}\n")
    f.close()

if __name__ == "__main__":
    main()
