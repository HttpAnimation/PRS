gcc server.c -o server
gcc client.c -o client

echo "$(date +'%Y-%m-%d %H:%M:%S')" > Builds/Version.ini