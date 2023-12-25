import functions.download as download
import functions.copy_files as copy;

from urllib.parse import urljoin
from zipfile import ZipFile


if __name__ == "__main__":
    base_url = "https://glad.dav1d.de/generated/tmpl95a1hepglad/"
    zip_file_url = urljoin(base_url, "glad.zip")
    extract_folder = "Dependencies"

    download.download_and_extract(zip_file_url, extract_folder)
    copy.copy_files_by_extension("Submodules/Source/Binaries/Debug-windows-x86_64", "Dependencies/lib", extension=".lib")
    copy.copy_files("Submodules/GLFW/include/GLFW", "Dependencies/include/GLFW")