# open-RAN testing interface

## Building
### From source code
#### Step 1:
**Obtaining the Deployment Scripts.**
```
git clone https://github.com/justnik98/open-ran-interface.git
cd ./open-ran-interface
```
#### Step 2:

**Edit the config.cf file to specify system parametrs.**
```
#redis client setup
REDIS_IP=127.0.0.1
REDIS_PORT=6379
TOPICS = foo,foo2,foo3

#thread setup

MAX_NUMBER_OF_THREADS=4
```
#### Step 3:
**Installing dependencies and deploying.**
```
conan install .
cmake . -DCMAKE_BUILD_TYPE=RELEASE
make
cd ./bin
./oran-interface
```
