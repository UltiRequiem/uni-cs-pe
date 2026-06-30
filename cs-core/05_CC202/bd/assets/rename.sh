for file in *\ \(*\)*; do
    if [ -f "$file" ]; then
        # Replaces spaces and parentheses with underscores
        newname=$(echo "$file" | tr -d '()' | tr -s ' ' '_')
        mv "$file" "$newname"
        echo "Renamed: '$file' to '$newname'"
    fi
done