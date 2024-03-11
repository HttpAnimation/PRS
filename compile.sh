gcc server.c -o Builds/server
gcc client.c -o Builds/client

echo "$(date +'%Y-%m-%d %H:%M:%S')" > Builds/Version.ini