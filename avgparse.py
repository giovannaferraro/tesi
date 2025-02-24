import argparse

# Function to compute the average from a file of latencies
def compute_average_latency(file_path):
    latencies = []  # List to store latency values
    
    # Read the file and extract latencies
    with open(file_path, 'r') as f:
        for line in f:
            try:
                # Convert each line to float and append to the list
                latency = float(line.strip())  # strip() removes leading/trailing whitespace
                latencies.append(latency)
            except ValueError:
                # Handle any lines that are not valid floats (if necessary)
                print("Skipping invalid value: {}".format(line.strip()))
    
    if latencies:  # Check if the list is not empty
        # Compute the average latency
        average_latency = sum(latencies) / len(latencies)
        return average_latency
    else:
        return None  # If the list is empty, return None

def main():
    # Set up the argument parser
    parser = argparse.ArgumentParser(description="Compute average latency from a file.")
    
    # Add argument for the file path
    parser.add_argument('file_path', help="Path to the file containing latencies")
    
    # Parse the command line arguments
    args = parser.parse_args()
    
    # Compute and print the average latency
    average = compute_average_latency(args.file_path)
    if average is not None:
        print("Average Latency: {:.6f} seconds".format(average))
    else:
        print("No valid latencies found in the file.")

if __name__ == "__main__":
    main()
