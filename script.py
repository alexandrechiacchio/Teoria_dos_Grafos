from subprocess import run
from multiprocessing import Process
from threading import Thread

# Compile the C++ program
run(["g++", "main.cpp", "-O3", "-o", "a"], check=True)

# Run the compiled program with different arguments
processes = []
for i in range(1, 6):
    processes.append(Process(target=run, args=(["./a", 'grafo_W_' + str(i) + '.txt'],), kwargs={"check": True}))
    processes[-1].deamon = True

for i in processes:
    i.start()

for i in processes:
    i.join()