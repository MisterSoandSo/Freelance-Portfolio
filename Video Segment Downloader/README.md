# Video Segment Downloader

This is a basic Python script for downloading `.ts` video segments listed in a remote playlist (e.g., `.m3u8` format), and saves them locally along with a `segments.txt` file that can be used for further processing (e.g., merging the segments with `ffmpeg`).

## ⚠️ Warning

> **This script was created as part of an exploratory project bid and is provided _as-is_.**  
> It is not production-ready, and no guarantees are made regarding its correctness, stability, or completeness.  
> Use at your own risk.

## Features

- Automatically fetches and parses the playlist.
- Downloads all video segments listed.
- Saves segments into a timestamped output directory.
- Generates a `segments.txt` file compatible with `ffmpeg` for concatenation.

## Requirements

- Python 3.x
- `requests` library

You can install the required library using pip:

```bash
pip install requests
```