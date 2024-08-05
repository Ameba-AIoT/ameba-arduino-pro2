import os

def find_all_matches_and_extract_suffixes(folder_path, prefix, suffix):
    matches = []
    for root, dirs, files in os.walk(folder_path):
        for file_name in files:
            if file_name.startswith(prefix) and file_name.endswith(suffix):
                # Extract part after prefix
                result = file_name[len(prefix):]
                # Remove suffix
                if result.endswith(suffix):
                    result = result[:-len(suffix)]
                matches.append(result)
    return matches

def compare_and_keep_largest(data_list):
    def parse_version(version):
        return [int(part) for part in version.split('.')]

    while len(data_list) > 1:
        # Compare by each component
        max_a = max(parse_version(v)[0] for v in data_list)
        data_list = [v for v in data_list if parse_version(v)[0] == max_a]
        
        if len(data_list) == 1:
            break
        
        max_b = max(parse_version(v)[1] for v in data_list)
        data_list = [v for v in data_list if parse_version(v)[1] == max_b]
        
        if len(data_list) == 1:
            break
        
        max_c = max(parse_version(v)[2] for v in data_list)
        data_list = [v for v in data_list if parse_version(v)[2] == max_c]
        
        if len(data_list) == 1:
            break
        
        if len(parse_version(data_list[0])) == 4:
            max_d = max(parse_version(v)[3] for v in data_list if len(parse_version(v)) == 4)
            data_list = [v for v in data_list if len(parse_version(v)) == 4 and parse_version(v)[3] == max_d]
        
        break

    return data_list[0] if data_list else None

# Example usage:
folder_path = "./"  # Set to current directory
prefix = "ameba_pro2_tools_windows-"
suffix = ".tar.gz"

# Store the results in an array
results_array = find_all_matches_and_extract_suffixes(folder_path, prefix, suffix)

# Compare and keep the largest value data
largest_value_data = compare_and_keep_largest(results_array)

if largest_value_data:
    print(f"Largest value data: {largest_value_data}")
else:
    print("No matching data found.")

# Output the array (for verification)
print("\nStored results in array:")
print(results_array)
