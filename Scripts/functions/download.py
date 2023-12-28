import os
import tempfile
from urllib.request import urlopen, Request, URLError, HTTPError
from urllib.parse import urljoin
from zipfile import ZipFile

def download_and_extract(url, extract_folder):
    try:
        # Create a temporary folder to store the zip file
        temp_folder = tempfile.mkdtemp()
        
        # Set user-agent header to mimic Microsoft Edge
        headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36 Edg/91.0.864.59"}
        request = Request(url, headers=headers)

        # Download the file to the temporary folder
        temp_zip_file_path = os.path.join(temp_folder, "glad.zip")
        with urlopen(request) as response:
            with open(temp_zip_file_path, "wb") as zip_file:
                zip_file.write(response.read())

        # Create the main extraction folder if it doesn't exist
        if not os.path.exists(extract_folder):
            os.makedirs(extract_folder)

        # Extract the contents
        with ZipFile(temp_zip_file_path, "r") as zip_ref:
            zip_ref.extractall(extract_folder)

        print(f"Download and extraction completed. Files are in '{extract_folder}' folder.")

        # Delete the temporary folder and its contents
        os.remove(temp_zip_file_path)
        os.rmdir(temp_folder)
        print(f"Temporary folder '{temp_folder}' deleted.")

    except HTTPError as e:
        print(f"HTTP Error: {e.code} - {e.reason}")
    except URLError as e:
        print(f"URL Error: {e.reason}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")