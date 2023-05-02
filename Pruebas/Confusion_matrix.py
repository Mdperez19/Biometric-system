import os
from typing import Dict, List, Tuple
import numpy as np
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
import pandas as pd


def generate_binary_lists_with_shift(shift_size: int, list_length: int, file_data: Dict[str, List[int]]) \
        -> Dict[str, List[List[int]]]:
    """Generates a dictionary of binary lists for each file in file_data,
    each with a shift of `shift_size` ones for each iteration."""
    predicted_lists = {}
    shift_count = 0
    iteration_count = 1

    for file_name, values in file_data.items():
        binary_list = np.zeros(list_length, dtype=int)
        binary_list[:shift_size] = 1  # Set the first `shift_size` elements to 1
        binary_list = np.roll(binary_list,
                              shift_size * shift_count)  # Shift the list `shift_size * shift_count` times
        predicted_lists[file_name] = binary_list.tolist()

        # Increment the shift count after every `shift_size` iterations
        if iteration_count % shift_size == 0:
            shift_count += 1
        iteration_count += 1

    return predicted_lists


def read_files_from_folder(folder_path: str) -> Dict[str, list[int]]:
    """Reads all files with .txt extension from a folder and returns their content as a dictionary."""
    files = os.listdir(folder_path)
    data = {}
    for file in files:
        if file.endswith('.txt'):
            with open(os.path.join(folder_path, file)) as f:
                lines = f.readlines()
                data[file] = [int(line.strip()) for line in lines]
    return data


if __name__ == "__main__":
    n = 4
    length = 12
    # Read binary lists from files
    folder_path = 'Resultados/6'
    data = read_files_from_folder(folder_path)

    # Generate predicted binary list for each file
    predicted = generate_binary_lists_with_shift(n, length, data)

    # Calculate confusion matrix
    y_true = []
    y_pred = []
    for file, values in data.items():
        y_true += values
        y_pred += predicted[file]

    confusion_matrix_result = confusion_matrix(y_true, y_pred)

    # Create Pandas DataFrame and format table
    df = pd.DataFrame(confusion_matrix_result,
                      columns=['True Accepted', 'True Rejected'],
                      index=['False Accepted', 'False Rejected'])
    df.style.set_caption("Confusion Matrix").format("{:,.0f}")
    print(df, end='\n\n')

    # Calculate precision, recall and f1-score
    print(classification_report(y_true, y_pred))
