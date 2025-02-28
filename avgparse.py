import argparse

# Function to compute the average latency and packet size from a file
def compute_averages(file_path):
    latencies = []  # List to store latency values
    packet_sizes = []  # List to store packet size values
    
    # Read the file and extract latencies and packet sizes
    with open(file_path, 'r') as f:
        for line in f:
            try:
                # Split the line into latency and packet size
                latency, packet_size = line.strip().split()  # Assuming space or tab separates columns
                latency = float(latency)  # Convert latency to float
                packet_size = float(packet_size)  # Convert packet size to float
                latencies.append(latency)
                packet_sizes.append(packet_size)
            except ValueError:
                # Handle any lines that are not valid floats
                print("Skipping invalid line: {}".format(line.strip()))
    
    # Check if there are valid latencies and packet sizes
    if latencies and packet_sizes:
        # Compute the averages
        avg_latency = sum(latencies) / len(latencies)
        avg_packet_size = sum(packet_sizes) / len(packet_sizes)
        return avg_latency, avg_packet_size
    else:
        return None, None  # If there are no valid entries

def main():
    # Set up the argument parser
    parser = argparse.ArgumentParser(description="Compute average latency and packet size from a file.")
    
    # Add argument for the file path
    parser.add_argument('file_path', help="Path to the file containing latencies and packet sizes")
    
    # Parse the command line arguments
    args = parser.parse_args()
    
    # Compute and print the average latency and packet size
    avg_latency, avg_packet_size = compute_averages(args.file_path)
    if avg_latency is not None and avg_packet_size is not None:
        print(f"Average Latency: {avg_latency:.6f} seconds")
        print(f"Average Packet Size: {avg_packet_size:.2f} bytes")
    else:
        print("No valid data found in the file.")

if __name__ == "__main__":
    main()
