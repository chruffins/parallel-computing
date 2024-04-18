import matplotlib.pyplot as plt

RESULTS_FILE = "results.txt"

if __name__ == "__main__":
    fp = open("results.txt", 'r')
    lines = fp.readlines()
    
    data = [line.split() for line in lines]
    intervals = [int(x[0]) for x in data]
    error = [float(x[2]) for x in data]
    clocktime = [float(x[3]) for x in data]

    fig, (a1, a2) = plt.subplots(1, 2, figsize=(10, 5))

    # intervals vs. error approximation
    a1.plot(intervals, error, marker='o', linestyle='-', color='red')
    a1.set_xlabel("Intervals")
    a1.set_ylabel("Error")
    a1.set_xscale('log')
    a1.set_yscale('log')
    a1.set_title("Error as a Function of Integration Intervals")

    # intervals vs. wall clock time
    a2.plot(intervals, clocktime, marker='o', linestyle='-', color='green')
    a2.set_xlabel("Intervals")
    a2.set_ylabel("Time")
    a2.set_xscale('log')
    a2.set_yscale('log')
    a2.set_title("Time as a Function of Integration Intervals")

    plt.tight_layout()
    plt.savefig('plots.png')