import sys

def main():
    # Read two integers from input
    line = sys.stdin.readline().strip()
    a, b = map(int, line.split())

    # Print the sum
    print(a + b)

if __name__ == "__main__":
    main()