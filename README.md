# Vision and Image Recognition

## Using
- コンパイル
```
g++ -ggdb  `pkg-config --cflags opencv`  -o  `basename file_name.cpp .cpp`  file_name.cpp  `pkg-config --libs opencv` -std=c++14
```

- キャプチャ
```
import -window "window_name" file_name.jpg
```
