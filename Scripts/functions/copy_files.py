import shutil
import os

def copy_files(source_directory, destination_directory):
    # Ensure the source directory exists
    if not os.path.exists(source_directory):
        print(f"Source directory '{source_directory}' does not exist.")
        return

    # Ensure the destination directory exists, create it if not
    if not os.path.exists(destination_directory):
        os.makedirs(destination_directory)

    # Get a list of files in the source directory
    files = os.listdir(source_directory)

    for file in files:
        # Construct the full file paths
        source_path = os.path.join(source_directory, file)
        destination_path = os.path.join(destination_directory, file)

        # Copy the file to the destination directory
        shutil.copy2(source_path, destination_path)
        print(f"File '{file}' copied to '{destination_directory}'.")


def copy_files_by_extension(source_directory, destination_directory, extension=".lib"):
    # Ensure the source directory exists
    if not os.path.exists(source_directory):
        print(f"Source directory '{source_directory}' does not exist.")
        return

    # Ensure the destination directory exists, create it if not
    if not os.path.exists(destination_directory):
        os.makedirs(destination_directory)

    # Recursively walk through the source directory and its subdirectories
    for foldername, subfolders, filenames in os.walk(source_directory):
        for filename in filenames:
            # Check if the file has the desired extension
            if filename.endswith(extension):
                # Construct the full file paths
                source_path = os.path.join(foldername, filename)
                relative_path = os.path.relpath(source_path, source_directory)
                destination_path = os.path.join(destination_directory, relative_path)

                # Create the destination directory if it doesn't exist
                os.makedirs(os.path.dirname(destination_path), exist_ok=True)

                # Copy the file to the destination directory
                shutil.copy2(source_path, destination_path)
                print(f"File '{filename}' copied to '{destination_directory}'.")

