import sys

def main():
    LIMIT = 10**9
    product = 1

    # Read 10 integers
    numbers = list(map(int, sys.stdin.readline().split()))

    # Ensure we have exactly 10 numbers
    if len(numbers) != 10:
        print("Error: Expected exactly 10 numbers")
        return

    for x in numbers:
        product *= x

        # Early termination if product exceeds limit
        if product > LIMIT:
            print(-1)
            return

    print(product)

if __name__ == "__main__":
    main()