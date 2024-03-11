#!/bin/bash

# Create Builds folder if it doesn't exist
mkdir -p Builds

# Get current date and time
current_datetime=$(date +'%Y-%m-%d_%H-%M-%S')

# Create a folder with the current date and time
build_folder="Builds/$current_datetime"
mkdir -p "$build_folder"

# Compile server.c and client.c into the build folder
gcc server.c -o "$build_folder/PRS-Server"
gcc -o "$build_folder/PRS-Client" client.c `pkg-config --cflags --libs gtk+-3.0`

# Copy server.c and client.c into the build folder
cp server.c "$build_folder/server.c"
cp client.c "$build_folder/client.c"

# Create a Version.ini file with the current date and time
echo "$current_datetime" > "$build_folder/Version.ini"

# Create README file
readme_file="$build_folder/README.txt"
echo "Build created at: $current_datetime" > "$readme_file"
echo "This folder contains builds for the server and client programs." >> "$readme_file"

# Print the path to the build folder
echo "Builds created at: $build_folder"
