from bs4 import BeautifulSoup
import re
import os

# --- Configuration ---
HTML_FILE = "report.html"  # Name of the file containing the HTML
INPUT_FILE = "inputs.txt"
OUTPUT_FILE = "expected_outputs.txt"
# --- End Configuration ---


def extract_test_data_by_markers(html_filepath):
    """
    Parses the HTML file, finds input and expected output sections based on
    text markers ("--- Input ---", "--- Expected output ---"), groups them
    by test number ("-Test X:"), and returns them as lists of strings.
    """
    all_inputs_data = []
    all_outputs_data = []

    try:
        with open(html_filepath, "r", encoding="utf-8") as f:
            html_content = f.read()
    except FileNotFoundError:
        print(f"Error: HTML file '{html_filepath}' not found.")
        return None, None

    # Use 'html.parser' as a fallback if lxml isn't installed or preferred
    # Install lxml (pip install lxml) for better performance and handling
    soup = BeautifulSoup(html_content, "lxml")

    if not soup.body:
        print("Error: Could not find the <body> tag in the HTML.")
        return None, None

    # Get all non-empty text strings from the body
    # Using stripped_strings is generally better than get_text() here
    lines = list(soup.body.stripped_strings)

    # Use regex to find lines that contain all the markers we are interested in
    pattern = re.compile(
        r"^(?=.*?--- Input ---)(?=.*?--- Program output ---)(?=.*?--- Expected output).*",
        re.DOTALL,
    )
    matches = [line for line in lines if pattern.search(line)]

    if not matches:
        print("No relevant sections found in the HTML file.")
        return None, None

    # Extract input and output data based on the markers
    for line in matches:
        # Extract the test number
        test_number = re.search(r"Test (\d+):", line)
        if test_number:
            test_number = test_number.group(1)
            # Extract input data
            input_data = re.search(r"Input\s*(.*?)\s*Program output", line, re.DOTALL)
            if input_data:
                all_inputs_data.append(
                    f"Test {test_number}:\n{input_data.group(1).strip()}"
                )
            # Extract expected output data
            output_data = re.search(r"Expected output\s*(.*?)\s*$", line, re.DOTALL)
            if output_data:
                all_outputs_data.append(
                    f"Test {test_number}:\n{output_data.group(1).strip()}"
                )

    return all_inputs_data, all_outputs_data


def write_data_to_file(filename, data_list):
    """Writes a list of strings to a file, one string per line."""
    if data_list is None:
        return  # Do nothing if data extraction failed

    if not data_list:
        print(f"No relevant data found to write to {filename}.")
        # Optionally create an empty file or write a message
        # with open(filename, 'w', encoding='utf-8') as f:
        #     f.write("No relevant input/output data extracted based on markers.\n")
        return

    try:
        with open(filename, "w", encoding="utf-8") as f:
            for item in data_list:
                f.write(item + "\n")
        print(f"Data successfully saved to {filename}")
    except IOError as e:
        print(f"Error writing to file {filename}: {e}")


# --- Main Execution ---
if __name__ == "__main__":
    print(f"Attempting to extract data from: {HTML_FILE}")
    # Use the new function name
    inputs, outputs = extract_test_data_by_markers(HTML_FILE)

    if inputs is not None:
        write_data_to_file(INPUT_FILE, inputs)
    else:
        print("Input data extraction failed.")

    if outputs is not None:
        write_data_to_file(OUTPUT_FILE, outputs)
    else:
        print("Output data extraction failed.")
