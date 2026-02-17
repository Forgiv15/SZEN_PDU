import os
from pathlib import Path
from datetime import datetime

# =========================
# CONFIGURATION
# =========================

# Change this to your source folder
SOURCE_DIR = r"C:\Users\forgi\MPLABProjects\SZEN_PDU_0.1\My_MCC_Config\src"

# Output file
OUTPUT_FILE = "project_export.txt"

# File extensions to include
VALID_EXTENSIONS = [".c", ".h"]

# =========================
# SCRIPT
# =========================

def collect_source_files(source_dir):
    source_path = Path(source_dir)
    files = []

    for ext in VALID_EXTENSIONS:
        files.extend(source_path.rglob(f"*{ext}"))

    # Sort for deterministic output
    files = sorted(files, key=lambda x: str(x).lower())

    return files


def write_output(files, source_dir, output_file):
    source_path = Path(source_dir)

    with open(output_file, "w", encoding="utf-8") as f:
        # Global header
        f.write("=" * 80 + "\n")
        f.write("PROJECT SOURCE EXPORT\n")
        f.write("=" * 80 + "\n")
        f.write(f"Source directory: {source_dir}\n")
        f.write(f"Exported at: {datetime.now()}\n")
        f.write(f"Total files: {len(files)}\n")
        f.write("=" * 80 + "\n\n")

        for file_path in files:
            relative_path = file_path.relative_to(source_path)

            f.write("\n" + "#" * 80 + "\n")
            f.write(f"FILE: {relative_path}\n")
            f.write(f"TYPE: {file_path.suffix}\n")
            f.write("#" * 80 + "\n\n")

            try:
                with open(file_path, "r", encoding="utf-8", errors="replace") as src:
                    content = src.read()
                    f.write(content)
            except Exception as e:
                f.write(f"\n[ERROR READING FILE: {e}]\n")

            f.write("\n\n")

    print(f"\nExport complete → {output_file}")


def main():
    print("Collecting source files...")
    files = collect_source_files(SOURCE_DIR)

    if not files:
        print("No source files found.")
        return

    print(f"Found {len(files)} files.")
    write_output(files, SOURCE_DIR, OUTPUT_FILE)


if __name__ == "__main__":
    main()
