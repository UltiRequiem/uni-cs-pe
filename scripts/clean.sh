#!/bin/bash

# Directory to process (default: current)
DIR="${1:-.}"

# Loop through files with spaces in their names
find "$DIR" -depth -name "* *" | while read -r file; do
  # Build new name (replace spaces with underscores)
  newname=$(echo "$file" | tr ' ' '_')
  
  # Rename file
  mv "$file" "$newname"
  echo "Renamed: $file -> $newname"
done
