import os
import datetime
import requests
from urllib.parse import urljoin
from pathlib import Path

# URL of the playlist containing the list of .ts video segment files
playlist_url = "<insert playlist link here>" 

# Extract the base URL from the playlist URL for joining with segment filenames
base_url = playlist_url.rsplit('/', 1)[0] + "/"

# Generate a timestamped directory name for saving downloaded files
current_time = datetime.datetime.now()
timestamp = current_time.strftime("%Y%m%d_%H%M%S")
directory_name = f"output_{timestamp}"

# Fetch the playlist content (typically an .m3u8 file)
response = requests.get(playlist_url)
lines = response.text.strip().splitlines()

# Extract segment URLs from the playlist, skipping any comment or directive lines (e.g., lines starting with "#")
segment_urls = [
    urljoin(base_url, line)
    for line in lines
    if line and not line.startswith("#")
]

# Create a new directory to store the downloaded video segments
os.mkdir(directory_name)

# Open a text file to store the list of downloaded segment filenames
# This is often used for concatenating segments later with tools like ffmpeg
with open(f"{directory_name}/segments.txt", "w") as f:
    for i, segment_url in enumerate(segment_urls):
        # Define the local filename for each segment
        filename = f"{directory_name}/segment{i}.ts"
        try:
            # Download the video segment and save it to disk
            with open(filename, "wb") as out:
                seg_data = requests.get(segment_url).content
                out.write(seg_data)
            
            # Write the file reference to the segments.txt file in the required format for ffmpeg
            f.write(f"file '{filename}'\n")
        except:
            pass
