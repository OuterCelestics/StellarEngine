import functions.download as download
import functions.copy_files as copy;
from zipfile import ZipFile


if __name__ == "__main__":
    base_url = "https://www.dropbox.com/scl/fi/vyp42bm1gu4orrjyg638v/glad.zip?rlkey=32c86nhaqagcbztlbji0tcv4r&dl=1"
    extract_folder = "Dependencies"

    download.download_and_extract(base_url, extract_folder)
    copy.copy_files_by_extension("Submodules/Source/Binaries/Debug-windows-x86_64", "Dependencies/lib", extension=".lib")
    copy.copy_files("Submodules/GLFW/include/GLFW", "Dependencies/include/GLFW")
    copy.copy_files("Dependencies/src", "Engine/source")