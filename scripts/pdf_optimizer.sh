find . -type f -name "*.pdf" -exec bash -c '
for f; do
  echo "Optimizing $f"
  gs -sDEVICE=pdfwrite \
     -dCompatibilityLevel=1.4 \
     -dPDFSETTINGS=/printer \
     -dNOPAUSE -dQUIET -dBATCH \
     -sOutputFile="${f}.tmp" "$f" && mv "${f}.tmp" "$f"
done
' bash {} +
