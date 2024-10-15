from subprocess import run


# Compile the C++ program
run(["g++", "main.cpp", "-O3", "-o", "a"], check=True)

# Run the compiled program with different arguments
for i in range(1, 6):
    run([f"./a", "grafo_W_" + str(i) + ".txt"], check=True)