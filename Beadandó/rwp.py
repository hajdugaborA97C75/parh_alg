import random
import math
import threading
import time

RADIUS = 500.0
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
    print(f"A(z) {thread_id} azonosítójú szál {steps} lépést tett meg.")

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

    print(f"\nA szimuláció teljes futási ideje: {execution_time:.2f} másodperc.")


if __name__ == "__main__":
    main()
