# open-RAN testing interface

## Building
### From source code
```
git clone https://github.com/justnik98/open-ran-interface.git
cd ./open-ran-interface
conan install .
cmake . -DCMAKE_BUILD_TYPE=RELEASE
make
cd ./bin
./open-ran-interface
```
